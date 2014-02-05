/*----------------------------------------------------------------------------*\
  ========                  |
     ||     T Thermal       | TAT: Thermal Analysis Toolbox
     ||     A Analysis      |
     ||     T Toolbox       | Copyright (C) 2013 Raymond Valdes
     ||                     |
--------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
    Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/

#include "thermal/analysis/thermalsweepoptimizer.hpp"
#include "math/estimation/constrained.hpp"
#include "math/utility.hpp"

namespace thermal{
namespace analysis{

ThermalSweepOptimizer::ThermalSweepOptimizer(
    const math::estimation::settings &Settings_in,
    const ThermalData &thermalData,
    const math::estimation::unknownList &unknownParameters_,
    const std::shared_ptr< LMA > &bestfitMethod_in,
    const std::shared_ptr< PIE > &intervalEstimates_in,
    const math::estimation::unknownList thermalSweepSearch_in,
    const std::vector<physicalModel::labels> sweepOptimizationGoal_in )
  : LMA_BASE( Settings_in, unknownParameters_, thermalData.size() ) ,
    bestfitMethod( bestfitMethod_in ),
    intervalEstimates( intervalEstimates_in ),
    thermalSweepSearch( thermalSweepSearch_in ),
    sweepOptimizationGoal( sweepOptimizationGoal_in )
{




}
ThermalSweepOptimizer::~ThermalSweepOptimizer( void ) {}

void ThermalSweepOptimizer::
  ThermalProp_Analysis( double *x, double *fvec, class Kernal &popteaCore )
{
//  //Update parameters with current bestfits by transforming x
//  math::estimation::unknownList updatedInput;
//  int i = 0;
//  for( auto& unknown :  (*unknownParameters)() )
//  {
//    const double val = math::estimation::
//        x_limiter2( x[i++] , unknown.lowerBound(), unknown.upperBound() );
//    unknown.bestfitset( val );
//    updatedInput.addUnknown(unknown);
//  }
//  (*unknownParameters)( updatedInput() );

//  ///Load these unknownParameters into the popteaCore and thermalData kernals
//  thermalData->updatefromBestFit( (*unknownParameters)() ,
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

  return;
}

void ThermalSweepOptimizer::updateWorkSpace( const size_t Lend, const size_t N )
{
//  LMA_workspace.updateArraySize( Lend , N );
}

double ThermalSweepOptimizer::bestFit( void )
{
  bestfitMethod->solve( unknownParameters, thermalData, coreSystem );
  return thermalData->MSE;
}

void ThermalSweepOptimizer::pieAnalysis( void )
{
  intervalEstimates->solve( unknownParameters, thermalData, coreSystem,
                            bestfitMethod );
}

void ThermalSweepOptimizer::start(
    const std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
    const std::shared_ptr<ThermalData> &thermalData_in,
    const std::shared_ptr<Kernal> &coreSystem_in,
    const std::shared_ptr<LMA> &bestfitMethod_in,
    const std::shared_ptr<PIE> &intervalEstimates_in )
{

  unknownParameters = unknownParameters_in;
  thermalData = thermalData_in;
  coreSystem = coreSystem_in;
  bestfitMethod = bestfitMethod_in;
  intervalEstimates = intervalEstimates_in;

  solve( unknownParameters_in, thermalData_in, coreSystem_in  ) ;
}

void ThermalSweepOptimizer::solve(
    const std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
    const std::shared_ptr<ThermalData> &thermalData_in,
    const std::shared_ptr<Kernal> &coreSystem_in )
{

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
    //see global object

    ///The optimization algorithm will have the experimental data in vector for.
    /// I need to take that data and be able to resize it.
//    using math::estimation::unknown;
//    saveExperimental( *thermalData );
//    std::vector< unknown > originalListParams = (*unknownParameters)();



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



}}
