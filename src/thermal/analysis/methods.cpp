/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
-------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/
#include <vector>
#include <string>
#include <functional>

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/methods.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "models/physicalmodel.hpp"
#include "math/algorithms/combinations.hpp"
#include "math/utility.hpp"
namespace thermal{
namespace analysis{

methods::methods( const math::estimation::settings &Settings_in,
                  const math::estimation::unknownList &unknownParameters_in,
                  const ThermalData& thermalData_in )
  : bestfitMethod( Settings_in, unknownParameters_in, thermalData_in.size() )
{
}

double methods::bestFit(
    std::shared_ptr< math::estimation::unknownList > &list_in,
    std::shared_ptr< ThermalData > &thermalData_in,
    std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  bestfitMethod.solve( list_in, thermalData_in, coreSystem_in );

  coreSystem_in->updatefromBestFit( (*list_in)() );


  return thermalData_in->MSE;
}

double methods::Gfunc( const double val ,
                       const enum physicalModel::labels::Name &mylabel)
{  
  coreSystem->TBCsystem.updateVal( mylabel , val ) ;
  coreSystem->TBCsystem.updateCoat() ;

  bestFit( unknownParameters, thermalData, coreSystem ) ;

  return thermalData->MSE;
}


double methods::optiGfun( const double xCenter, const double xRange,
                          const enum physicalModel::labels::Name &mylabel)
{
  const size_t numPos = 10;
  resizeExperimental( xCenter, xRange, numPos );

  bestFit( unknownParameters, thermalData, coreSystem ) ;
  parameterIntervalEstimates( unknownParameters, thermalData, coreSystem ) ;

  double xreturn = 1;
  for( math::estimation::unknown& val : (*unknownParameters)() )
  {
    if( val.label() == mylabel )
    {
      xreturn = math::xspread( val.bestfitInterval.lower, val.bestfit(),
                               val.bestfitInterval.upper );
    }
  }

  return xreturn;
}

void methods::updateExperimentalData( const std::vector<double> &omegas,
                                      const std::vector<double> &input,
                                      Kernal &coreSystem_in,
                                      ThermalData &thermalData_in )
{
  thermalData_in.updateOmegas( omegas , coreSystem_in.TBCsystem.coating );
  thermalData_in.updateExperimental( input );
}

void methods::parameterIntervalEstimates(
    std::shared_ptr< math::estimation::unknownList > &list_in,
    std::shared_ptr< ThermalData > &thermalData_in,
    std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  unknownParameters = list_in;
  thermalData = thermalData_in;
  coreSystem = coreSystem_in;

  /// Save experimental data, quality-of-fit, unknownParameter List
  using math::estimation::unknown;
  std::vector< unknown > originalListParams( (*unknownParameters)() );
  saveExperimental( *thermalData );
  const double S1 = thermalData->MSE;

  /// Update initial guess using bestfits
  for( auto& param : originalListParams)
    { param.Initialset( param.bestfit() ); }

  /// Predicted emission as the new experimental
  const std::vector<double> TEMPExperimental = thermalData->predictedEmission;
  updateExperimentalData( SAVEomega, TEMPExperimental, *coreSystem, *thermalData);

  /// Create list of parameters that must be refitted
  using math::algorithms::combos_minusOne;
  const std::vector< std::vector<  unknown > >
      unknownParaLists = combos_minusOne( originalListParams );

  std::vector< enum physicalModel::labels::Name  > parametersToBeManipulated;
  for ( const auto& unknown : originalListParams )
    { parametersToBeManipulated.push_back( unknown.label() ); }

  /// update list of parameters using unknownIterations
  size_t i = 0;
  for( auto& newListVect : unknownParaLists )
  {
    ///identifiy fixed parameter and update search bound
    const unknown myfixedParameter =  originalListParams[i];
    const enum physicalModel::labels::Name mylabel = myfixedParameter.label();
    const double bestfit = myfixedParameter.bestfit();
    const double lowerbound = myfixedParameter.lowerBound();
    const double upperbound = myfixedParameter.upperBound();

    ///search space
    (*unknownParameters)( newListVect );
    const double min = solve( S1, lowerbound, bestfit , mylabel, "min" ) ;
    const double max = solve( S1, bestfit, upperbound , mylabel, "max" ) ;

    originalListParams[i++].bestfitIntervalset( min, max);
  }

  ///Update list of parameters with updated list  
  (*unknownParameters)( originalListParams );
  updateExperimentalData( SAVEomega , SAVEExperimental, *coreSystem, *thermalData);
  thermalData_in->MSE = S1;
}

double methods::solve(const double target , const double min, const double max,
                       const enum physicalModel::labels::Name mylabel,
                       const std::string &bound)
{
  const std::function<double(double)>
      myFuncReduced = std::bind( &methods::Gfunc, this , std::placeholders::_1,
                                 mylabel ) ;

  const math::solve ojb( myFuncReduced, target, min, max ) ;
  double soln = ojb.returnSoln();

  if(!ojb.pass)
  {
    if( bound == "min" ) soln = min;
    if( bound == "max" ) soln = max;
  }

  return soln;
}


std::vector<double>
methods::resizeExperimental( const double center, const double range,
                             const size_t numPos )
{
  const double lmin = SAVEExperimental.front();
  const double lmax = SAVEExperimental.back();

  const double strPos = center - range/2;
  const double endPos = center + range/2;

  const double lminNEW = math::valFROMpercentileLog10( strPos, lmin, lmax ) ;
  const double lmaxNEW = math::valFROMpercentileLog10( endPos, lmin, lmax ) ;

  std::vector<double>output = math::range1og10( lminNEW, lmaxNEW, numPos );

  return output;
}

void methods::optimization(
    std::shared_ptr< math::estimation::unknownList > &list_in,
    std::shared_ptr< ThermalData > &thermalData_in,
    std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  coreSystem = coreSystem_in;
  thermalData = thermalData_in;
  unknownParameters = list_in;

  ///The optimization algorithm will have the experimental data in vector for.
  /// I need to take that data and be able to resize it.
  using math::estimation::unknown;
  saveExperimental( *thermalData );
  std::vector< unknown > originalListParams = (*unknownParameters)();


  /// I need to create ways to optimize thermal penetration. The ones I am
  /// thinking
  ///   a) given X data what is the optimal range to best estimate properties
  ///      - original data limited in range
  ///      - cannot introduce new measurements
  ///   b) given LMIN and LMAX what is the optimal range to take data to
  ///     ensure the most accurate measurements
  ///  The function I am minimizing is
  ///  S1
  ///
  /// So this means one should be from the perspective of someone doing
  /// post-analysis on their data.  They have a given range of values ( a
  /// thermograph) and they're looking to see how much data to keep.
  ///
  ///


  ///Update list of parameters with updated list
  (*unknownParameters)( originalListParams ) ;
  updateExperimentalData( SAVEomega , SAVEExperimental, *coreSystem,
                          *thermalData );
}

void methods::saveExperimental(const ThermalData& thermalData_in)
{
  SAVEExperimental = thermalData_in.experimentalEmission;
  SAVEomega = thermalData_in.omegas;
}






}}
