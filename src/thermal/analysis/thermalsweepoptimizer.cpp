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
#include <string>
#include "thermal/analysis/thermalsweepoptimizer.hpp"
#include "math/estimation/constrained.hpp"
#include "math/utility.hpp"
#include "math/numIntegration/gslfunc.hpp"
#include "math/estimation/lmdiff.hpp"
#include "tools/interface/exportfile.hpp"
#include "thermal/emission/phase99.hpp"
#include "thermal/define/lthermal.h"

namespace thermal{
namespace analysis{

ThermalSweepOptimizer::ThermalSweepOptimizer(
    const math::estimation::settings &Settings_in,
    const ThermalData &thermalData_in,
    const math::estimation::unknownList &unknownParameters_,
    const std::shared_ptr< LMA > &bestfitMethod_in,
    const std::shared_ptr< PIE > &intervalEstimates_in,
    const math::estimation::unknownList thermalSweepSearch_in,
    const std::vector<thermal::model::labels> sweepOptimizationGoal_in,
    const sensible::layer coating, const size_t iter_in)
  : LMA_BASE( Settings_in, unknownParameters_, thermalData_in.size() ) ,
    bestfitMethod( bestfitMethod_in ),
    intervalEstimates( intervalEstimates_in ),
    thermalSweepSearch( thermalSweepSearch_in ),
    sweepOptimizationGoal( sweepOptimizationGoal_in ),
    coatingTOinterpretFullRange( new sensible::layer( coating )),
    xSweep(0.5,0.5),
    iter(iter_in)
{
  updateWorkSpace( thermalSweepSearch_in, sweepOptimizationGoal_in );
}

ThermalSweepOptimizer::~ThermalSweepOptimizer( void ) {}

std::pair< double, double > ThermalSweepOptimizer::updateSweep( void )
{
  using std::make_pair;

  double thermalCenter = 0;
  double thermalRange = 0;
  using thermal::model::labels;
  

  for( const auto& unknown : thermalSweepSearch() )
  {
    const double bestfit  = unknown.bestfit();
    if ( unknown.label() == labels::Name::thermalCenter  )
      thermalCenter = bestfit ;
    else if ( unknown.label() == labels::Name::thermalRange  )
      thermalRange = bestfit ;
  }

  return make_pair( thermalCenter, thermalRange ) ;
}


ThermalData ThermalSweepOptimizer::updatedFromXsearch(  double *x )
{
  //std::cout << "precheck3 " <<x[0] << "\t" << x[1] << " here3\n";

  //Update parameters with current bestfits by transforming x
  using math::estimation::unknownList;
  using math::estimation::x_limiter2;
  using sensible::layer;

  unknownList updatedInput;
  size_t i = 0;
  for( auto& unknown : thermalSweepSearch() ) {
    const double val = x_limiter2( x[i++] , unknown.lowerBound(),
                                            unknown.upperBound() );
//    std::cout << val << "\t ";
    unknown.bestfitset( val ) ;
    updatedInput.addUnknown( unknown ) ;
  }
  thermalSweepSearch( updatedInput() ) ;
  

  ///Load these to slice the thermal Data
  xSweep = updateSweep() ;
  
  //std::cout  <<xSweep.first << "\t" << xSweep.second  << "\n";


  const double xCenter = xSweep.first ;
  const double xRange = xSweep.second ;
  const layer coatUpdate( coreSystem->TBCsystem.coating ) ;
  
 // std::cout << "check3 " <<xCenter << "\t" << xRange << " here3\n";
  return sliceThermalData( xCenter, xRange, coatUpdate ) ;
}

void ThermalSweepOptimizer::resize_ThermalCenterRange( double*x )
{
  const double center = x[0];
  const double range = x[1];

  const double strPos = center - range/2;
  const double endPos = center + range/2;

//  const double tol = 0.0001;

  if( strPos < 0 || endPos > 1  )
  {
    double range_new;
    
    if ( strPos < 0 )
    {
      range_new = 2 * center - .2 ;
    }
    else
    {
      range_new = 1.8 - 2 * center;
    }
    
    x[1] = range_new;

  }
  
}



void ThermalSweepOptimizer::pieAnalysis(void)
{
//  std::cout << "\nnow:\n";
  intervalEstimates->solve( unknownParameters , thermalData , coreSystem ,
                            bestfitMethod ) ;
  coreSystem->updatefromBestFit( (*unknownParameters)() ) ;
  captureState( coreSystem->TBCsystem.coating ) ;
}



double ThermalSweepOptimizer::
penalty( const std::pair<double, double>  thermalCenterRange ,
         const double scale )
{
  using std::pow;
  using std::abs;
  using std::ceil;

  const double center = thermalCenterRange.first;
  const double range = thermalCenterRange.second;

  const double strPos = center - range / 2.;
  const double endPos = center + range / 2.;

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
    error += abs( errorModifier * scale * 10 ) ;
    
    std::cout << strPos << "\t" << endPos << "\t" << error << "\n";

  }

