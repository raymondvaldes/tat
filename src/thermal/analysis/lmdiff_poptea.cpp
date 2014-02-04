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
#include <functional>
#include <cstddef>
#include <vector>
#include <boost/foreach.hpp>
#include <iostream>

#include "math/estimation/lmdiff.hpp"
#include "math/statistical_tools.hpp"
#include "math/estimation/constrained.hpp"
#include "math/estimation/utils.hpp"
#include "math/utility.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/emission/phase99.hpp"

namespace thermal {
namespace analysis{

LMA_BASE::LMA_BASE( const math::estimation::settings &Settings_,
                    const math::estimation::unknownList &unknownParameters_,
                    const size_t Lend_ )
  : Settings(Settings_), LMA_workspace( Lend_, unknownParameters_.size() )
{}



void LMA_BASE::updateBindFunc( void )
{
  myReduced =
  std::bind( &LMA_BASE::ThermalProp_Analysis, this , std::placeholders::_1,
             std::placeholders::_2, std::placeholders::_3) ;
}

void LMA::updateWorkSpace( const size_t Lend, const size_t N )
{
  LMA_workspace.updateArraySize( Lend , N );
}


LMA::LMA( const math::estimation::settings &Settings_,
          const math::estimation::unknownList &unknownParameters_,
          const size_t Lend_ )
  : LMA_BASE( Settings_, unknownParameters_, Lend_ )
{}

LMA::~LMA(void){}





void LMA::solve(
    std::shared_ptr< math::estimation::unknownList > &unknownParameters_in,
    std::shared_ptr< ThermalData > &thermalData_in,
    std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  unknownParameters = unknownParameters_in;
  thermalData = thermalData_in;
  coreSystem = coreSystem_in;

  ///update workspaces
  updateWorkSpace( thermalData->size() , unknownParameters->size()  );

  ///Solve
  paramter_estimation( &info, &nfev );
}


class ThermalData
LMA::paramter_estimation( int *info, int *nfev )
{
  using namespace math::estimation;
  const size_t m = thermalData->omegas.size();
  const size_t n = unknownParameters->size();

  ///Create workspaces
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
  std::vector<double> xInitial(0);

  for( const auto &unknown : (*unknownParameters)() )
    { xInitial.push_back( unknown.initialVal() ); }
  for( size_t i=0 ; i< n ; i++ )
    { x[i] = xInitial[i]; }

  scaleDiag( diag, *unknownParameters , coreSystem->TBCsystem,
             Settings.mode ) ;

  ///Transform inputs
  int j = 0;
  for( const auto& unknown : (*unknownParameters)() )
  {
    x[j] = kx_limiter2( x[j], unknown.lowerBound(), unknown.upperBound() );
    j++;
  }

  ///levenberg-marquardt algorithm
  updateBindFunc();
  math::estimation::lmdif( myReduced , m, n, x, fvec, Settings.ftol,
                           Settings.xtol, Settings.gtol, Settings.maxfev,
                           Settings.epsfcn, diag, Settings.mode,
                           Settings.factor, Settings.nprint, info, nfev, fjac,
                           m, ipvt, qtf, wa1, wa2, wa3, wa4, wa5,
                           *coreSystem ) ;

  //Transform outputs
  j=0;
  for( auto& unknown : (*unknownParameters)() )
  {
    x[j] = x_limiter2(x[j], unknown.lowerBound(), unknown.upperBound());
    unknown.bestfitset(x[j]);
    j++;
  }

   ///Final fit
  coreSystem->updatefromBestFit( (*unknownParameters)() );
  thermalData->predictedEmission =
      thermal::emission::phase99( *coreSystem , thermalData->omegas );

  /// Quality-of-fit
  thermalData->MSE = math::estimation::SobjectiveLS(
        thermalData->experimentalEmission, thermalData->predictedEmission );

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

  return *thermalData;
}


void LMA::ThermalProp_Analysis( double *x, double *fvec,
                                class thermal::analysis::Kernal &popteaCore )
{
  //Update parameters
  math::estimation::unknownList updatedInput;
  int i = 0;
  for( auto& unknown :  (*unknownParameters)() )
  {
    const double val = math::estimation::
        x_limiter2( x[i++] , unknown.lowerBound(), unknown.upperBound() );
    unknown.bestfitset( val );
    updatedInput.addUnknown(unknown);
  }

  (*unknownParameters)( updatedInput() );
  popteaCore.updatefromBestFit( (*unknownParameters)()  );

  // Estimates the phase of emission at each heating frequency
  thermalData->predictedEmission =
      thermal::emission::phase99( popteaCore, thermalData->omegas );

  /// Evaluate Objective function
  for( size_t n = 0 ; n < thermalData->omegas.size() ; ++n )
  {
     fvec[n] =  thermalData->experimentalEmission[n] -
                    thermalData->predictedEmission[n] ;
  }

  thermalData->MSE =
      math::estimation::SobjectiveLS( thermalData->experimentalEmission,
                                      thermalData->predictedEmission );
  printPEstimates( popteaCore.TBCsystem, *unknownParameters ) ;

  return;
}




//void methods::Optimization_Analysis( double *x, double *fvec,
//                                     class thermal::analysis::Kernal &popteaCore )
//{
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

//  return;
//}




void ThermalSweepOptimizer::solve(
    std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
    std::shared_ptr<ThermalData> &thermalData_in,
    std::shared_ptr<Kernal> &coreSystem_in)
{


//  ///Define experimental "operability domain"
//  ///This is the section of my code where I have figured out what lmin and lmax
//  /// is. At this point I am assuming that the experimental data has been loaded
//  /// and a best fit has been done on the parameters.  The new lthermals are
//  const std::pair<double, double> thermalOperabilityLimits =
//      thermalData->get_lthermalLimits(coreSystem->TBCsystem.coating );
//  std::cout << "thermalOperabilityLimits\t"
//            << thermalOperabilityLimits.first << "\t"
//            << thermalOperabilityLimits.second << "\n";

//  ///Define acceptable tolerance.  This is where I give it a threshold in which
//  /// it will seach for the optimal range and stop once the threshold is
//  /// satisfied.
//  const double minError = 0;

//  /// Given a center and a range can I create data from this. [TEST]
//  const double xCenter = .2;
//  const double xRange = 1;
//  const std::pair<double, double> updatedRange =
//  math::newThermalSweepLimits( xCenter, xRange, thermalOperabilityLimits );
//  std::cout << "updated range\t" << updatedRange.first << "\t"
//            << updatedRange.second << "\n";

//  const std::pair<double, double> CRfromSwweep =
//  math::CRfromSweepLimits( updatedRange.first, updatedRange.second,
//                     thermalOperabilityLimits );
//  std::cout << "updated center range\t" << CRfromSwweep.first << "\t"
//            << CRfromSwweep.second << "\n";


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




}}

void printPEstimates( const physicalModel::TBCsystem TBCSystem,
                      math::estimation::unknownList list )
{
  for( const auto& unknown : list() )
  {
    std::cout << TBCSystem.returnVal( unknown.label() ) << "  ";
  }

  std::cout << "\n";
  return;
}
