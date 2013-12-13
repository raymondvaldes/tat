#include "../Header.h"

int paramter_estimation(const size_t m, const size_t n,
                        struct parameterEstimation::settings ParaEstSetting,
                        int *info, int *nfev,
                        const struct parameter_constraints *pc_ptr, double *x,
                        class thermalAnalysisMethod::PopTea poptea,
                        const double factorMax,
                        const double factorScale, double *xpredicted)
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

  scaleDiag(ParaEstSetting.mode, n, diag, poptea );

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
      for(size_t i=0 ; i<n ; ++i)
      {
        switch ( poptea.xParametersNames[i] )
        {
          case asub :
              x[i] = x_ini(pc_ptr->a_sub_min, pc_ptr->a_sub_max);
              break;
          case E1 :
              x[i] = x_ini(pc_ptr->E_sigma_min, pc_ptr->E_sigma_max);
              break;
          case gammaEff :
              x[i] = x_ini(pc_ptr->gamma_min, pc_ptr->gamma_max);
              break;
          case R1 :
              x[i] = x_ini(pc_ptr->R1_min, pc_ptr->R1_max);
              break;
          case lambda :
              x[i] = x_ini(pc_ptr->lambda_min, pc_ptr->lambda_max);
              break;
          case R0 :
              x[i] = x_ini(pc_ptr->R0_min, pc_ptr->R0_max);
              break;
          default:
              std::cout << "\nSwitch Error!!\n";
              exit(-69);
              break;
        }
      }
    }

    for(size_t i=0; i< n; i++)
    {
        xguess[i] = x[i];
    }

    ///Transform inputs
    for(size_t i=0 ; i< n ; i++)
    {
      switch ( poptea.xParametersNames[i] )
      {
        case asub :
            x[i] = kx_limiter2(x[i],pc_ptr->a_sub_min,pc_ptr->a_sub_max);
            break;
        case E1 :
            x[i] = kx_limiter2(x[i],pc_ptr->E_sigma_min,pc_ptr->E_sigma_max);
            break;
        case gammaEff :
            x[i] = kx_limiter2(x[i], pc_ptr->gamma_min, pc_ptr->gamma_max);
            break;
        case R1 :
            x[i] = kx_limiter2(x[i],pc_ptr->R1_min,pc_ptr->R1_max);
            break;
        case lambda :
            x[i] = kx_limiter2(x[i],pc_ptr->lambda_min,pc_ptr->lambda_max);
            break;
        case R0 :
            x[i] = kx_limiter2(x[i],pc_ptr->R0_min,pc_ptr->R0_max);
            break;
        default:
            std::cout << "\nSwitch Error!!\n";
            exit(-69);
            break;
      }
    }

    ///levenberg-marquardt algorithm
    lmdif(&ThermalProp_Analysis, m, n, x, fvec, ParaEstSetting.ftol,
          ParaEstSetting.xtol, ParaEstSetting.gtol, ParaEstSetting.maxfev,
          ParaEstSetting.epsfcn, diag, ParaEstSetting.mode,
          ParaEstSetting.factor, ParaEstSetting.nprint, info, nfev, fjac, m,
          ipvt, qtf, wa1, wa2, wa3, wa4, wa5, pc_ptr, poptea);

    ///Exit Routine
    /* Sets up a condition where the total error in the phase is compared
    against a fvec Tolerance.  If the error is greater than this constant,
    then the parameter estimation algorithm is reset with a new set of
    initial guesses. This is let to run a fixed number of iterations. */
    constexpr double ExpStddev = 0;
    const double ExpVarianceEst = ExpStddev * ExpStddev;
    poptea.LMA.LMA_workspace.fvecTotal = SobjectiveLS(
                                      poptea.expSetup.laser.L_end,
                                      poptea.LMA.LMA_workspace.emissionExperimental,
                                      poptea.LMA.LMA_workspace.predicted);
    const size_t v1 = poptea.expSetup.laser.L_end - n;
    double reduceChiSquare;
    if(ExpVarianceEst ==0 )
    {
      reduceChiSquare = 100;
    }
    else
    {
      reduceChiSquare = (poptea.LMA.LMA_workspace.fvecTotal /
                         ExpVarianceEst) / v1;
    }

    if( reduceChiSquare < 2
       || ParaEstSetting.factor == factorMax
       || poptea.LMA.LMA_workspace.fvecTotal < poptea.LMA.LMA_workspace.MSETol
       )
    {

//            const bool
//            condition1 = reduceChiSquare < 2;
//            const bool
//            condition2 = ParaEstSetting.factor == factorMax;
//            const bool
//            condition3 = poptea->fvecTotal < poptea->MSETol;

//            std::cout <<  "\nexit with     "
//            << condition1 << "\t" << condition2
//            << "\t" << condition3 <<"\n";
//
//            std::cout << "\n"<<reduceChiSquare << "\t" << poptea->fvecTotal
//            << "\t" << poptea->MSETol << "\t" << factor << "\n";

      ///Transform outputs
      for(size_t i=0 ; i< n ; i++)
      {
        switch ( poptea.xParametersNames[i] )
        {
          case asub :
              poptea.TBCsystem.a_sub =
              x_limiter2(x[i], pc_ptr->a_sub_min, pc_ptr->a_sub_max);
              xpredicted[i] = poptea.TBCsystem.a_sub;
              break;
          case E1 :
              poptea.TBCsystem.optical.Emit1 =
              x_limiter2(x[i], pc_ptr->E_sigma_min,
                         pc_ptr->E_sigma_max);
              xpredicted[i] = poptea.TBCsystem.optical.Emit1;
              break;

          case gammaEff :
              poptea.TBCsystem.gamma =
              x_limiter2(x[i], pc_ptr->gamma_min, pc_ptr->gamma_max);
              xpredicted[i] = poptea.TBCsystem.gamma ;
              break;

          case R1 :
              poptea.TBCsystem.optical.R1 =
              x_limiter2(x[i], pc_ptr->R1_min, pc_ptr->R1_max);
              xpredicted[i] = poptea.TBCsystem.optical.R1;
              break;

          case lambda :
              poptea.TBCsystem.coating.lambda =
              x_limiter2(x[i], pc_ptr->lambda_min,
                         pc_ptr->lambda_max);
              xpredicted[i] = poptea.TBCsystem.coating.lambda;
              break;

          case R0 :
              poptea.TBCsystem.optical.R0 =
              x_limiter2(x[i], pc_ptr->R0_min, pc_ptr->R0_max);
              xpredicted[i] = poptea.TBCsystem.optical.R0;
              break;

          default:
              std::cout << "\nSwitch Error!!\n";
              exit(-69);
              break;
        }
      }

      poptea.TBCsystem.updateCoat();

      ///repulate predicted phase
      phase99(poptea.expSetup.laser.L_end, poptea,
              poptea.LMA.LMA_workspace.predicted);

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


void printPEstimates(const size_t N, class thermalAnalysisMethod::PopTea poptea)
{

    poptea.LMA.LMA_workspace.MSE = MSE(
          poptea.expSetup.laser.L_end,
          poptea.LMA.LMA_workspace.emissionExperimental,
          poptea.LMA.LMA_workspace.predicted);

    for(size_t j = 0 ; j < N; ++j)
    {
        switch ( poptea.xParametersNames[j] )
        {
            case asub :
                std::cout << poptea.TBCsystem.a_subEval();
                break;
            case E1 :
                std::cout << poptea.TBCsystem.optical.Emit1;
                break;
            case gammaEff :
                std::cout << poptea.TBCsystem.gammaEval();
                break;
            case R1 :
                std::cout << poptea.TBCsystem.optical.R1;
                break;
            case lambda :
                std::cout << poptea.TBCsystem.coating.lambda;
                break;
            case R0 :
                std::cout << poptea.TBCsystem.optical.R0;
                break;
            default:
                std::cout << "\nSwitch Error!!\n";
                exit(-69);
                break;
        }
        std::cout << "  ";
    }
    std::cout << std::setprecision(10) << poptea.LMA.LMA_workspace.MSE;
    std::cout << std::setprecision(6)  << "\n";

    return;
}

void ThermalProp_Analysis(int /*P*/, int N, double *x, double *fvec,
                          int * /*iflag*/,
                          const struct parameter_constraints *pc_ptr,
                          class thermalAnalysisMethod::PopTea poptea)
{
///Transform estimates from kappa space to k space based on the limits imposed
//physicalModel::labels::Name::asub;
// physicalModel::labels::Name::E1;
//    physicalModel::labels::Name::gammaEff;
//    physicalModel::labels::Name::lambda;
//    physicalModel::labels::Name::R1;

  int i = 0;
  BOOST_FOREACH(class parameterEstimation::unknown &unknown,
                poptea.LMA.unknownParameters.vectorUnknowns)
  {
    const double val =
        x_limiter2(x[i] , unknown.lowerBound(), unknown.upperBound());
    switch( unknown.label() )
    {
      case physicalModel::labels::Name::asub :
          poptea.TBCsystem.a_sub = val;
          break;
      case physicalModel::labels::Name::E1 :
          poptea.TBCsystem.optical.Emit1 = val;
          break;
      case physicalModel::labels::Name::gammaEff :
          poptea.TBCsystem.gamma = val;
          break;
      case physicalModel::labels::Name::R1 :
          poptea.TBCsystem.optical.R1 = val;
          break;
      case physicalModel::labels::Name::lambda :
          poptea.TBCsystem.coating.lambda = val;
          break;
      default:
          std::cout << "\nSwitch Error!!\n";
          exit(-68);
          break;
    }
    i++;
  }
//    exit(-2);

//  for(int i = 0; i < N; ++i)
//  {
//    switch ( poptea.xParametersNames[i] )
//    {
//      case asub :
//          poptea.TBCsystem.a_sub =
//          x_limiter2(x[i], pc_ptr->a_sub_min, pc_ptr->a_sub_max);
//          break;
//      case E1 :
//          poptea.TBCsystem.optical.Emit1 =
//          x_limiter2(x[i], pc_ptr->E_sigma_min, pc_ptr->E_sigma_max);
//          break;
//      case gammaEff :
//          poptea.TBCsystem.gamma =
//          x_limiter2(x[i], pc_ptr->gamma_min, pc_ptr->gamma_max);
//          break;
//      case R1 :
//          poptea.TBCsystem.optical.R1 =
//          x_limiter2(x[i], pc_ptr->R1_min, pc_ptr->R1_max);
//          break;
//      case lambda :
//          poptea.TBCsystem.coating.lambda =
//          x_limiter2(x[i], pc_ptr->lambda_min, pc_ptr->lambda_max);
//          break;
//      case R0 :
//          poptea.TBCsystem.optical.R0 =
//          x_limiter2(x[i], pc_ptr->R0_min, pc_ptr->R0_max);
//          break;
//      default:
//          std::cout << "\nSwitch Error!!\n";
//          exit(-68);
//          break;
//    }
//  }


///Update dependent parameters
  poptea.TBCsystem.updateCoat();

/// Estimates the phase of emission at each heating frequency
  phase99(poptea.expSetup.laser.L_end, poptea,
          poptea.LMA.LMA_workspace.predicted);

/// Evaluate Objective function
  for(size_t n = 0 ; n < poptea.expSetup.laser.L_end ; ++n )
  {
     fvec[n] =
     poptea.LMA.LMA_workspace.emissionExperimental[n] -
         poptea.LMA.LMA_workspace.predicted[n] ;
     poptea.LMA.LMA_workspace.fvec[n] = fvec[n];
  }

/// Print stuff to terminal
  poptea.LMA.LMA_workspace.MSE =
      MSE(poptea.expSetup.laser.L_end,
          poptea.LMA.LMA_workspace.emissionExperimental,
          poptea.LMA.LMA_workspace.predicted);
  printPEstimates(N, poptea);
  return;
}




