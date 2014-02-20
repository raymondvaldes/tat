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
#include <algorithm>

#include "thermal/analysis/thermalsweepoptimizer.hpp"
#include "math/estimation/constrained.hpp"
#include "math/utility.hpp"
#include "math/numIntegration/gslfunc.hpp"
#include "math/estimation/lmdiff.hpp"

namespace thermal{
namespace analysis{

ThermalSweepOptimizer::ThermalSweepOptimizer(
    const math::estimation::settings &Settings_in,
    const ThermalData &thermalData_in,
    const math::estimation::unknownList &unknownParameters_,
    const std::shared_ptr< LMA > &bestfitMethod_in,
    const std::shared_ptr< PIE > &intervalEstimates_in,
    const math::estimation::unknownList thermalSweepSearch_in,
    const std::vector<physicalModel::labels> sweepOptimizationGoal_in,
    const physicalModel::layer coating)
  : LMA_BASE( Settings_in, unknownParameters_, thermalData_in.size() ) ,
    bestfitMethod( bestfitMethod_in ),
    intervalEstimates( intervalEstimates_in ),
    thermalSweepSearch( thermalSweepSearch_in ),
    sweepOptimizationGoal( sweepOptimizationGoal_in ),
    coatingTOinterpretFullRange( new physicalModel::layer( coating )),
    xSweep(0.5,0.5)
{
  updateWorkSpace( thermalSweepSearch_in, sweepOptimizationGoal_in );

}

ThermalSweepOptimizer::~ThermalSweepOptimizer( void ) {

}

std::pair< double, double > ThermalSweepOptimizer::updateSweep( void )
{
  double thermalCenter = 0;
  double thermalRange = 0;

  for( const auto& unknown : thermalSweepSearch() )
  {
    const double bestfit  = unknown.bestfit();
    if ( unknown.label() == physicalModel::labels::Name::thermalCenter  )
      { thermalCenter = bestfit ; }
    else if ( unknown.label() == physicalModel::labels::Name::thermalRange  )
      { thermalRange = bestfit ; }
  }

  return std::make_pair( thermalCenter, thermalRange ) ;
}


void ThermalSweepOptimizer::
  ThermalProp_Analysis( double *x, double *fvec )
{
  //Update parameters with current bestfits by transforming x
  math::estimation::unknownList updatedInput;
  size_t i = 0;
  for( auto& unknown : thermalSweepSearch() )
  {
    const double val = math::estimation::
        x_limiter2( x[i++] , unknown.lowerBound(), unknown.upperBound() );
    unknown.bestfitset( val ) ;
    updatedInput.addUnknown(unknown) ;
  }
  thermalSweepSearch( updatedInput() ) ;

  ///Load these to slice the thermal Data
  xSweep = updateSweep() ;

  const double xCenter = xSweep.first ;
  const double xRange = xSweep.second ;
  const physicalModel::layer coatUpdate( coreSystem->TBCsystem.coating );

  ThermalData updatedThermal = sliceThermalData( xCenter, xRange, coatUpdate ) ;
  reassign( thermalData , updatedThermal ) ;

  // Parameter Estimation with PIE analysis
  pieAnalysis();

  ///Use results from anaylsis
  i =0 ;
  for( physicalModel::labels& myParam : sweepOptimizationGoal )
  {
    double error = 0 ;

    for ( math::estimation::unknown& unknown: (*unknownParameters)() )
    {
      if ( myParam.getName() == unknown.label() )
      {
        error = unknown.bestfitIntervalSpread();
      }
    }

    error += penalty( xSweep );

    fvec[i] = error ;
    i++;
  }

  return;
}

void ThermalSweepOptimizer::pieAnalysis(void)
{
  PIE::PIEAnalysisOutput output =
  intervalEstimates->solve( unknownParameters , thermalData , coreSystem ,
                            bestfitMethod ) ;
  captureState( coreSystem->TBCsystem.coating );


  for(size_t i = 0; i < 60 ; i ++)
    std::cout << "\n";
  std::cout << currentState.ppFinalResults() << "\n" ;
 }


double ThermalSweepOptimizer::penalty(
    const std::pair<double, double>  thermalCenterRange )
{
  const double center = thermalCenterRange.first;
  const double range = thermalCenterRange.second;

  const double strPos = center - range/2;
  const double endPos = center + range/2;

  double error = 0;

  if( strPos < 0 || endPos > 1  )
  {
    double errorModifier = 0;
    if ( strPos < 0 )
    {
      errorModifier = strPos ;
    }
    else if ( endPos > 1 )
    {
      errorModifier = endPos - 1 ;
    }

    error += pow( std::abs( floor( errorModifier*100 ) ) , 2 ) ;
  }

  return error;
}




void ThermalSweepOptimizer::updateWorkSpace( const size_t Lend, const size_t N )
{
  LMA_workspace.updateArraySize( Lend , N );
}

void ThermalSweepOptimizer::updateWorkSpace(
    const math::estimation::unknownList &thermalSweepSearch_in,
    const std::vector<physicalModel::labels> &sweepOptimizationGoal_in)
{
  const size_t Lend = sweepOptimizationGoal_in.size();
  const size_t N = thermalSweepSearch_in.size();
  updateWorkSpace( Lend, N ) ;
}

void ThermalSweepOptimizer::OptimizerOutput::clear( void )
{
}

void ThermalSweepOptimizer::OptimizerOutput::pp2Folder(const std::string path )
{

}


std::string ThermalSweepOptimizer::OptimizerOutput::ExperimentAnalysisState::
  ppFinalResults( void )
{
  std::ostringstream output ;

  output << unknownParameters->prettyPrint() ;

  const double lthermCenter = lthermalCenterDecades.first;
  const double lthermDecade = lthermalCenterDecades.second;

  const double lthermMin = lthermalLimits.first;
  const double lthermMax = lthermalLimits.second;

  output.setf( std::ios::fixed, std::ios::floatfield );
  output << std::setprecision(3);
  output << "| lthermal center: "<< std::setw(8) << std::right
         << lthermCenter << "               |\n";
  output << "| lthermal decades:"<< std::setw(8) << std::right
         << lthermDecade << "               |\n";
  output << "| lmin:     "<< std::setw(8) << std::right
         << lthermMin << "                      |\n";
  output << "| lmax:     "<< std::setw(8) << std::right
         << lthermMax << "                      |\n";
  output << "*-----------------------------------------*\n";

  return output.str() ;
}


ThermalSweepOptimizer::OptimizerOutput
ThermalSweepOptimizer::solve(
    const std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
    const std::shared_ptr<ThermalData> &thermalData_in,
    const std::shared_ptr<Kernal> &coreSystem_in,
    const std::shared_ptr<LMA> &bestfitMethod_in,
    const std::shared_ptr<PIE> &intervalEstimates_in )
{
  ouputResults.clear();

  bestfitMethod = bestfitMethod_in;
  intervalEstimates = intervalEstimates_in;

  solve( unknownParameters_in, thermalData_in, coreSystem_in  ) ;
  return ouputResults;
}

void ThermalSweepOptimizer::solve(
    const std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
    const std::shared_ptr<ThermalData> &thermalData_in,
    const std::shared_ptr<Kernal> &coreSystem_in )
{
  unknownParameters = unknownParameters_in;
  thermalData = thermalData_in;
  coreSystem = coreSystem_in;

  reassign( coatingTOinterpretFullRange, coreSystem->TBCsystem.coating  );
  fullRangeThermalData = thermalData;

  ///at this point all the input objects have been set and are now available
  optimizer( &info, &nfev );
}



ThermalData ThermalSweepOptimizer::sliceThermalData(
    const double xCenter, const double xRange,
    const physicalModel::layer updatedCoating )
{
  // Establish omegas limits of full range (FR) experimental data
  std::pair<double, double> omegaLimits =
      fullRangeThermalData->get_omegaLimits( ) ;

  std::vector<double> omegasMonoIncreasing( fullRangeThermalData->size() ) ;
  std::reverse_copy(
        std::begin( fullRangeThermalData->omegas ),
        std::end( fullRangeThermalData->omegas ),
        std::begin( omegasMonoIncreasing ) ) ;

  std::vector<double> emissionReversed( fullRangeThermalData->size() ) ;
  std::reverse_copy(
        std::begin( fullRangeThermalData->experimentalEmission ),
        std::end( fullRangeThermalData->experimentalEmission ),
        std::begin( emissionReversed ) ) ;

  math::numIntegration::funcClass experimentalEmissionInterpolater(
    &omegasMonoIncreasing[0] , &emissionReversed[0],
      omegasMonoIncreasing.size() ) ;

  // Use omega to derive current lthermalsLimits that correspond to FullRange
  const double coatingLength = updatedCoating.depth;
  const double coatingK = updatedCoating.kthermal.offset;
  const double coatingPsi = updatedCoating.psithermal.offset;

  const std::pair<double, double> thermalLimits(
  lthermal( coatingLength, coatingK,  coatingPsi, omegaLimits.first  ) ,
  lthermal( coatingLength, coatingK,  coatingPsi, omegaLimits.second ) ) ;

  // Take a slice of thermalData range based on updated limits and xC,xR
  const std::pair<double, double> slicedThermalLimits =
  math::newThermalSweepLimits( xCenter, xRange, thermalLimits ) ;

  const double lmin = slicedThermalLimits.first ;
  const double lmax = slicedThermalLimits.second ;
  const size_t lminPerDecarde = fullRangeThermalData->measurementsPerDecade;

  // Create vector of lthermals for my slice of data
  ThermalData output( lmin , lmax , lminPerDecarde, updatedCoating ) ;
  std::vector<double> sliceEmission( output.size() ); /*output.size() */

  size_t i = 0;
  for( auto& omega : output.omegas )
  {
    sliceEmission[i] =   experimentalEmissionInterpolater.eval( omega );
    i++;
  }
  output.updateExperimental( sliceEmission );

  return output;
}

void ThermalSweepOptimizer::optimizer( int *info, int *nfev )
{
  ///Create workspaces
  using namespace math::estimation;
  size_t m = sweepOptimizationGoal.size();
  size_t n = thermalSweepSearch.size();

  double *x = new double[n];
  double *fvec = new double[m];
  double *qtf = new double[n];
  double *wa1 = new double[n];
  double *wa2 = new double[n];
  double *wa3 = new double[n];
  double *wa4 = new double[m];
  double *fjac = new double[m*n];
  double *wa5 = new double[m*n];
  int *ipvt = new int[n];
  double *diag = new double[n];

  ///populate initial values
  std::vector<double> xInitial(0) ;
  for( const auto &unknown : thermalSweepSearch() )
    { xInitial.push_back( unknown.initialVal() ); }
  for( size_t i=0 ; i< n ; i++ )
    { x[i] = xInitial[i]; }


//  if( Settings.mode == 2 )
//  {
//    int i = 0;
//  for( const class math::estimation::unknown &unknown : thermalSweepSearch())
//    { diag[i++] = TBCsystem.returnVal( unknown.label() ); }
//  }


  ///Transform inputs
  size_t j = 0;
  for( const auto& unknown : thermalSweepSearch() )
  {
    x[j] = kx_limiter2( x[j], unknown.lowerBound(), unknown.upperBound() );
    j++;
  }

  /// Constrained nonlinear parameter estimation
  updateBindFunc() ;
  lmdif( myReduced, static_cast<int>(m), static_cast<int>(n), x, fvec,
         Settings.ftol, Settings.xtol, Settings.gtol,
         static_cast<int>(Settings.maxfev), Settings.epsfcn, diag,
         static_cast<int>(Settings.mode), Settings.factor,
         static_cast<int>(Settings.nprint), info, nfev, fjac,
         static_cast<int>(m), ipvt, qtf, wa1, wa2, wa3, wa4 ) ;

  ///Final fit
  bestfitMethod->solve( unknownParameters, thermalData, coreSystem );
  coreSystem->updatefromBestFit( (*unknownParameters)() );  

  delete [] qtf;
  delete [] wa1;
  delete [] wa2;
  delete [] wa3;
  delete [] wa4;
  delete [] wa5;
  delete [] ipvt;
  delete [] fvec;
  delete [] fjac;
  delete [] diag;
  delete [] x;
}

}}