  return error;
}


void ThermalSweepOptimizer::updateWorkSpace( const size_t Lend, const size_t N )
{
  LMA_workspace.updateArraySize( Lend , N );
}

void ThermalSweepOptimizer::updateWorkSpace(
    const math::estimation::unknownList &thermalSweepSearch_in,
    const std::vector<thermal::model::labels> &sweepOptimizationGoal_in)
{
  const size_t Lend = sweepOptimizationGoal_in.size();
  const size_t N = thermalSweepSearch_in.size();
  updateWorkSpace( Lend, N ) ;
}

void ThermalSweepOptimizer::OptimizerOutput::
addBefore( const ExperimentAnalysisState &input,
           const std::shared_ptr<ThermalData> &thermalData  )
{
  reassign( results.before , input ) ;
  results.preFitted = thermalData ;
}

void ThermalSweepOptimizer::OptimizerOutput::
addAfter( const ExperimentAnalysisState &input,
          const std::shared_ptr<Kernal> &coreSystem  )
{
  ///This saves the 'after' state.
  reassign( results.after , input ) ;

  ///This creates a full-range sweep of the model
  results.postFitted = results.preFitted;

  using thermal::emission::phase99;
  results.postFitted->predictedEmission =
      phase99( *(coreSystem) , results.postFitted->omegas ) ;
}

void ThermalSweepOptimizer::OptimizerOutput::clear( void )
{
  searchPath.clear() ;
}

void ThermalSweepOptimizer::OptimizerOutput::pp2Folder(const std::string path ,
                                                       const std::string i)
{
  using tools::interface::exportfile;
  using std::string;

  results.prettyPrint( path );

  const string searchOutput = searchPath.prettyPrint() ;
  const string fullPath = path + "/" + "optimizerPath"+ i +".dat";

  exportfile( fullPath , searchOutput ) ;


  const string fullSweep =
      results.postFitted->prettyPrint( *(searchPath.coating_final) );
  const string fullSweepfile = path + "/" + "optiSweep.dat" ;
  exportfile( fullSweepfile, fullSweep );
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
prettyPrint( const std::string folder )
{
  using std::string;
  using filesystem::makeDir;

  const string pre = "before" ;
  const string fullPathpre = folder + "/" + pre;
  makeDir( folder , pre ) ;
  before->ppExportAll( fullPathpre ) ;


  const string post = "after" ;
  const string fullpathPost = folder + "/" + post;
  makeDir( folder , post ) ;
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

//void ThermalSweepOptimizer::upSweepStartReset( void )
//{
//  bool pass = false;
//
//  while( !pass )
//  {
//    thermalSweepSearch.resetBestfits() ;
//    pass = math::checkLimits( thermalSweepSearch.vectorUnknowns[0].initialVal() ,
//                              thermalSweepSearch.vectorUnknowns[1].initialVal() ) ;
//
//  }
//
//
//}



std::string ThermalSweepOptimizer::montecarloMap()
{
  using std::cout;
  using std::pair;

  // Optimization process and then best-fit Info!!!
  // The purpose here is to get the "best possible fit" and use that as my ref.
  cout << "starting monte carlo method....  \n";

//  solve( unknownParameters_in, thermalData_in, coreSystem_in, bestfitMethod_in,
//         intervalEstimates_in ) ;
//  bestfitMethod_in->solve( unknownParameters, thermalData_in, coreSystem_in ) ;
  reassign ( unknownBestFit , *unknownParameters  ) ;
  coreSystem->updatefromInitial( (*unknownParameters)() );

  reassign( coatingTOinterpretFullRange, coreSystem->TBCsystem.coating  ) ;

  //sweep constraints
  const double lmin_bound = 0.01 ;
  const double lmax_bound = 10 ;
  const pair<double, double>thermalLimits( lmin_bound, lmax_bound ) ;


  //This function will output a table of values from maping out
//  constexpr double min = 0 ;
//  constexpr double max = 1 ;
  ouputResults.clear() ;

  for( size_t i = 0; i < iter ; ++i )
  {
    ///create random start points and transform them
    typedef pair<double, double > pairDD ;
    pairDD thermalCenDec;
    pairDD slicedThermalLimits;

    using math::random_CR_from_limits;
    const pairDD x_initial_CR = random_CR_from_limits( thermalLimits ) ;
    
  //  std::cout << x_initial_CR.first << "\t" << x_initial_CR.second << "\t" << CRinTHERMALSPACE.first << "\t" << CRinTHERMALSPACE.second << "\n";
//ERROR IN CODE - PRODUCING CR BUT I NEED IT PRESENTED IN TERMS OF DATA %
    /// transform it into something thermal_prop can understand
    double x[2] = { 0 } ;
    x[0] = x_initial_CR.first ;
    x[1] = x_initial_CR.second ;

    using math::estimation::kx_limiter2;
    x[0] = kx_limiter2( x[ 0 ], 0, 1 ) ;
    x[1] = kx_limiter2( x[ 1 ], 0, 1 ) ;

    //std::cout << lminmax.first << "\t" << lminmax.second;
    //std::cout << "\t" <<x_initial_CR.first << "\t" << x_initial_CR.second<< "\n" ;

    double fvec[2] = {0} ;
    ThermalProp_Analysis( x , fvec ) ;

    ///reset unknown parameters
    reassign( unknownParameters , *unknownBestFit ) ;
    coreSystem->updatefromInitial( (*unknownBestFit)() );
  }


  std::ostringstream output;

  output << "#|-------------------------------------------------------------\n";
  output << "#| Contour Map of Experimental Optimization                    \n";
  output << "#|                                                             \n";
  output << "#| columns...                                                  \n";
  output << "#| lthermal center  :                                          \n";
  output << "#| lthermal decade  :                                          \n";
  output << "#| lthermal min     :                                          \n";
  output << "#| lthermal max     :                                          \n";
  output << "#| omega lowerbound :                                          \n";
  output << "#| omega upperbound :                                          \n";
  output << "#| mean parameter error  :                                     \n";
  output << "#|                                                             \n";
  output << "#|-------------------------------------------------------------\n";

  const double kcond = coatingTOinterpretFullRange->kthermal.offset;
  const double psi = coatingTOinterpretFullRange->psithermal.offset;
  const double length = coatingTOinterpretFullRange->depth;


  for( OptimizerOutput::ExperimentAnalysisState&state :
       ouputResults.searchPath.path )
  {
    const double omegafirst = state.omegaLimits.first;
    const double omegasecond = state.omegaLimits.second;

    using define::lthermal;
    const double lmin = lthermal( length, kcond, psi, omegafirst ) ;
    const double lmax = lthermal( length, kcond, psi, omegasecond );

    using std::pair;
    const pair<double, double > lthermCenDec =math::xCenterlog10( lmin, lmax );

    output <<
    lthermCenDec.first                  << "\t" <<
    lthermCenDec.second                 << "\t" <<
    lmin                                << "\t" <<
    lmax                                << "\t" <<
    omegafirst                          << "\t" <<
    omegasecond                         << "\t" <<
    state.meanParameterError            << "\n";
  }
  return output.str();

}

void ThermalSweepOptimizer::captureState( const sensible::layer &coat )
{
  currentState.lthermalLimits = thermalData->get_lthermalLimits( coat ) ;
  currentState.lthermalCenterDecades =
      math::xCenterlog10( currentState.lthermalLimits.first,
                          currentState.lthermalLimits.second );

  currentState.omegaLimits = thermalData->get_omegaLimits();

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

  // Save true coating and fullrange thermal data
  reassign( coatingTOinterpretFullRange, coreSystem->TBCsystem.coating ) ;
  fullRangeThermalData = thermalData ;

  /// pre analysis on full-range
  {
    const double xC = .5 ;
    const double xR = 1 ;

    using sensible::layer;
    const layer coatUpdate( coreSystem->TBCsystem.coating ) ;
    const ThermalData updatedThermal = sliceThermalData( xC, xR, coatUpdate ) ;
    reassign( thermalData , updatedThermal ) ;
  }
  
  pieAnalysis() ;
  ouputResults.addBefore( currentState , thermalData ) ;

  /// optimization run
  optimizer( &info, &nfev ) ;
  std::cout << "ended optimizer with:--- " << info  << "  " << nfev<< "\n\n";

  /// post analysis
  pieAnalysis() ;
  ouputResults.addAfter( currentState, coreSystem ) ;
  reassign(ouputResults.searchPath.coating_final,coreSystem->TBCsystem.coating);

  /// now that all data is saved - reset thermalData to fullRange
  reassign(  thermalData, *fullRangeThermalData ) ;
}

ThermalData ThermalSweepOptimizer::sliceThermalData(
    const double xCenter, const double xRange,
    const sensible::layer updatedCoating )
{
  using std::pair;
  using std::vector;
  using std::reverse_copy;
  using std::begin;
  using std::end;
  
  using math::numIntegration::mySpline;
  using math::newThermalSweepLimits;
  using define::lthermal;


  // Establish omegas limits of full range (FR) experimental data
  const pair<double, double>
    omegaLimits = fullRangeThermalData->get_omegaLimits( ) ;

  vector<double> omegasMonoIncreasing( fullRangeThermalData->size() ) ;
  reverse_copy(
        begin( fullRangeThermalData->omegas ),
        end( fullRangeThermalData->omegas ),
        begin( omegasMonoIncreasing ) ) ;

  vector<double> emissionReversed( fullRangeThermalData->size() ) ;
  reverse_copy(
        begin( fullRangeThermalData->experimentalEmission ),
        end( fullRangeThermalData->experimentalEmission ),
        begin( emissionReversed ) ) ;

  const mySpline experimentalEmissionInterpolater(
      omegasMonoIncreasing.data(),
      emissionReversed.data(),
      omegasMonoIncreasing.size() ) ;

  // Use omega to derive current lthermalsLimits that correspond to FullRange
  const double coatingLength = updatedCoating.depth;
  const double coatingK = updatedCoating.kthermal.offset;
  const double coatingPsi = updatedCoating.psithermal.offset;

  const pair<double, double> thermalLimits(
  lthermal( coatingLength, coatingK,  coatingPsi, omegaLimits.first  ) ,
  lthermal( coatingLength, coatingK,  coatingPsi, omegaLimits.second ) ) ;

  // Take a slice of thermalData range based on updated limits and xC,xR
  const pair<double, double> slicedThermalLimits =
  newThermalSweepLimits( xCenter, xRange, thermalLimits ) ;

  const double lmin = slicedThermalLimits.first ;
  const double lmax = slicedThermalLimits.second ;
  const size_t lminPerDecarde = fullRangeThermalData->measurementsPerDecade;

  // Create vector of lthermals for my slice of data
  ThermalData output( lmin , lmax , lminPerDecarde, updatedCoating ) ;
  vector<double> sliceEmission( output.size() ); /*output.size() */

  size_t i = 0;
  for( auto& omega : output.omegas )
    sliceEmission[i++] =   experimentalEmissionInterpolater.eval( omega );
  
  output.updateExperimental( sliceEmission );

  return output;
}

void ThermalSweepOptimizer::optimizer( int *info, int *nfev )
{
  using std::vector;

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
  double *diag = new double[n]();

  ///populate initial values
  vector<double> xInitial(0) ;
  for( const auto &unknown : thermalSweepSearch() )
    xInitial.push_back( unknown.initialVal() );
  
  for( size_t i=0 ; i< n ; i++ )
  {
      x[i] = xInitial[i];
      ipvt[i] = 9;
   // std::cout << x[i] << "\n" ;
  }

  x[0] = 0.52;
  x[1] = 0.90;

  ///Transform inputs
  size_t j = 0;
  for( const auto& unknown : thermalSweepSearch() )
  {
    //std::cout << x[j] << "\t";
    x[j] = kx_limiter2( x[j], unknown.lowerBound(), unknown.upperBound() );
    //std::cout << unknown.lowerBound() << "\t" << unknown.upperBound() << "\t";
    //std::cout << x[j] << "\n";
    j++;
  }
  

  /// Constrained nonlinear parameter estimation
  updateBindFunc() ;

  Settings.mode = 1;
  Settings.epsfcn = .01;
  Settings.factor = 1;
  Settings.gtol = .00001;

  lmdif( myReduced, static_cast<int>(m), static_cast<int>(n), x, fvec,
         Settings.ftol, Settings.xtol, Settings.gtol,
         static_cast<int>(Settings.maxfev), Settings.epsfcn, diag,
         static_cast<int>(Settings.mode), Settings.factor,
         static_cast<int>(Settings.nprint), info, nfev, fjac,
         static_cast<int>(m), ipvt, qtf, wa1, wa2, wa3, wa4 ) ;
  std::cout << "error code:  "<< *info <<"\n\n";

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

void ThermalSweepOptimizer::ThermalProp_Analysis( double *x, double *fvec )
{
  using std::sqrt;
  using std::pow;
  using math::estimation::unknown;

//  if ( penalty( xSweep ) > 0 )
//  {
//    std::cout << "before  " << x[0] << "\t" << x[1] << "\n";
//    resize_ThermalCenterRange( x ) ;
//    std::cout << "after  " << x[0] << "\t" << x[1] << "\n";
//  }

  // update experimental data used based on search
  //std::cout << x[0] << "\t" << x[1] << "\t";
  ThermalData updatedThermal = updatedFromXsearch( x ) ;
  
  //std::cout << x[0] << "\t" << x[1] << "\t";
  reassign( thermalData , updatedThermal ) ;

  // Parameter Estimation with PIE analysis
  pieAnalysis();

  ///Use results from anaylsis
  size_t i = 0 ;
  currentState.meanParameterError = 0;
  for( thermal::model::labels& myParam : sweepOptimizationGoal )
  {
    double error = 0 ;

    for ( unknown& unknown: (*unknownParameters)() )
    {
      if ( myParam.getName() == unknown.label() )
      {
        error = unknown.bestfitIntervalSpread();
      }
    }
    currentState.meanParameterError += error ;

    error += penalty( xSweep , error);
    fvec[i] = error ;
    i++;
  }

  
  currentState.meanParameterError /= sweepOptimizationGoal.size();
  
  std::cout
            << thermalSweepSearch.vectorUnknowns[0].bestfit() << "\t"
            << thermalSweepSearch.vectorUnknowns[1].bestfit() << "\t"
            << x[0] << "\t" << x[1] << "\t"
            << currentState.meanParameterError << "\t"
          //  <<fvec[0] << "\t" << fvec[1] << "\t" <<
         //   xSweep.first << "\t" << xSweep.second
            << "\n";
  

  ouputResults.push_back( currentState ) ;
  
  
  return;
}


}}
