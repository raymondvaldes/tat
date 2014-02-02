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

methods::methods( const math::estimation::settings &Settings_,
                  const math::estimation::unknownList &unknownParameters_,
                  const ThermalData& thermalData_ )
  : bestfitMethod( Settings_, unknownParameters_, thermalData_.size() )
{}

double methods::bestFit( Kernal &coreSystem, ThermalData &thermalData,
                         math::estimation::unknownList& list )
{
  std::shared_ptr< thermal::analysis::Kernal > coreSystem_p;
  std::shared_ptr< ThermalData > thermalData_p;
  std::shared_ptr< math::estimation::unknownList > unknownParameters_p;

  reassign( coreSystem_p, coreSystem );
  reassign( unknownParameters_p, list );
  reassign( thermalData_p,  thermalData );

  bestfitMethod.solve( unknownParameters_p, thermalData_p, coreSystem_p );

  std::cout << "\ninside methods\n";
  for( auto& val : (*unknownParameters_p)() )
  {
    std::cout <<  val.bestfit() << "\n";
  }


  coreSystem.updatefromBestFit( list() );

  return thermalData.MSE;
}

double methods::Gfunc( const double val ,
                       const enum physicalModel::labels::Name &mylabel,
                       Kernal &coreSystem, ThermalData &thermalData,
                       math::estimation::unknownList &list )
{
  coreSystem.TBCsystem.updateVal( mylabel , val ) ;
  coreSystem.TBCsystem.updateCoat() ;

  bestFit( coreSystem, thermalData, list ) ;

  return thermalData.MSE;
}

void methods::updatelthermal( const double /*lmin*/, const double /*lmax*/ )
{
//  const size_t Lend =
//  thermalData.thermalSetup( lmin, lmax, coreSystem.TBCsystem.coating ) ;
//  analysis.bestfitMethod.updateWorkSpace(
//        Lend, analysis.bestfitMethod.unknownParameters.size() );
}


double methods::optiGfun( const double xCenter, const double xRange,
                          const enum physicalModel::labels::Name &mylabel,
                          Kernal &coreSystem, ThermalData &thermalData,
                          math::estimation::unknownList &list)
{
  const size_t numPos = 10;
  resizeExperimental( xCenter, xRange, numPos );

  bestFit( coreSystem, thermalData, list );
  parameterIntervalEstimates( coreSystem, thermalData, list) ;

  double xreturn = 1;
  for( math::estimation::unknown& val : list() )
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
                                      Kernal &coreSystem,
                                      ThermalData &thermalData )
{
  thermalData.updateOmegas( omegas , coreSystem.TBCsystem.coating );
  thermalData.updateExperimental( input );
}

void methods::parameterIntervalEstimates( Kernal &coreSystem,
                                          ThermalData &thermalData,
                                          math::estimation::unknownList &list )
{
  /// Save experimental data, quality-of-fit, unknownParameter List
  using math::estimation::unknown;
  std::vector< unknown > originalListParams( list() );
  saveExperimental( thermalData );
  const double S1 = thermalData.MSE;

  /// Update initial guess using bestfits
  for( auto& param : originalListParams)
    { param.Initialset( param.bestfit() ); }

  /// Predicted emission as the new experimental
  const std::vector<double> TEMPExperimental = thermalData.predictedEmission;
  updateExperimentalData( SAVEomega, TEMPExperimental, coreSystem, thermalData);

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

//    std::cout << "solve this\t" << lowerbound << "\t" << bestfit << "\t" << upperbound << "\n";

    ///search space
    math::estimation::unknownList myUpdateList(newListVect);
    const double min = solve( S1, lowerbound, bestfit , mylabel, "min",
                              coreSystem, thermalData, myUpdateList ) ;
    const double max = solve( S1, bestfit, upperbound , mylabel, "max",
                              coreSystem, thermalData, myUpdateList ) ;

    originalListParams[i++].bestfitIntervalset( min, max);
  }

  ///Update list of parameters with updated list  
  list( originalListParams );
  updateExperimentalData( SAVEomega , SAVEExperimental, coreSystem,thermalData);
  thermalData.MSE = S1;
}

double methods::solve( const double target , const double min, const double max,
                       const enum physicalModel::labels::Name mylabel,
                       const std::string &bound, Kernal &coreSystem,
                       ThermalData &thermalData,
                       math::estimation::unknownList &list )
{
  using std::placeholders::_1;
  const std::function<double(double)>
      myFuncReduced = std::bind( &methods::Gfunc, this , _1 , mylabel,
                                 coreSystem, thermalData, list ) ;

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

void methods::optimization( Kernal &coreSystem, ThermalData &thermalData ,
                            math::estimation::unknownList &list)
{
  ///The optimization algorithm will have the experimental data in vector for.
  /// I need to take that data and be able to resize it.
  using math::estimation::unknown;
  saveExperimental( thermalData );
  std::vector< unknown > originalListParams = list();


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
  list( originalListParams ) ;
  updateExperimentalData( SAVEomega , SAVEExperimental, coreSystem,
                          thermalData );
}

void methods::saveExperimental( const ThermalData& thermalData)
{
  SAVEExperimental = thermalData.experimentalEmission;
  SAVEomega = thermalData.omegas;
}






}}
