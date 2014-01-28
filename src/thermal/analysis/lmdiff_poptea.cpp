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

#include "math/statistical_tools.hpp"
#include "math/estimation/constrained.hpp"
#include "math/estimation/utils.hpp"
#include "math/utility.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/emission/phase99.hpp"

namespace thermal {
namespace analysis{


LMA::LMA(const math::estimation::settings &Settings_,
          const math::estimation::unknownList &unknownParameters_,
          const size_t Lend_, const ThermalData &thermalData_)
  : thermalData(thermalData_), Settings(Settings_),
    unknownParameters(unknownParameters_),
    LMA_workspace( Lend_, unknownParameters_.Nsize() )
{

}

LMA::~LMA(void){}

void LMA::updateUnknownParameters(
    const std::vector< class math::estimation::unknown > &unknownList_ )
{
  std::vector<class math::estimation::unknown> updated(unknownList_);
  unknownParameters.vectorUnknowns.swap( updated );

  const size_t Default = LMA_workspace.emissionNominal.size();
  updateWorkSpace( Default, updated.size() ) ;
}

void LMA::updateWorkSpace( const size_t Lend, const size_t N )
{
  LMA_workspace.updateArraySize( Lend , N );
}


void LMA::updateThermalData( class ThermalData thermalData_ )
{
  thermalData = thermalData_;
}

std::vector<double>
LMA::paramter_estimation( int *info, int *nfev,  Kernal &coreSystem,
                          const ThermalData &thermalData_ )
{
  updateThermalData( thermalData_ );
  std::vector<double>xInitial;
  for( const auto &unknown : unknownParameters.vectorUnknowns )
  {
    xInitial.push_back( unknown.initialVal() );
  }

  using namespace math::estimation;
  const size_t m = thermalData.omegas.size();
  const size_t n = unknownParameters.Nsize();
  std::vector<double> xpredicted(n);  //FIX THIS TODO BUG
  std::vector<double> xguessAuto(n);  //FIX THIS TODO BUG

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

  scaleDiag( diag, unknownParameters , coreSystem.TBCsystem,
             Settings.mode ) ;

  for(size_t i=0 ; i< n ; i++)
  {
    x[i] = xInitial[i];
  }

  ///set initial guesses
  if ( fabs(x[0] - 0) < 1e-10 )
  {
    int i = 0; 
    for( const auto& unknown : unknownParameters.vectorUnknowns )
    {
      x[i++] = math::x_ini( unknown.lowerBound(), unknown.upperBound() );
    }
  }

  for(size_t i=0; i< n; i++)
  {
    xguessAuto[i] = x[i];
  }

  ///Transform inputs
  int i = 0;
  for( const auto& unknown : unknownParameters.vectorUnknowns )
  {
    x[i] = kx_limiter2( x[i], unknown.lowerBound(), unknown.upperBound() ) ;
    i++;
  }

  ///levenberg-marquardt algorithm
  lmdif( myReduced , m, n, x, fvec, Settings.ftol,
         Settings.xtol, Settings.gtol, Settings.maxfev,
         Settings.epsfcn, diag, Settings.mode,
         Settings.factor, Settings.nprint, info, nfev, fjac, m,
         ipvt, qtf, wa1, wa2, wa3, wa4, wa5, coreSystem ) ;

  ///Exit Routine
  /* Sets up a condition where the total error in the phase is compared
  against a fvec Tolerance.  If the error is greater than this constant,
  then the parameter estimation algorithm is reset with a new set of
  initial guesses. This is let to run a fixed number of iterations. */

  LMA_workspace.fvecTotal =
      math::estimation::SobjectiveLS( thermalData.omegas.size(),
                                      LMA_workspace.emissionExperimental,
                                      LMA_workspace.predicted);

  i = 0;
  for( auto& unknown : unknownParameters.vectorUnknowns )
  {
    unknown.bestfitset( x[i] ) ;
    xpredicted.push_back( x[i] ) ;
    x[i++] = math::x_ini( unknown.lowerBound(), unknown.upperBound() );
  }

  for(size_t i=0 ; i< n ; i++)
  {
    x[i] = xInitial[i];
  }


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

  return xpredicted;
}


void LMA::ThermalProp_Analysis( int /*P*/, int /*N*/, double *x, double *fvec,
                                int * /*iflag*/,
                                class thermal::analysis::Kernal popteaCore)
{
  using namespace math::estimation;

  //Update parameters
  int i = 0;
  for( const auto& unknown :  unknownParameters.vectorUnknowns)
  {
    const double val =
        x_limiter2( x[i++] , unknown.lowerBound(), unknown.upperBound() );

    popteaCore.TBCsystem.updateVal( unknown.label() , val );
  }
  popteaCore.TBCsystem.updateCoat();

  // Estimates the phase of emission at each heating frequency
  LMA_workspace.predicted = thermal::emission::phase99( popteaCore,
                                                        thermalData.omegas );

  /// Evaluate Objective function
  for( size_t n = 0 ; n < thermalData.omegas.size() ; ++n )
  {
     fvec[n] = abs( LMA_workspace.emissionExperimental[n] -
                    LMA_workspace.predicted[n] );
//     LMA_workspace.fvec[n] = fvec[n];
  }

/// Print stuff to terminal
//  LMA_workspace.MSE =
//      MSE( thermalData.omegas.size() ,
//           LMA_workspace.emissionExperimental,
//           LMA_workspace.predicted );

  printPEstimates( popteaCore.TBCsystem, unknownParameters ) ;
  return;
}

}
}

void printPEstimates( const class physicalModel::TBCsystem TBCSystem,
                      math::estimation::unknownList list )
{
  for( const auto& unknown : list.vectorUnknowns)
  {
    std::cout << TBCSystem.returnVal( unknown.label() ) << "  ";
  }

  std::cout << "\n";
  return;
}
