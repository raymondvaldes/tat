#include "../Header.h"
void InformationIndex(const size_t P, const size_t N, double *Index,
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
//        Index[j] *= ki;
//        Index[j] *= ki;
//        Index[j] *= fjac[j + P*I];
        Index[j] = fabs(Index[j]);

    }

//    double maxIndex = fabs(Index[0]);
//    for(size_t j=0; j<P ; ++j)
//    {
//        if(Index[j] > maxIndex)
//        {
//            maxIndex = fabs(Index[j]);
//        }
//    }
//
//    for(size_t j=0; j<P ; ++j)
//    {
//        Index[j] /= maxIndex;
//    }


    return;
}

void InformationIndex(const size_t P, const size_t N, std::vector<double> Index,
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
//        Index[j] *= ki;
//        Index[j] *= ki;
//        Index[j] *= fjac[j + P*I];
        Index[j] = fabs(Index[j]);

    }

//    double maxIndex = fabs(Index[0]);
//    for(size_t j=0; j<P ; ++j)
//    {
//        if(Index[j] > maxIndex)
//        {
//            maxIndex = fabs(Index[j]);
//        }
//    }
//
//    for(size_t j=0; j<P ; ++j)
//    {
//        Index[j] /= maxIndex;
//    }


    return;
}

void InformationIndexAll(const size_t P, const size_t N,
                         const struct parameterStr * parametersStr)
{
//    for(size_t i = 0; i < N; ++i)
//    {
//        switch ( parametersStr->xParameters[i] )
//        {
//            case 51 :
//                 InformationIndex(P, N, parametersStr-> InformationIndex_asub,
//                                  i, parametersStr->a_sub, parametersStr->fjac);
//                break;
//            case 28 :
//                 InformationIndex(P, N, parametersStr->InformationIndex_Esigma,
//                                  i, parametersStr->E_sigma,
//                                  parametersStr->fjac);
//                 break;
//            case 50 :
//                 InformationIndex(P, N, parametersStr-> InformationIndex_gamma,
//                                  i, parametersStr->gamma, parametersStr->fjac);
//                 break;
//            case 19 :
//                 InformationIndex(P, N, parametersStr-> InformationIndex_R1, i,
//                                  parametersStr->R1, parametersStr->fjac);
//                break;
//            case 11 :
//                 InformationIndex(P, N, parametersStr-> InformationIndex_lambda,
//                                  i, parametersStr->lambda,
//                                  parametersStr->fjac);
//                 break;
//            case 8 :
//                 InformationIndex(P, N, parametersStr-> InformationIndex_Lcoat,
//                                  i, parametersStr->L_coat,
//                                  parametersStr->fjac);
//                 break;
//            case 18 :
//                 InformationIndex(P, N, parametersStr-> InformationIndex_R0, i,
//                                  parametersStr-> R0, parametersStr->fjac);
//                 break;
//            default:
//                 break;
//        }
//    }
//
//    std::ofstream myfile;
//    myfile.open("InformationIndex.dat");
//    for(size_t j = 0 ; j < P ; ++j )
//    {
//        myfile << parametersStr->l_thermal[j];
//        for(size_t i = 0 ; i < N; ++i)
//        {
//            myfile << "\t";
//            switch ( parametersStr->xParameters[i] )
//            {
//                case 51 :
//                     myfile << parametersStr-> InformationIndex_asub[j];
//                    break;
//                case 28 :
//                     myfile << parametersStr-> InformationIndex_Esigma[j];
//                     break;
//                case 50 :
//                     myfile << parametersStr-> InformationIndex_gamma[j];
//                     break;
//                case 19 :
//                     myfile << parametersStr-> InformationIndex_R1[j];
//                    break;
//                case 11 :
//                     myfile << parametersStr-> InformationIndex_lambda[j];
//                     break;
//                case 8 :
//                     myfile << parametersStr-> InformationIndex_Lcoat[j];
//                     break;
//                case 18 :
//                     myfile << parametersStr-> InformationIndex_R0[j];
//                     break;
//                default:
//                     break;
//            }
//        }
//        myfile << "\n" ;
//    }
//    myfile.close();

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


void printPEstimates(const size_t N, struct parameterStr * parametersStr)
{
    parametersStr->MSE = MSE(parametersStr->L_end,
                             parametersStr->emissionExperimental,
                             parametersStr-> predicted);
    for(size_t j = 0 ; j < N; ++j)
    {
        switch ( parametersStr->xParametersNames[j] )
        {
            case asub :
                std::cout << parametersStr-> a_sub;
                break;
            case E1 :
                std::cout << parametersStr-> E_sigma;
                break;
            case gammaEff :
                std::cout << parametersStr-> gamma;
                break;
            case R1 :
                std::cout << parametersStr-> R1;
                break;
            case lambda :
                std::cout << parametersStr-> lambda;
                break;
            case R0 :
                std::cout << parametersStr-> R0;
                break;
            default:
                std::cout << "\nSwitch Error!!\n";
                exit(-69);
                break;
        }
        std::cout << "  ";
    }
    std::cout << std::setprecision(10) << parametersStr->MSE;
    std::cout << std::setprecision(6)  << "\n";

    return;
}

void ThermalProp_Analysis(int P, int N, double *x, double *fvec, int *iflag,
                          const struct parameter_constraints *pc_ptr,
                          struct parameterStr * parametersStr)
{
/*
    There is an error in the fitting routine in that some parameter estimates
    go the the boundaries of their domain.  When this is the case and fitting
    routine detects the boundaries as low points in the algorithm.  This causes
    the parameter estimation to stop.
*/
/// Store previous iteration for future reference
    for(int i=0; i<N; i++)
    {
        parametersStr-> xParameters54[i] = x[i];
    }

///Transform estimates from kappa space to k space based on the limits imposed
    for(int i = 0; i < N; ++i)
    {

        switch ( parametersStr->xParametersNames[i] )
        {
            case asub :
                parametersStr->a_sub =
                x_limiter2(x[i], pc_ptr->a_sub_min, pc_ptr->a_sub_max);
                break;
            case E1 :
                parametersStr->E_sigma =
                x_limiter2(x[i], pc_ptr->E_sigma_min, pc_ptr->E_sigma_max);
                break;
            case gammaEff :
                parametersStr->gamma =
                x_limiter2(x[i], pc_ptr->gamma_min, pc_ptr->gamma_max);
                break;
            case R1 :
                parametersStr->R1 =
                x_limiter2(x[i], pc_ptr->R1_min, pc_ptr->R1_max);
                break;
            case lambda :
                parametersStr->lambda =
                x_limiter2(x[i], pc_ptr->lambda_min, pc_ptr->lambda_max);
                break;
            case R0 :
                parametersStr->R0 =
                x_limiter2(x[i], pc_ptr->R0_min, pc_ptr->R0_max);
                break;
            default:
                std::cout << "\nSwitch Error!!\n";
                exit(-68);
                break;
        }
    }

///Update dependent parameters
    parameters_update(parametersStr, N);

/// Estimates the phase of emission at each heating frequency
    const size_t lends = parametersStr->L_end;
    phase99(lends, parametersStr, parametersStr->predicted);

/// Evaluate Objective function
    for(size_t n = 0 ; n < lends ; ++n )
    {
       fvec[n] =
       parametersStr->emissionExperimental[n] - parametersStr->predicted[n] ;
       parametersStr->fvec[n] = fvec[n];
    }

/// Print stuff to terminal
    parametersStr->MSE = MSE(lends, parametersStr->emissionExperimental,
                             parametersStr->predicted);
    printPEstimates(N, parametersStr);

    return;
}
