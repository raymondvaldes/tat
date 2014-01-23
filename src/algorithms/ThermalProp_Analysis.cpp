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
#include "algorithms/ThermalProp_Analysis.h"
#include "algorithms/statistical_tools.hpp"
#include "thermal/emission/phase99.hpp"
#include "math/estimation/lmdiff.hpp"
#include "math/estimation/lmdiff_helper.hpp"
#include "math/estimation/constrained.hpp"
#include "math/utility.hpp"

int paramter_estimation( const size_t m, const size_t n,
                         class math::estimation::settings ParaEstSetting,
                         int *info, int *nfev, double *x,
                         class thermal::analysis::Kernal popteaCore,
                         const double factorMax, const double factorScale,
                         double *xpredicted )
{
/*
  The parameter estimation function takes in the function, fitting parameters,
  initial guess.  If no initial guess is given then it will populate an
  initial guess based on a random distribution of the parameter range. The
  initial guess is then transformed based on the parameter estimation ranges.
  The parameter estimation employed is the levenberg-marquardt algorithm(LMA).
  The the objective function is evaluated and compared against a tolerance.
  If it is larger than the tolerance than a new initial guess will be
  initialized.  This process is repeated until the objective function
  satisfies the tolerance or the number of iterations maxes out. The final
  values are populated back into the parameter structure and the dependent
  parameters are updated.
*/
  using namespace math::estimation;
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

  scaleDiag(ParaEstSetting.mode, n, diag, popteaCore );

  double *xinitial = new double[n];
  double *xguess = new double[n];

  for(size_t i=0 ; i< n ; i++)
  {
      xinitial[i] = x[i];
  }

  ///set initial guesses
  /// TODO put in function !
  if ( fabs(x[0] - 0) < 1e-10 )
  {
    int i = 0;
    BOOST_FOREACH(class unknown &unknown,
                  popteaCore.LMA.unknownParameters.vectorUnknowns)
    {
      x[i++] = math::x_ini( unknown.lowerBound(), unknown.upperBound() );
    }
  }

  for(size_t i=0; i< n; i++)
  {
    xguess[i] = x[i];
  }

  ///Transform inputs
  int i = 0;
  BOOST_FOREACH( class unknown &unknown,
                 popteaCore.LMA.unknownParameters.vectorUnknowns)
  {
    x[i] = kx_limiter2( x[i], unknown.lowerBound(),
                                          unknown.upperBound());
    i++;
  }

  ///levenberg-marquardt algorithm

  lmdif(&ThermalProp_Analysis, m, n, x, fvec,
                                   ParaEstSetting.ftol, ParaEstSetting.xtol,
                                   ParaEstSetting.gtol, ParaEstSetting.maxfev,
                                   ParaEstSetting.epsfcn, diag,
                                   ParaEstSetting.mode, ParaEstSetting.factor,
                                   ParaEstSetting.nprint, info, nfev, fjac, m,
                                   ipvt, qtf, wa1, wa2, wa3, wa4, wa5, popteaCore);

  ///Exit Routine
  /* Sets up a condition where the total error in the phase is compared
  against a fvec Tolerance.  If the error is greater than this constant,
  then the parameter estimation algorithm is reset with a new set of
  initial guesses. This is let to run a fixed number of iterations. */
  constexpr double ExpStddev = 0;
  const double ExpVarianceEst = ExpStddev * ExpStddev;
  popteaCore.LMA.LMA_workspace.fvecTotal = SobjectiveLS(
                                    popteaCore.expSetup.laser.L_end,
                                    popteaCore.LMA.LMA_workspace.emissionExperimental,
                                    popteaCore.LMA.LMA_workspace.predicted);
  const size_t v1 = popteaCore.expSetup.laser.L_end - n;
  double reduceChiSquare;
  if(ExpVarianceEst ==0 )
  {
    reduceChiSquare = 100;
  }
  else
  {
    reduceChiSquare = (popteaCore.LMA.LMA_workspace.fvecTotal /
                       ExpVarianceEst) / v1;
  }

  if( reduceChiSquare < 2
     || ParaEstSetting.factor == factorMax
     || popteaCore.LMA.LMA_workspace.fvecTotal < popteaCore.LMA.LMA_workspace.MSETol
     )
  {
    ///Transform outputs
    int i = 0;
    BOOST_FOREACH(class unknown &unknown,
                  popteaCore.LMA.unknownParameters.vectorUnknowns)
    {
      const double val = x_limiter2( x[i], unknown.lowerBound(),
                                     unknown.upperBound() ) ;

      popteaCore.TBCsystem.updateVal ( unknown.label() , val );
      xpredicted[i++] = val;
    }

    popteaCore.TBCsystem.updateCoat();

    ///repulate predicted phase
    thermal::emission::phase99(popteaCore, popteaCore.LMA.LMA_workspace.predicted);

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

    delete [] xinitial;
    delete [] xguess;
    return *info;

  }

  else if (ParaEstSetting.factor <= factorMax/factorScale)
  {
    ParaEstSetting.factor *=factorScale;
//            std::cout << "factor increased to "  << factor <<"\n";

  }
  else if (ParaEstSetting.factor > factorMax/factorScale &&
           ParaEstSetting.factor < factorMax)
  {
    ParaEstSetting.factor = factorMax;
    std::cout << "factor increased max "<< ParaEstSetting.factor <<"\n";
  }

  for(size_t i=0 ; i< n ; i++)
  {
    x[i] = xinitial[i];
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

  delete [] xinitial;
  delete [] xguess;

  return *info;
}


std::vector<double>
paramter_estimation(class thermal::analysis::Kernal popteaCore, int *info,
                    int *nfev)
{

/*
  The parameter estimation function takes in the function, fitting parameters,
  initial guess.  If no initial guess is given then it will populate an
  initial guess based on a random distribution of the parameter range. The
  initial guess is then transformed based on the parameter estimation ranges.
  The parameter estimation employed is the levenberg-marquardt algorithm(LMA).
  The the objective function is evaluated and compared against a tolerance.
  If it is larger than the tolerance than a new initial guess will be
  initialized.  This process is repeated until the objective function
  satisfies the tolerance or the number of iterations maxes out. The final
  values are populated back into the parameter structure and the dependent
  parameters are updated.
*/
  using namespace math::estimation;
  const size_t m = popteaCore.expSetup.laser.l_thermal.size();
  const size_t n = popteaCore.LMA.unknownParameters.vectorUnknowns.size();
  class settings ParaEstSetting = popteaCore.LMA.Settings;

  const double factorMax = popteaCore.LMA.Settings.factorMax;
  const double factorScale = popteaCore.LMA.Settings.factorScale;

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

  scaleDiag(ParaEstSetting.mode, n, diag, popteaCore );

  for(size_t i=0 ; i< n ; i++)
  {
    x[i] = popteaCore.LMA.xInitial[i];
  }

  ///set initial guesses
  /// TODO put in function !
  if ( fabs(x[0] - 0) < 1e-10 )
  {
    int i = 0;
    BOOST_FOREACH( class unknown &unknown,
                   popteaCore.LMA.unknownParameters.vectorUnknowns )
    {
      x[i++] = math::x_ini( unknown.lowerBound(), unknown.upperBound() );
    }
  }

  for(size_t i=0; i< n; i++)
  {
    popteaCore.LMA.xguessAuto[i] = x[i];
  }

  ///Transform inputs
  int i = 0;
  BOOST_FOREACH( class unknown &unknown,
                 popteaCore.LMA.unknownParameters.vectorUnknowns )
  {
    x[i] = kx_limiter2(x[i], unknown.lowerBound(), unknown.upperBound());
    i++;
  }

  ///levenberg-marquardt algorithm
  lmdif( &ThermalProp_Analysis, m, n, x, fvec, ParaEstSetting.ftol,
         ParaEstSetting.xtol, ParaEstSetting.gtol, ParaEstSetting.maxfev,
         ParaEstSetting.epsfcn, diag, ParaEstSetting.mode,
         ParaEstSetting.factor, ParaEstSetting.nprint, info, nfev, fjac, m,
         ipvt, qtf, wa1, wa2, wa3, wa4, wa5, popteaCore ) ;

  ///Exit Routine
  /* Sets up a condition where the total error in the phase is compared
  against a fvec Tolerance.  If the error is greater than this constant,
  then the parameter estimation algorithm is reset with a new set of
  initial guesses. This is let to run a fixed number of iterations. */
  constexpr double ExpStddev = 0;
  const double ExpVarianceEst = ExpStddev * ExpStddev;
  popteaCore.LMA.LMA_workspace.fvecTotal =
      SobjectiveLS( popteaCore.expSetup.laser.L_end,
                    popteaCore.LMA.LMA_workspace.emissionExperimental,
                    popteaCore.LMA.LMA_workspace.predicted);
  const size_t v1 = popteaCore.expSetup.laser.L_end - n;
  double reduceChiSquare;
  if(ExpVarianceEst ==0 )
  {
    reduceChiSquare = 100;
  }
  else
  {
    reduceChiSquare = (popteaCore.LMA.LMA_workspace.fvecTotal /
                       ExpVarianceEst) / v1;
  }

  if( reduceChiSquare < 2
     || ParaEstSetting.factor == factorMax
     || popteaCore.LMA.LMA_workspace.fvecTotal < popteaCore.LMA.LMA_workspace.MSETol
     )
  {
    ///Transform outputs
    int i = 0;
    BOOST_FOREACH(class unknown &unknown,
                  popteaCore.LMA.unknownParameters.vectorUnknowns)
    {
      const double val =
          x_limiter2(x[i], unknown.lowerBound(), unknown.upperBound());

      popteaCore.TBCsystem.updateVal ( unknown.label() , val );
      popteaCore.LMA.xpredicted[i++] = val;
    }

    popteaCore.TBCsystem.updateCoat();

    ///repopulate predicted phase
    thermal::emission::phase99(popteaCore, popteaCore.LMA.LMA_workspace.predicted);

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

    return popteaCore.LMA.xpredicted;
  }

  else if (ParaEstSetting.factor <= factorMax/factorScale)
  {
    ParaEstSetting.factor *=factorScale;
//            std::cout << "factor increased to "  << factor <<"\n";

  }
  else if (ParaEstSetting.factor > factorMax/factorScale &&
           ParaEstSetting.factor < factorMax)
  {
    ParaEstSetting.factor = factorMax;
    std::cout << "factor increased max "<< ParaEstSetting.factor <<"\n";
  }

  for(size_t i=0 ; i< n ; i++)
  {
    x[i] = popteaCore.LMA.xInitial[i];
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

  return popteaCore.LMA.xpredicted;
}


void InformationIndex(const size_t P, double *Index,
                      const size_t I, const double ki, const double *const fjac)
{
/*
    P  is the number of measurements
    N  is the number of parameters
    I  is the parameter name
    kj is the value of the parameter
*/
    for(size_t j = 0; j < P ; ++j)
    {
        Index[j] = fjac[j + P*I];
        Index[j] *= ki;
        Index[j] *= ki;
        Index[j] *= fjac[j + P*I];
        Index[j] = fabs(Index[j]);

    }

    double maxIndex = fabs(Index[0]);
    for(size_t j=0; j<P ; ++j)
    {
        if(Index[j] > maxIndex)
        {
            maxIndex = fabs(Index[j]);
        }
    }

    for(size_t j=0; j<P ; ++j)
    {
        Index[j] /= maxIndex;
    }


    return;
}

void InformationIndex(const size_t P, std::vector<double> Index,
                      const size_t I, const double ki,
                      const double* fjac)
{
/*
    P  is the number of measurements
    N  is the number of parameters
    I  is the parameter name
    kj is the value of the parameter
*/
    for(size_t j = 0; j < P ; ++j)
    {
        Index[j] = fjac[j + P*I];
        Index[j] *= ki;
        Index[j] *= ki;
        Index[j] *= fjac[j + P*I];
        Index[j] = fabs(Index[j]);

    }

    double maxIndex = fabs(Index[0]);
    for(size_t j=0; j<P ; ++j)
    {
        if(Index[j] > maxIndex)
        {
            maxIndex = fabs(Index[j]);
        }
    }

    for(size_t j=0; j<P ; ++j)
    {
        Index[j] /= maxIndex;
    }


    return;
}

void printfJac(const size_t N, const size_t P, const double*fjac)
{
/*
    P  is the number of measurements
    N  is the number of parameters
    I  is the parameter name
*/
    std::ofstream myfile;
    myfile.open("SensitivityMatrix.dat");
    myfile << std::setprecision(16);
    for(size_t j=0 ; j < P; ++j)
    {
        for(size_t i=0 ; i < N; ++i)
        {
            myfile <<  fjac[j + P*i] << "\t";
        }
        myfile << "\n";
    }

    myfile.close();

    return;
}


void printPEstimates( class thermal::analysis::Kernal popteaCore ,
                      const class physicalModel::TBCsystem TBCSystem)
{
  BOOST_FOREACH(class math::estimation::unknown &unknown,
                popteaCore.LMA.unknownParameters.vectorUnknowns)
  {
    std::cout << TBCSystem.returnVal( unknown.label() ) << "  ";
  }

  popteaCore.LMA.LMA_workspace.MSE = MSE(
        popteaCore.expSetup.laser.L_end,
        popteaCore.LMA.LMA_workspace.emissionExperimental,
        popteaCore.LMA.LMA_workspace.predicted);

  std::cout << std::setprecision(10) << popteaCore.LMA.LMA_workspace.MSE;
  std::cout << std::setprecision(6)  << "\n";

  return;
}

void ThermalProp_Analysis( int /*P*/, int /*N*/, double *x, double *fvec,
                           int * /*iflag*/,
                           class thermal::analysis::Kernal popteaCore)
{
  using namespace math::estimation;
  //Update parameters
  int i = 0;
  BOOST_FOREACH( class math::estimation::unknown &unknown,
                 popteaCore.LMA.unknownParameters.vectorUnknowns)
  {
    const double val =
        x_limiter2( x[i++] , unknown.lowerBound(), unknown.upperBound() );

    popteaCore.TBCsystem.updateVal( unknown.label() , val );
  }
  popteaCore.TBCsystem.updateCoat();

  // Estimates the phase of emission at each heating frequency
  thermal::emission::phase99(popteaCore, popteaCore.LMA.LMA_workspace.predicted);

/// Evaluate Objective function
  for(size_t n = 0 ; n < popteaCore.expSetup.laser.L_end ; ++n )
  {
     fvec[n] =
     popteaCore.LMA.LMA_workspace.emissionExperimental[n] -
         popteaCore.LMA.LMA_workspace.predicted[n] ;
     popteaCore.LMA.LMA_workspace.fvec[n] = fvec[n];
  }

/// Print stuff to terminal
  popteaCore.LMA.LMA_workspace.MSE =
      MSE( popteaCore.expSetup.laser.L_end,
           popteaCore.LMA.LMA_workspace.emissionExperimental,
           popteaCore.LMA.LMA_workspace.predicted );
//  printPEstimates( popteaCore ) ;
  return;
}
