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
#include "thermal/analysis/pie.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "models/physicalmodel.hpp"
#include "math/algorithms/combinations.hpp"
#include "math/utility.hpp"

namespace thermal{
namespace analysis{

methods::methods( const math::estimation::settings &Settings_in,
                  const math::estimation::unknownList &unknownParameters_in,
                  const ThermalData& thermalData_in )
  : bestfitMethod( new LMA( Settings_in, unknownParameters_in,
                            thermalData_in.size() ) ),
    intervalEstimates( new PIE() )
{}

double methods::bestFit(
    std::shared_ptr< math::estimation::unknownList > &list_in,
    std::shared_ptr< ThermalData > &thermalData_in,
    std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  bestfitMethod->solve( list_in, thermalData_in, coreSystem_in );

  coreSystem_in->updatefromBestFit( (*list_in)() );


  return thermalData_in->MSE;
}




//double methods::optiGfun( const double xCenter, const double xRange,
//                          const enum physicalModel::labels::Name &mylabel)
//{
//  const size_t numPos = 10;
//  resizeExperimental( xCenter, xRange, numPos );

//  bestFit( unknownParameters, thermalData, coreSystem ) ;
//  parameterIntervalEstimates( unknownParameters, thermalData, coreSystem ) ;

//  double xreturn = 1;
//  for( math::estimation::unknown& val : (*unknownParameters)() )
//  {
//    if( val.label() == mylabel )
//    {
//      xreturn = math::xspread( val.bestfitInterval.lower, val.bestfit(),
//                               val.bestfitInterval.upper );
//    }
//  }

//  return xreturn;
//}



void methods::parameterIntervalEstimates(
    std::shared_ptr< math::estimation::unknownList > &list_in,
    std::shared_ptr< ThermalData > &thermalData_in,
    std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  intervalEstimates->solve( list_in, thermalData_in, coreSystem_in,
                            bestfitMethod );


//  unknownParameters = list_in;
//  thermalData = thermalData_in;
//  coreSystem = coreSystem_in;

//  /// Save experimental data, quality-of-fit, unknownParameter List
//  using math::estimation::unknown;
//  std::vector< unknown > originalListParams( (*unknownParameters)() );
//  saveExperimental( *thermalData );
//  const double S1 = thermalData->MSE;

//  /// Update initial guess using bestfits
//  for( auto& param : originalListParams)
//    { param.Initialset( param.bestfit() ); }

//  /// Predicted emission as the new experimental
//  const std::vector<double> TEMPExperimental = thermalData->predictedEmission;
//  updateExperimentalData( TEMPExperimental, *thermalData) ;

//  /// Create list of parameters that must be refitted
//  using math::algorithms::combos_minusOne;
//  const std::vector< std::vector<  unknown > >
//      unknownParaLists = combos_minusOne( originalListParams );

//  std::vector< enum physicalModel::labels::Name  > parametersToBeManipulated;
//  for ( const auto& unknown : originalListParams )
//    { parametersToBeManipulated.push_back( unknown.label() ); }

//  /// update list of parameters using unknownIterations
//  size_t i = 0;
//  for( auto& newListVect : unknownParaLists )
//  {
//    ///identifiy fixed parameter and update search bound
//    const unknown myfixedParameter =  originalListParams[i];
//    const enum physicalModel::labels::Name mylabel = myfixedParameter.label();
//    const double bestfit = myfixedParameter.bestfit();
//    const double lowerbound = myfixedParameter.lowerBound();
//    const double upperbound = myfixedParameter.upperBound();

//    ///search space
//    (*unknownParameters)( newListVect );
//    const double min = solve( S1, lowerbound, bestfit , mylabel, "min" ) ;
//    const double max = solve( S1, bestfit, upperbound , mylabel, "max" ) ;

//    originalListParams[i++].bestfitIntervalset( min, max);
//  }

//  ///Update list of parameters with updated list
//  (*unknownParameters)( originalListParams );
//  updateExperimentalData(  SAVEExperimental, *thermalData ) ;
//  thermalData_in->MSE = S1;
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

void methods::optimization(
    std::shared_ptr< math::estimation::unknownList > &list_in,
    std::shared_ptr< ThermalData > &thermalData_in,
    std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  coreSystem = coreSystem_in;
  thermalData = thermalData_in;
  unknownParameters = list_in;

  ///Define experimental "operability domain"
  ///This is the section of my code where I have figured out what lmin and lmax
  /// is. At this point I am assuming that the experimental data has been loaded
  /// and a best fit has been done on the parameters.  The new lthermals are
  const std::pair<double, double> thermalOperabilityLimits =
      thermalData->get_lthermalLimits(coreSystem->TBCsystem.coating );
  std::cout << "thermalOperabilityLimits\t"
            << thermalOperabilityLimits.first << "\t"
            << thermalOperabilityLimits.second << "\n";

  ///Define acceptable tolerance.  This is where I give it a threshold in which
  /// it will seach for the optimal range and stop once the threshold is
  /// satisfied.
  const double minError = 0;

  /// Given a center and a range can I create data from this. [TEST]
  const double xCenter = .2;
  const double xRange = 1;
  const std::pair<double, double> updatedRange =
  math::newThermalSweepLimits( xCenter, xRange, thermalOperabilityLimits );
  std::cout << "updated range\t" << updatedRange.first << "\t"
            << updatedRange.second << "\n";

  const std::pair<double, double> CRfromSwweep =
  math::CRfromSweepLimits( updatedRange.first, updatedRange.second,
                     thermalOperabilityLimits );
  std::cout << "updated center range\t" << CRfromSwweep.first << "\t"
            << CRfromSwweep.second << "\n";


  ///Create list of unknowns
//  class math::estimation::unknownList unknownSweep;

//  unknownSweep.addUnknown( , 0, 1, 0.5);

//  physicalModel::labels::Name


  ///The optimization algorithm will have the experimental data in vector for.
  /// I need to take that data and be able to resize it.
//  using math::estimation::unknown;
//  saveExperimental( *thermalData );
//  std::vector< unknown > originalListParams = (*unknownParameters)();



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
//  (*unknownParameters)( originalListParams ) ;
//  updateExperimentalData(  SAVEExperimental, *thermalData );
}

void methods::saveExperimental(const ThermalData& thermalData_in)
{
  SAVEExperimental = thermalData_in.experimentalEmission;
  SAVEomega = thermalData_in.omegas;
}
void methods::updateExperimentalData( const std::vector<double> &input,
                                      ThermalData &thermalData_in )
{
  thermalData_in.updateExperimental( input );
}
double methods::Gfunc( const double val ,
                       const enum physicalModel::labels::Name &mylabel)
{
  coreSystem->TBCsystem.updateVal( mylabel , val ) ;
  coreSystem->TBCsystem.updateCoat() ;

  bestFit( unknownParameters, thermalData, coreSystem ) ;

  return thermalData->MSE;
}

//void methods::Optimization_Analysis( double *x, double *fvec,
//                                     class thermal::analysis::Kernal &popteaCore )
//{
//  //Update parameters with current bestfits by transforming x
//  math::estimation::unknownList updatedInput;
//  int i = 0;
//  for( auto& unknown :  (*unknownParameters_p)() )
//  {
//    const double val = math::estimation::
//        x_limiter2( x[i++] , unknown.lowerBound(), unknown.upperBound() );
//    unknown.bestfitset( val );
//    updatedInput.addUnknown(unknown);
//  }
//  (*unknownParameters_p)( updatedInput() );

//  ///Load these unknownParameters into the popteaCore and thermalData kernals
//  thermalData->updatefromBestFit( (*unknownParameters_p)() ,
//                                  popteaCore.TBCsystem.coating ) ;

//  // Estimates the phase of emission at each heating frequency
//  thermalData->predictedEmission =
//      thermal::emission::phase99( popteaCore, thermalData->omegas );

//  /// Evaluate Objective function
//  for( size_t n = 0 ; n < thermalData->omegas.size() ; ++n )
//  {
//     fvec[n] =  thermalData->experimentalEmission[n] -
//                    thermalData->predictedEmission[n] ;
//  }

//  return;
//}







}}
