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
#include "tools/interface/exportfile.hpp"

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


ThermalData ThermalSweepOptimizer::updatedFromXsearch( const double *x )
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
  const physicalModel::layer coatUpdate( coreSystem->TBCsystem.coating ) ;

  return sliceThermalData( xCenter, xRange, coatUpdate ) ;
}


void ThermalSweepOptimizer::ThermalProp_Analysis( double *x, double *fvec )
{
  // update experimental data used based on search
  ThermalData updatedThermal = updatedFromXsearch( x ) ;
  reassign( thermalData , updatedThermal ) ;

  // Parameter Estimation with PIE analysis
  pieAnalysis();

  ///Use results from anaylsis
  size_t i =0 ;
  for( physicalModel::labels& myParam : sweepOptimizationGoal )
  {
    double error = 0 ;

    for ( math::estimation::unknown& unknown: (*unknownParameters)() )
    {
      if ( myParam.getName() == unknown.label() )
      {
        error = unknown.bestfitIntervalSpread();
        //std::cout << error << "\t";
      }
    }
    //std::cout <<"\n";

    currentState.meanParameterError = error;
    error += penalty( xSweep );

    fvec[i] = error ;
    i++;
  }

  ouputResults.push_back( currentState ) ;


  return;
}

void ThermalSweepOptimizer::pieAnalysis(void)
{
  intervalEstimates->solve( unknownParameters , thermalData , coreSystem ,
                            bestfitMethod ) ;
  captureState( coreSystem->TBCsystem.coating ) ;


//  for(size_t i = 0; i < 60 ; i ++)
//    std::cout << "\n";
//  std::cout << currentState.ppFinalResults() << "\n" ;
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

    error += std::pow( std::fabs( std::floor( errorModifier*100 ) ) , 2 ) ;
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

void ThermalSweepOptimizer::OptimizerOutput::
addBefore( ExperimentAnalysisState input )
{
  reassign( results.before , input ) ;
}

void ThermalSweepOptimizer::OptimizerOutput::
addAfter( ExperimentAnalysisState input )
{
  reassign( results.after , input ) ;
}

void ThermalSweepOptimizer::OptimizerOutput::clear( void )
{
  searchPath.clear() ;
}

void ThermalSweepOptimizer::OptimizerOutput::pp2Folder(const std::string path )
{
  results.prettyPrint( path );

  const std::string searchOutput = searchPath.prettyPrint() ;
  const std::string fullPath = path + "/" + "optimizerPath.dat";
  tools::interface::exportfile( fullPath , searchOutput ) ;
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

std::string ThermalSweepOptimizer::OptimizerOutput::ExperimentAnalysisState::
  ppEmissionSweep( void )
{
  std::ostringstream output ;
  output << thermalData->prettyPrint( *coating ) ;

  return output.str() ;
}

void ThermalSweepOptimizer::OptimizerOutput::ExperimentAnalysisState::
ppExportEmissionSweep( const std::string path )
{
  const std::string fullpath =  path + "/" +  "emission.dat" ;
  const std::string output = ppEmissionSweep() ;

  tools::interface::exportfile( fullpath , output ) ;
}

void ThermalSweepOptimizer::OptimizerOutput::ExperimentAnalysisState::
ppExportAll( const std::string path )
{
  ppExportEmissionSweep( path ) ;
  const std::string output = ppFinalResults();
  tools::interface::exportfile( path + "/" + "pie.dat", output ) ;

  const std::string fullpath =  path + "/" +  "emission.dat" ;
  const std::string outEmission = ppEmissionSweep() ;
  tools::interface::exportfile( fullpath , outEmission ) ;
}

void ThermalSweepOptimizer::OptimizerOutput::ExperimentAnalysisState::
clear( void )
{
  thermalData.reset() ;
  coating.reset() ;
  unknownParameters.reset() ;
  thermalSweepSearch.reset() ;

  fitquality = 0 ;
}

std::string ThermalSweepOptimizer::OptimizerOutput::SearchPath::
prettyPrint( void )
{
  std::ostringstream output;

  output << "#|-------------------------------------------------------------\n";
  output << "#| Search Path                                                 \n";
  output << "#|                                                             \n";
  output << "#| columns...                                                  \n";
  output << "#| lthermal center  :                                          \n";
  output << "#| lthermal decade  :                                          \n";
  output << "#| lthermal min     :                                          \n";
  output << "#| lthermal max     :                                          \n";
  output << "#| fit-quality      :                                          \n";
  output << "#| mean parameter error  :                                     \n";
  output << "#|                                                             \n";
  output << "#|-------------------------------------------------------------\n";

  for ( ExperimentAnalysisState state : path )
  {
    output << state.lthermalCenterDecades.first << "\t"
           << state.lthermalCenterDecades.second << "\t"
           << state.lthermalLimits.first << "\t"
           << state.lthermalLimits.second << "\t"
           << state.fitquality << "\t"
           << state.meanParameterError << "\t"
           << "\n";
  }
  return output.str() ;
}

void ThermalSweepOptimizer::OptimizerOutput::SearchPath::
push_back( const ExperimentAnalysisState &data_in )
{
  path.push_back( data_in ) ;
}


void ThermalSweepOptimizer::OptimizerOutput::Comparison::
prettyPrint( const std::string path )
{
  const std::string pre = "before" ;
  const std::string fullPathpre = path + "/" + pre;
  filesystem::makeDir( path , pre ) ;
  before->ppExportAll( fullPathpre ) ;


  const std::string post = "after" ;
  const std::string fullpathPost = path + "/" + post;
  filesystem::makeDir( path , post ) ;
  after->ppExportAll( fullpathPost ) ;
}

void ThermalSweepOptimizer::OptimizerOutput::SearchPath::
clear( void )
{
  path.clear();
}

void ThermalSweepOptimizer::OptimizerOutput::
  push_back( const ExperimentAnalysisState &data_in )
{
  searchPath.push_back( data_in ) ;
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

void ThermalSweepOptimizer::upSweepStartReset( void )
{
  bool pass = false;

  while( !pass )
  {
    thermalSweepSearch.resetBestfits() ;
    pass = math::checkLimits( thermalSweepSearch.vectorUnknowns[0].bestfit() ,
                              thermalSweepSearch.vectorUnknowns[0].bestfit() ) ;
  }
}

math::estimation::unknownList thermalSweepSearch;

void ThermalSweepOptimizer::
upSweepOptiGoals ( const std::vector<physicalModel::labels> &goal )
{
  sweepOptimizationGoal = goal;
}



std::string ThermalSweepOptimizer::montecarloMap(
    const std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
    const std::shared_ptr<ThermalData> &thermalData_in,
    const std::shared_ptr<Kernal> &coreSystem_in,
    const std::shared_ptr< LMA > &bestfitMethod_in,
    const std::shared_ptr< PIE > &intervalEstimates_in, const size_t iIter )
{
  //The purpose here is to get the "best possible fit" and use that as my ref.
  solve( unknownParameters_in, thermalData_in, coreSystem_in, bestfitMethod_in,
         intervalEstimates_in ) ;

  reassign ( unknownBestFit , *unknownParameters  ) ;
  coreSystem->updatefromBestFit( (*unknownParameters)() );
  reassign( coatingTOinterpretFullRange, coreSystem->TBCsystem.coating  ) ;

  //This function will output a table of values from maping out
  constexpr double min = 0 ;
  constexpr double max = 1 ;

  ouputResults.clear();
  for( size_t i = 0; i < iIter ; ++i )
  {
    ///create random start points and transform them
    bool initialGuessPass = false;
    double xinitial[2] = {0};

    while ( !initialGuessPass )
    {
      xinitial[0] = math::x_ini( min, max ) ;
      xinitial[1] = math::x_ini( min, max ) ;
      initialGuessPass = math::checkLimits( xinitial[0] , xinitial[1] ) ;
    }

    /// transform it into something thermal_prop can understand
    double x[2] = { 0 } ;
    for( size_t j =0 ; j < 2 ; ++j )
      { x[j] = math::estimation::kx_limiter2( xinitial[j], min, max ) ; }

    double fvec[2] = {0} ;
    ThermalProp_Analysis( x , fvec ) ;

    ///reset unknown parameters
    reassign( unknownParameters , *unknownBestFit ) ;
    coreSystem->updatefromBestFit( (*unknownBestFit)() );
  }


  std::ostringstream output;

  output << "#|-------------------------------------------------------------\n";
  output << "#| Contour Map of Experimental Optimization                    \n";
  output << "#|                                                             \n";
  output << "#| columns...                                                  \n";
  output << "#| lthermal center  :                                          \n";
  output << "#| lthermal decade  :                                          \n";
  output << "#| mean parameter error  :                                     \n";
  output << "#|                                                             \n";
  output << "#|-------------------------------------------------------------\n";

  for( OptimizerOutput::ExperimentAnalysisState&state :
       ouputResults.searchPath.path )
  {
    output <<
    state.lthermalCenterDecades.first   << "\t" <<
    state.lthermalCenterDecades.second  << "\t" <<
    state.meanParameterError << "\n";
  }
  return output.str();

}

void ThermalSweepOptimizer::captureState( const physicalModel::layer coat )
{
  currentState.lthermalLimits = thermalData->get_lthermalLimits( coat ) ;
  currentState.lthermalCenterDecades =
      math::xCenterlog10( currentState.lthermalLimits.first,
                          currentState.lthermalLimits.second );

  reassign( currentState.thermalData, *thermalData ) ;
  reassign( currentState.thermalSweepSearch, thermalSweepSearch ) ;
  reassign( currentState.unknownParameters, *unknownParameters ) ;
  reassign( currentState.coating, (*coreSystem).TBCsystem.coating ) ;
  currentState.fitquality = thermalData->MSE ;
}

void ThermalSweepOptimizer::solve(
    const std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
    const std::shared_ptr<ThermalData> &thermalData_in,
    const std::shared_ptr<Kernal> &coreSystem_in )
{
  ///at this point all the input objects have been set
  unknownParameters = unknownParameters_in ;
  thermalData = thermalData_in ;
  coreSystem = coreSystem_in ;

  reassign( coatingTOinterpretFullRange, coreSystem->TBCsystem.coating ) ;
  fullRangeThermalData = thermalData ;

  /// pre analysis on full-range
  double xC = 0.5 ;
  double xR = 1 ;
  const physicalModel::layer coatUpdate( coreSystem->TBCsystem.coating ) ;
  const ThermalData updatedThermal = sliceThermalData( xC, xR, coatUpdate ) ;
  reassign( thermalData , updatedThermal ) ;

  pieAnalysis() ;
  ouputResults.addBefore( currentState ) ;

  /// optimization run
  optimizer( &info, &nfev ) ;
  //std::cout << "ended optimizer with:--- " << info  << "  " << nfev<< "\n\n";

  /// post analysis
  pieAnalysis() ;
  ouputResults.addAfter( currentState ) ;

  /// now that all data is saved - reset thermalData to fullRange
  reassign(  thermalData, *fullRangeThermalData ) ;
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
//    { diag[i++] = TBCsystem.returnVal( unknown.label() ) ; }
//  }

  ///Transform inputs
  size_t j = 0;
  for( const auto& unknown : thermalSweepSearch() )
  {
    x[j] = kx_limiter2( x[j], unknown.lowerBound(), unknown.upperBound() );
    j++;
  }

  //  std::cout << static_cast<int>(m) << "\n" <<  static_cast<int>(n) << "\n" ;
  //  for( int i = 0; i < n ; ++i)
  //  {
  //    std::cout << "this is x: "<< i << "\t" <<x[i] << "\n";
  //  }

  /// Constrained nonlinear parameter estimation
  updateBindFunc() ;
  lmdif( myReduced, static_cast<int>(m), static_cast<int>(n), x, fvec,
         Settings.ftol, Settings.xtol, Settings.gtol,
         static_cast<int>(Settings.maxfev), Settings.epsfcn, diag,
         static_cast<int>(Settings.mode), Settings.factor,
         static_cast<int>(Settings.nprint), info, nfev, fjac,
         static_cast<int>(m), ipvt, qtf, wa1, wa2, wa3, wa4 ) ;
  //std::cout << "error code:  "<< *info <<"\n\n";

  ///Final fit
  ThermalData updatedThermal = updatedFromXsearch( x ) ;
  reassign( thermalData , updatedThermal ) ;

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
