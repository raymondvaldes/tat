/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
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
#include <boost/foreach.hpp>
#include <vector>
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/emission/phase99.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "math/estimation/lmdiff.hpp"
#include "math/estimation/lmdiff_helper.hpp"
#include "math/estimation/utils.hpp"
#include "math/utility.hpp"
#include "math/estimation/constrained.hpp"
#include "algorithms/ThermalProp_Analysis.h"

namespace thermal {
namespace analysis{  

Poptea::Poptea( const class Kernal coreSystem_ )
  : coreSystem( coreSystem_ ) {}

Poptea::~Poptea(void){}


void loadExperimentalData( std::vector<double> data);



//std::vector<double>
//Poptea::paramter_estimation( int *info, int *nfev )
//{

///*
//  The parameter estimation function takes in the function, fitting parameters,
//  initial guess.  If no initial guess is given then it will populate an
//  initial guess based on a random distribution of the parameter range. The
//  initial guess is then transformed based on the parameter estimation ranges.
//  The parameter estimation employed is the levenberg-marquardt algorithm(LMA).
//  The the objective function is evaluated and compared against a tolerance.
//  If it is larger than the tolerance than a new initial guess will be
//  initialized.  This process is repeated until the objective function
//  satisfies the tolerance or the number of iterations maxes out. The final
//  values are populated back into the parameter structure and the dependent
//  parameters are updated.
//*/

//  using namespace math::estimation;
//  const size_t m = coreSystem.expSetup.laser.l_thermal.size();
//  const size_t n = coreSystem.LMA.unknownParameters.vectorUnknowns.size();
//  class math::estimation::settings ParaEstSetting = coreSystem.LMA.Settings;

//  const double factorMax = coreSystem.LMA.Settings.factorMax;
//  const double factorScale = coreSystem.LMA.Settings.factorScale;

//  double *x = new double[n];

//  double *fvec = new double[m];
//  double *qtf = new double[n];
//  double *wa1 = new double[n];
//  double *wa2 = new double[n];
//  double *wa3 = new double[n];
//  double *wa4 = new double[m];
//  double *fjac = new double[m*n];
//  double *wa5 = new double[m*n];
//  int *ipvt = new int[n];
//  double *diag = new double[n];

//  scaleDiag(ParaEstSetting.mode, n, diag, coreSystem );

//  for(size_t i=0 ; i< n ; i++)
//  {
//    x[i] = coreSystem.LMA.xInitial[i];
//  }

//  ///set initial guesses
//  /// TODO put in function !
//  if ( fabs(x[0] - 0) < 1e-10 )
//  {
//    int i = 0;
//    BOOST_FOREACH( class unknown &unknown,
//                   coreSystem.LMA.unknownParameters.vectorUnknowns )
//    {
//      x[i++] = math::x_ini( unknown.lowerBound(), unknown.upperBound() );
//    }
//  }

//  for(size_t i=0; i< n; i++)
//  {
//    coreSystem.LMA.xguessAuto[i] = x[i];
//  }

//  ///Transform inputs
//  int i = 0;
//  BOOST_FOREACH( class math::estimation::unknown &unknown,
//                 coreSystem.LMA.unknownParameters.vectorUnknowns )
//  {
//    x[i] = math::estimation::kx_limiter2( x[i], unknown.lowerBound(),
//                                          unknown.upperBound() ) ;
//    i++;
//  }

//  ///levenberg-marquardt algorithm
//  math::estimation::lmdif( &ThermalProp_Analysis, m, n, x, fvec,
//                                    ParaEstSetting.ftol, ParaEstSetting.xtol,
//                                    ParaEstSetting.gtol, ParaEstSetting.maxfev,
//                                    ParaEstSetting.epsfcn, diag,
//                                    ParaEstSetting.mode, ParaEstSetting.factor,
//                                    ParaEstSetting.nprint, info, nfev, fjac, m,
//                                    ipvt, qtf, wa1, wa2, wa3, wa4, wa5,
//                                    coreSystem ) ;

//  ///Exit Routine
//  /* Sets up a condition where the total error in the phase is compared
//  against a fvec Tolerance.  If the error is greater than this constant,
//  then the parameter estimation algorithm is reset with a new set of
//  initial guesses. This is let to run a fixed number of iterations. */
//  constexpr double ExpStddev = 0;
//  const double ExpVarianceEst = ExpStddev * ExpStddev;
//  coreSystem.LMA.LMA_workspace.fvecTotal =
//      SobjectiveLS( coreSystem.expSetup.laser.L_end,
//                    coreSystem.LMA.LMA_workspace.emissionExperimental,
//                    coreSystem.LMA.LMA_workspace.predicted);
//  const size_t v1 = coreSystem.expSetup.laser.L_end - n;
//  double reduceChiSquare;
//  if(ExpVarianceEst ==0 )
//  {
//    reduceChiSquare = 100;
//  }
//  else
//  {
//    reduceChiSquare = (coreSystem.LMA.LMA_workspace.fvecTotal /
//                       ExpVarianceEst) / v1;
//  }

//  if( reduceChiSquare < 2
//     || ParaEstSetting.factor == factorMax
//     || coreSystem.LMA.LMA_workspace.fvecTotal < coreSystem.LMA.LMA_workspace.MSETol
//     )
//  {
//    ///Transform outputs
//    int i = 0;
//    BOOST_FOREACH( class math::estimation::unknown &unknown,
//                   coreSystem.LMA.unknownParameters.vectorUnknowns)
//    {
//      const double val =
//          x_limiter2(x[i], unknown.lowerBound(), unknown.upperBound());

//      coreSystem.TBCsystem.updateVal ( unknown.label() , val );
//      coreSystem.LMA.xpredicted[i++] = val;
//    }

//    coreSystem.TBCsystem.updateCoat();

//    ///repopulate predicted phase
//    thermal::emission::phase99( coreSystem,
//                                coreSystem.LMA.LMA_workspace.predicted);

//    delete [] qtf;
//    delete [] wa1;
//    delete [] wa2;
//    delete [] wa3;
//    delete [] wa4;
//    delete [] wa5;
//    delete [] ipvt;
//    delete [] fvec;
//    delete [] fjac;
//    delete [] diag;
//    delete [] x;

//    return coreSystem.LMA.xpredicted;
//  }

//  else if (ParaEstSetting.factor <= factorMax/factorScale)
//  {
//    ParaEstSetting.factor *=factorScale;
////            std::cout << "factor increased to "  << factor <<"\n";

//  }
//  else if (ParaEstSetting.factor > factorMax/factorScale &&
//           ParaEstSetting.factor < factorMax)
//  {
//    ParaEstSetting.factor = factorMax;
//    std::cout << "factor increased max "<< ParaEstSetting.factor <<"\n";
//  }

//  for(size_t i=0 ; i< n ; i++)
//  {
//    x[i] = coreSystem.LMA.xInitial[i];
//  }


//  delete [] qtf;
//  delete [] wa1;
//  delete [] wa2;
//  delete [] wa3;
//  delete [] wa4;
//  delete [] wa5;
//  delete [] ipvt;
//  delete [] fvec;
//  delete [] fjac;
//  delete [] diag;
//  delete [] x;

//  return coreSystem.LMA.xpredicted;
//}

}}
