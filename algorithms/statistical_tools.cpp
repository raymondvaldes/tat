#include "../Header.h"

bool equalto(const double a, const double b)
{
    const double multi = a > b ? a : b;
    const double multi2 = multi >= 1 ? multi  : 1;

    return std::fabs(a - b) < (std::numeric_limits<double>::epsilon()) * multi2;
}

bool equalto(const double a, const int b)
{
    const double multi = a > b ? a : b;
    const double multi2 = multi > 1 ? multi  : 1;

    return std::fabs(a - b) < (std::numeric_limits<double>::epsilon()) * multi2;
}


double arrayMax(const double* x, const size_t I)
{
    double maxi = x[0];
    for(size_t i = 1; i < I ; ++i)
    {
        if(x[i] > maxi ) maxi = x[i];
    }


    return maxi;
}

double arrayMin(const double* x, const size_t I)
{
    double maxi = x[0];
    for(size_t i = 1; i < I ; ++i)
    {
        if(x[i] < maxi ) maxi = x[i];
    }

    return maxi;
}


void vector3DSetup(std::vector< std::vector< std::vector< double > > > &Vnew,
                   const size_t x, const size_t y, const size_t z)
{
    Vnew.resize(x);
    for(size_t i = 0; i < x ; ++i )
    {
        Vnew[i].resize(y);

        for(size_t j = 0; j < y ; ++j)
        {
               Vnew[i][j].resize(z);
        }
    }
}

void vector2DSetup(std::vector< std::vector< double > > &Vnew,
                   const size_t x, const size_t y)
{
    Vnew.resize(x);
    for(size_t i = 0; i < x ; ++i )
    {
        Vnew[i].resize(y);
    }
}

double rss(const double N, const double* exp, const double* x_hat)
{
    /*
        This function calculated the residual sum of squares between an
        experimental results and predicted results.
            exp         experimental results
            x_hat       predicted results
            N           number of measurements
    */
    double sum = 0;
    for(size_t n = 0; n < N ; n++)
    {
        sum += (exp[n] - x_hat[n]) * (exp[n] - x_hat[n]);
    }

    return sum;
}

//double VarianceEst(const size_t num, const size_t P, const size_t N,
//                   const double* l_thermal, struct parameterStr * parametersStr,
//                   const double stddevExperimental)
//
//{
///*
//    The estimate of the variance (sigma^2)  is obtained from the degrees of
//    freedom and the objective function. This is valid if the
//
//        S ... objective function
//        P ... number of unique measurements
//        N ... number of unknown parameters
//        num...  number of measurements used to estimate each unique measurement
//        parametersStr   ... structure with parameter values
//        stddevExperimental ...stddev used to create artificial experimental data
//        l_thermal ... values for thermal penetration used
//*/
//    double data[P][num];
//    double average[P];
//    double SSall[P][num];
//    double sum;
//
//    for(size_t n = 0 ; n < P ; ++n )
//    {
//        double temp = emission_analytical(parametersStr->lambda,
//                                          l_thermal[n], parametersStr->E_sigma,
//                                          parametersStr->gamma,
//                                          parametersStr->R1);
//        sum = 0;
//        for(size_t i = 0; i < num ; ++i)
//        {
//            data[n][i] = x_normal(temp, temp*stddevExperimental);
//            sum += data[n][i];
//        }
//        average[n] = sum / num;
//    }
//
//    sum = 0;
//    for(size_t n = 0 ; n<P ; ++n )
//    {
//        for(size_t i = 0; i < num ; ++i)
//        {
//            SSall[n][i] = pow(data[n][i] - average[n] , 2 );
//            sum += SSall[n][i];
//        }
//    }
//
//    return sum / ( P*num - N ) ;
//}



double variance(const size_t P, const size_t N, const double S)
{
    /*
        The estimate of the variance (sigma^2)  is obtained from the degrees of
        freedom and the objective function.
            S ... objective function
            P ... number of measurements
            N ... number of unknown parameters
    */
    return S / (P-N);
}

double SobjectiveLS(const size_t N, const double*emissionExp,
                    const std::vector<double>& emissionEst)
{
    /*
        The objective function is evaluated for all the measurements.
        emissionEst[n]  ...     is calculated through the model
        emissionExp[n]  ...     is determined through the experiment

    */
    double fvec_objective = 0;

    for(size_t n=0 ; n < N; n++)
    {
        fvec_objective += pow( emissionExp[n] - emissionEst[n]  , 2);
    }

    return fvec_objective;
}

double SobjectiveLS(const size_t N, const double*emissionExp,
                    const double* emissionEst)
{
    /*
        The objective function is evaluated for all the measurements.
        emissionEst[n]  ...     is calculated through the model
        emissionExp[n]  ...     is determined through the experiment

    */
    double fvec_objective = 0;

    for(size_t n=0 ; n < N; n++)
    {
        fvec_objective += pow( emissionExp[n] - emissionEst[n]  , 2);
    }

    return fvec_objective;
}

double chisquare(const size_t N, const double*emissionExp,
                    const double* emissionEst)
{
    /*
        The objective function is evaluated for all the measurements.
        emissionEst[n]  ...     is calculated through the model
        emissionExp[n]  ...     is determined through the experiment
    */

    double chisquare = 0;

    for(size_t n=0 ; n < N; n++)
    {
        chisquare += (pow( emissionExp[n] - emissionEst[n]  , 2) / emissionEst[n]);
    }
    return chisquare;
}

double Sobjective(const size_t L_end, const double*emissionExp,
                  const double* emissionNum)
{
    /*
        The objective function is evaluated for all the measurements and the
        mean square is returned.

    */
    double fvec_objective = 0;

    for(size_t n=0 ; n < L_end; n++)
    {
        fvec_objective += pow((emissionExp[n] / emissionNum[n] - 1), 2);
    }

    return sqrt(fvec_objective / L_end );
}

double MSE(const size_t N, const double* const emissionExp,
           const std::vector<double>& emissionEst)
{
    /*
        The objective function is evaluated for all the measurements and the
        mean square is returned.

    */
    double fvec_objective = 0;

    for(size_t n=0 ; n < N; n++)
    {
        fvec_objective += pow( emissionEst[n]/emissionExp[n] - 1  , 2);
    }

    return 100*(fvec_objective / N);
}

double MSE(const size_t N, const double* const emissionExp,
           const double* const emissionEst)
{
    /*
        The objective function is evaluated for all the measurements and the
        mean square is returned.

    */
    double fvec_objective = 0;

    for(size_t n=0 ; n < N; n++)
    {
        fvec_objective += pow( emissionEst[n]/emissionExp[n] - 1  , 2);
    }

    return 100*(fvec_objective / N);
}

void matrixTranspose(const size_t P, const size_t N, double*matrix)
{
    /*
       N is parameters being estimated
       P number of measurements
    */

    for(size_t j = 0 ; j < P ; ++j)
    {
        for(size_t i = 0 ; i < N ; ++i)
        {
            matrix[j+P*i] = matrix[i+j*N];
        }
    }

    return;
}

void matrixTranspose(const size_t P, const size_t N, const double*matrix,
                     double*matrixT)
{
    /*
       N is parameters being estimated
       P number of measurements
    */

    for(size_t j = 0 ; j < P ; ++j)
    {
        for(size_t i = 0 ; i < N ; ++i)
        {
            matrixT[j+P*i] = matrix[i+j*N];
        }
    }

    return;
}

void matrixDot(const double* MatrixA, const size_t rowA, const size_t columnA,
               const double* MatrixB, const size_t rowB, const size_t columnB,
               double* MatrixResultant)
{
    /*
        This is for matrices arranged in 1D with the indexes such that:
            i + m * j
                i column
                j row
                m row width

        The arguments row and column are the lengths of the row and column of the
        resultant matrix.
            MatrixResultant[row,column] = MatrixA[row,::] * MatrixB[::,column]
     */
    if(columnA != rowB)
    {
        std::cout << "\nerror with matrix size\n";
        return;
    }

    for(size_t j = 0 ; j < rowA ; ++j)
    {
        for(size_t i = 0 ; i < columnB ; ++i)
        {
            MatrixResultant[i+columnB*j] = 0;

            for (size_t k = 0; k < columnA; ++k)
            {
                MatrixResultant[i+columnB*j] +=
                    MatrixA[k + j*columnA] * MatrixB[i + columnB*k];
            }
        }
    }

    return;
}

void covarianceMatrix(const size_t N, const double variance,
                      const double* Amatrix, double* cov)
{
    /*
        The covariance matrix is the product of the variance and the jacobian
        matrix.
    */
    double* AmatrixT;
    AmatrixT = (double*)malloc(N * N * sizeof(double));
    matrixTranspose(N, N, Amatrix, AmatrixT);

    size_t ij=0;
    for(size_t j = 0 ; j < N ; ++j)
    {
        for(size_t i = 0 ; i < N ; ++i)
        {
            cov[ij] = variance * AmatrixT[ij] ; //  fjac[i+m*j]
            ij++;
        }
    }

    free(AmatrixT);
    return;
}

void standardError(const size_t N, const double *cov, double* standardError)
{
    for(size_t i=0; i<N; ++i)
    {
        standardError[i] = sqrt( cov[ i + N * i ] );
    }

    return;
}

void printVariable(const double X1, const double X2, const double X3,
                   const size_t X4)
{
    std::cout << "\n";
    std::cout << X1 << "\t"<< X2 << "\t" << X3 << "\t" << X4;
    std::cout << "\n";
    return;
}

void printArray(const double* const matrix, const size_t N)
{
    std::cout << "\n";
    for(size_t j = 0 ; j < N ; ++j)
    {
        std::cout<< matrix[j] << "\n";
    }
    std::cout << "\n";
    return;
}

void printArray(const std::vector<double> &matrix, const size_t N)
{
    std::cout << "\n";
    for(size_t j = 0 ; j < N ; ++j)
    {
        std::cout<< matrix[j] << "\n";
    }
    std::cout << "\n";
    return;
}

void printArray2d(const size_t N, const size_t M, const double* const matrix)
{
    for(size_t j = 0 ; j < M ; ++j)
    {
        for(size_t i = 0 ; i < N ; ++i)
        {
            std::cout<< matrix[i+N*j] << "\t";
        }
        std::cout << "\n";
    }
    return;
}

void printArray2d(const size_t N, const size_t M,
                  const std::vector<std::vector<double>>& matrix)
{
    for(size_t j = 0 ; j < M ; ++j)
    {
        for(size_t i = 0 ; i < N ; ++i)
        {
            std::cout<< matrix[j][i]<< "\t";
        }
        std::cout << "\n";
    }
    return;
}

void Amatrix(const size_t P, const size_t N, const double*fjac, double* Amatrix)
{
    /*
        The A matrix is defined as the transpose of the jacobian dot product with
        the jacobian matrix.  The jacobian matrix is of size (N,P).  The resulting
        A matrix will be size (N,N). Where,
            N is the number of parameters to be estimated
            P is the number of measurements used in the estimation algorithm.
    */
    double*fjacT;
    fjacT = (double*)malloc(P * N * sizeof(double));

    matrixTranspose(P, N, fjac, fjacT);
    matrixDot(fjacT, N, P, fjac, P, N, Amatrix);

    free(fjacT);
    return;
}

void perturbationTest(const size_t m, const size_t n, const double ftol,
                      const double xtol, const double gtol,
                      const int maxfev, const double epsfcn, const int mode,
                      double factor, const int nprint,
                      const struct parameter_constraints *st_ptr,
                      double *xInitial, struct parameterStr * parametersStr,
                      const double factorMax, const double factorScale,
                      class perturbStruct *pStruct)
{
/*
    The idea with the perturbation test is that I have my "perfect fit" and
    then refit each while changing one paramter +-20% for example.
*/
///perturbation parameters
    const size_t xnumber = pStruct->xnumber;
    const double spread = pStruct->spread;
    constexpr bool debugPrint = true;

///fitting constants set
    int nfev;
    int info = 0;
    const double a_subTrue    = parametersStr->a_sub;
    const double gammaTrue    = parametersStr->gamma;
    const double E_sigmaTrue  = parametersStr->E_sigma;
    const double lambdaTrue   = parametersStr->lambda;
    const double R1True       = parametersStr->R1;
    const double R0True       = parametersStr->R0;
    double*xpredicted = new double[n];

///Prepare output file
    std::ofstream myfile;
    std::ostringstream filename;
    filesystem::makeDir(parametersStr->dir, "debug");

    if(debugPrint)
    {
        filename <<  "../debug/perturbationTestLog.dat";
        myfile.open(filename.str().c_str());
        myfile << std::setprecision(8);
        myfile << spread << "\t" << xnumber << "\t" << parametersStr->N << "\n";
        myfile << a_subTrue<< "\t" << gammaTrue << "\t" <<E_sigmaTrue  << "\t";
        myfile << lambdaTrue  << "\t" <<R1True  << "\n";
    }


///Implement iteration
    if( parametersStr->N >1)
    {
        parametersStr->N = parametersStr->N95-1;
    }


    for(size_t currentI = 0; currentI <=  parametersStr->N ; ++currentI)
    {
        ///Reset parameters to be fitted
        size_t iter = 0;
        for(size_t i = 0; i < parametersStr->N95 ; ++i)
        {
            if( currentI != i )
            {
                parametersStr->xParametersNames[iter++]
                = parametersStr->xParameters95Names[i];
            }
        }

//        for(size_t n = 0;  n < 4; ++n)
//        {
//            std::cout << parametersStr->xParametersNames[n] << "\n";
//        }getchar();

        double area1 = 0;
        double area2 = 0;

        ///Perturb one parameter
        for (size_t xiters = 0; xiters < xnumber;  ++xiters)
        {
            for(size_t i = 0 ; i < parametersStr->N ; ++i)
            {
                double
                multiplier = 1-spread + 2*spread*(xiters/double(xnumber-1));
                switch( parametersStr->xParameters95Names[currentI] )
                {
                    case asub :
                        parametersStr->a_sub = a_subTrue * multiplier;
                        break;
                    case E1 :
                        parametersStr->E_sigma = E_sigmaTrue * multiplier;
                        break;
                    case gammaEff :
                        parametersStr->gamma = gammaTrue * multiplier;
                        break;
                    case R1 :
                        parametersStr->R1 = R1True * multiplier;
                        break;
                    case lambda :
                        parametersStr->lambda = lambdaTrue * multiplier;
                        break;
                    case R0 :
                        parametersStr->R0 = R0True * multiplier;
                        break;
                    default:
                        std::cout << "\nSwitch Error!!\n";
                        exit(-66);
                        break;
                }


                parameters_kcp_update(parametersStr, parametersStr->gamma,
                                      parametersStr->a_sub);

                ///Set Initial conditions
                switch( parametersStr->xParametersNames[i] )
                {
                    case asub :
                        xInitial[i] = a_subTrue;
                        break;
                    case E1 :
                        xInitial[i] = E_sigmaTrue;
                        break;
                    case gammaEff :
                        xInitial[i] = gammaTrue;
                        break;
                    case R1 :
                        xInitial[i] = R1True;
                        break;
                    case lambda :
                        xInitial[i] = lambdaTrue;
                        break;
                    case R0 :
                        xInitial[i] = R0True;
                        break;
                    default:
                        std::cout << "\nSwitch Error!!\n";
                        exit(-67);
                        break;
                }
//std::cout <<  xInitial[i] <<"\t";

            }

            paramter_estimation(m, parametersStr->N, ftol, xtol, gtol, maxfev,
                                epsfcn, mode, factor, nprint, &info, &nfev,
                                st_ptr, xInitial, parametersStr,
                                factorMax, factorScale, xpredicted);
            phase99(parametersStr->L_end,
                    parametersStr, parametersStr->predicted);

            const double msearea =
            MSEarea(parametersStr->L_end, parametersStr->emissionNominal,
                    parametersStr->predicted);


            pStruct->temp[xiters + xnumber*currentI ] = msearea;

            /*Select larger of two possible extremes.*/
            if(xiters == 0 || xiters == xnumber-1 )
            {
                if(xiters == 0) {area1 = msearea;}
                if(xiters == xnumber-1)
                {
                    area2 = msearea;
                    pStruct->xArea[currentI] = (area1 < area2 ? area1 : area2);
                }
            }

            if(debugPrint)
            {
              /*printPEstimates(parametersStr->N, parametersStr);*/
                myfile << std::setprecision(8)
                       << parametersStr->a_sub << "\t"
                       << parametersStr->gamma << "\t"
                       << parametersStr->E_sigma << "\t"
                       << parametersStr->lambda << "\t"
                       << parametersStr->R1 << "\t"
                       << msearea;
                myfile << "\n";
            }
        }

    }

///RESET
    parametersStr->N = parametersStr->N95;

    for(size_t i = 0; i < parametersStr->N ; ++i)
    {
        parametersStr->xParametersNames[i]
        = parametersStr->xParameters95Names[i];
        ///Set Initial conditions
        switch( parametersStr->xParametersNames[i] )
        {
            case asub :
                parametersStr->a_sub = a_subTrue;
                std::cout << parametersStr->a_sub << "\t";
                break;
            case E1 :
                parametersStr->E_sigma = E_sigmaTrue;
                std::cout << parametersStr->E_sigma << "\t";
                break;
            case gammaEff :
                parametersStr->gamma = gammaTrue;
                std::cout << parametersStr->gamma << "\t";
                break;
            case R1 :
                parametersStr->R1 = R1True;
                std::cout << parametersStr->R1 << "\t";
                break;
            case lambda :
                parametersStr->lambda = lambdaTrue;
                std::cout << parametersStr->lambda << "\t";
                break;
            case R0 :
                parametersStr->R0 = R0True;
                std::cout << parametersStr->R0 << "\t";
                break;
            default:
                std::cout << "\nSwitch Error!!\n";
                exit(-67);
                break;
        }
    }
    parameters_kcp_update(parametersStr, parametersStr->gamma,
                          parametersStr->a_sub);

    myfile.close();
    delete []xpredicted;

    return;
}

void lthermalSweep(const size_t m, const size_t n, const double ftol,
                   const double xtol, const double gtol,
                   const int maxfev, const double epsfcn, const int mode,
                   double factor, const int nprint,
                   const struct parameter_constraints *st_ptr,
                   double *xInitial, struct parameterStr * parametersStr,
                   const double factorMax, const double factorScale,
                   class perturbStruct *pStruct, const std::string filename,
                   const size_t lEndMin)
{
    /*  The idea with the perturbation test is that I have my "perfect fit" and
    then refit each while changing one paramter +-20% for example. */
    const int xnum = pStruct->xnumber;

    const double gammaTrue    = parametersStr->gamma;
    const double a_subTrue    = parametersStr->a_sub;
    const double R1True       = parametersStr->R1;
    const double E_sigmaTrue  = parametersStr->E_sigma;
    const double lambdaTrue   = parametersStr->lambda;

///Prepare output file
    std::ofstream myfile;
    myfile.open(filename);
    myfile << std::setprecision(8);
    myfile << pStruct->spread << "\t" << xnum << "\t" << parametersStr->N;
    myfile << "\n" << pStruct->iterates << "\n";
    myfile << a_subTrue<< "\t" << gammaTrue << "\t" << E_sigmaTrue  << "\t";
    myfile <<lambdaTrue  << "\t" <<R1True  << "\n";

    for(int i = 0 ; i < xnum; ++i)
    {
        myfile << pStruct->spread *
        ( double( -( ( xnum/2 ) ) + i ) / ( double ( xnum / 2 ) ) ) << "\t";
    }
    myfile << "\n";

///Implement iteration
    for(size_t j = 0; j <  pStruct->iterates ; ++j)
    {
        const double lmin = pStruct->lmin[j];
        const double lmax = pStruct->lmax[j];

        parametersStr->thermalSetup(lmin, lmax, lEndMin);
        phase99(parametersStr->L_end,
                parametersStr, parametersStr->emissionNominal);
        for(size_t i = 0 ; i < parametersStr->L_end; ++i)
        {
            parametersStr->emissionExperimental[i]
            = parametersStr->emissionNominal[i];
        }

        perturbationTest(parametersStr->L_end, parametersStr->N, ftol, xtol,
                         gtol, maxfev, epsfcn, mode, factor, nprint, st_ptr,
                         xInitial, parametersStr,factorMax, factorScale,
                         pStruct);

        std::cout << j <<" "<< pStruct->bands[j]<<" "<< lmin <<" "<< lmax;
        for(size_t i = 0; i < parametersStr->N; ++i)
            std::cout << " " << pStruct->xArea[i];
        std::cout << "\n";

        myfile << j << "\t" <<  pStruct->bands[j] <<  "\t" << lmin << "\t";
        myfile << lmax;

        for( size_t k = 0 ; k < parametersStr->N ; k++)
        {
            for(size_t i = 0 ; i < pStruct->xnumber ; ++i)
            {
                myfile << "\t" << pStruct->temp[i + k*pStruct->xnumber];
            }
        }
        myfile << "\n";
    }

    myfile.close();

    return;
}

void lthermalOptimization(const size_t n, const double ftol, const double xtol,
                          const double gtol, const int maxfev,
                          const double epsfcn, const int mode, double factor,
                          const int nprint,
                          const struct parameter_constraints *st_ptr,
                          double *xInitial, struct parameterStr * parametersStr,
                          const double factorMax, const double factorScale,
                          class perturbStruct *pStruct, const double a,
                          const double b, const bool d1, const bool d2,
                          const int s1, const double noiseRandom,
                          const std::string filename)
{
    /*The idea with the perturbation test is that I have my "perfect fit" and
    then refit each while changing one paramter +-20% for example. */
    const int xnum = pStruct->xnumber;
    const double gammaTrue    = parametersStr->gamma;
    const double a_subTrue    = parametersStr->a_sub;
    const double R1True       = parametersStr->R1;
    const double E_sigmaTrue  = parametersStr->E_sigma;
    const double lambdaTrue   = parametersStr->lambda;
    const double R0True       = parametersStr->R0;
    const double lminN  = parametersStr->laser->l_thermal[0];
    const double lmaxN  = parametersStr->laser->l_thermal[parametersStr->L_end-1];
    double*xpredicted = new double[n];

    int nfev;
    int info = 0;

///Input calibration file and read data
    class calibration_curves *CCurves = nullptr;
    CCurves = new class calibration_curves(filename);

///Create Initial Experimental Data
    phase99(parametersStr->L_end,
            parametersStr, parametersStr->emissionNominal);

    for(size_t i =0 ; i < parametersStr->L_end; i++)
    {
        parametersStr->emissionExperimental[i]
        = parametersStr->emissionNominal[i];
    }

///Initial Fit to get initial guesses
    constexpr size_t interants = 0;
    fitting(parametersStr->L_end, parametersStr->N, ftol, xtol, gtol, maxfev,
            epsfcn, mode, factor, nprint, st_ptr, parametersStr,
            xInitial, interants, factorMax, factorScale);

///prepare output file with parameter uncertainty data
    filesystem::makeDir(parametersStr->dir, "debug");
    std::ofstream myoutputfile;
    std::stringstream filename1;
    filename1 <<  "../data/ParameterUncertainty.dat";
    myoutputfile.open(filename1.str().c_str());
    myoutputfile << std::setprecision(8);

///Implement iteration
    for(size_t j = 0; j <  pStruct->iterates ; ++j)
    {
        ///setup thermal penetration distribution
        const double lmin = pStruct->lmin[j];
        const double lmax = pStruct->lmax[j];
        constexpr size_t lEndMin = 50;
        parametersStr->thermalSetup(lmin, lmax, lEndMin);

        ///Create Initial Experimental Data
        phase99(parametersStr->L_end,
                parametersStr, parametersStr->emissionNominal);
        for(size_t i =0 ; i < parametersStr->L_end; i++)
        {
            parametersStr->emissionExperimental[i]
            = parametersStr->emissionNominal[i];
        }

        ///add artificial experimental data
        parametersStr->EmissionNoise(a, b, d1, d2, s1, noiseRandom,
                                     parametersStr->emissionNominal, lminN, lmaxN);

        ///estimate unknown parameters
        paramter_estimation(parametersStr->L_end, parametersStr->N, ftol, xtol,
                            gtol, maxfev,epsfcn, mode, factor, nprint, &info,
                            &nfev, st_ptr, xInitial, parametersStr, factorMax,
                            factorScale, xpredicted);
        phase99(parametersStr->L_end,
                parametersStr, parametersStr->predicted);

        ///develop the uncertainties
        double msearea = MSEarea(parametersStr->L_end,
                                 parametersStr->emissionNominal,
                                 parametersStr->predicted);
        double
        diffUncerntainty = evaluateUncertainty(msearea,
                                               CCurves->perturbation,
                                               CCurves->caliDiff[j],
                                               xnum);
        double
        effUncerntainty = evaluateUncertainty(msearea,
                                              CCurves->perturbation,
                                              CCurves->caliEff[j],
                                              xnum);
        double
        R1Uncerntainty = evaluateUncertainty(msearea,
                                             CCurves->perturbation,
                                             CCurves->caliR1[j],
                                             xnum);
        double
        E1Uncerntainty = evaluateUncertainty(msearea,
                                             CCurves->perturbation,
                                             CCurves->caliEmission[j],
                                             xnum);
        double
        OptUncerntainty = evaluateUncertainty(msearea,
                                              CCurves->perturbation,
                                              CCurves->caliOptical[j],
                                              xnum);

        myoutputfile << pStruct->bands[j] << "\t" << lmin << "\t" << lmax;
        myoutputfile << "\t" << msearea;
        myoutputfile << "\t" << diffUncerntainty << "\t" << effUncerntainty ;
        myoutputfile << "\t" << R1Uncerntainty << "\t" << E1Uncerntainty ;
        myoutputfile << "\t" << OptUncerntainty <<"\n";

        ///Reset Inputs
        for(size_t i=0 ; i< n ; i++)
        {
            switch ( parametersStr->xParametersNames[i] )
            {
                case asub :
                    parametersStr->a_sub = a_subTrue;
                    break;

                case E1 :
                    parametersStr->E_sigma =E_sigmaTrue;
                    break;

                case gammaEff :
                    parametersStr->gamma = gammaTrue;
                    break;

                case R1 :
                    parametersStr->R1 = R1True;
                    break;

                case lambda :
                    parametersStr->lambda = lambdaTrue;
                    break;

                case R0 :
                    parametersStr->R0 = R0True;
                    break;

                default:
                    std::cout << "\nSwitch Error!!\n";
                    exit(-69);
                    break;
            }
        }

        ///Reset Initial Guess
        xInitial[0] = 2.5;
        xInitial[1] = 3.9;
        xInitial[2] = 44;
        xInitial[3] = .83;
        xInitial[4] = .6;
    }

    myoutputfile.close();


    delete []xpredicted;
    CCurves->cleanup();
    delete CCurves;

    return;
}

void statisticalPrintOut(size_t P, size_t N,
                        const struct parameter_constraints *pc_ptr,
                        double *xInitial, struct parameterStr * parametersStr,
                        const double ExpStddev,double *Numerical_Phase,
                        double *Analytical_Phase, const double factorMax,
                        const double factorScale)
{
    const size_t v1 = parametersStr->L_end - N;
    const double ExpVarianceEst = ExpStddev * ExpStddev;

    parametersStr->variance = variance(P,N,parametersStr->fvecTotal);
//    Amatrix(P, N, parametersStr->fjac, parametersStr->Amatrix);
//    covarianceMatrix(N, parametersStr->variance, parametersStr->Amatrix,
//                     parametersStr->cov);
//    standardError(N, parametersStr->cov, parametersStr->standardError);
//    InformationIndexAll(P, N, parametersStr);

//    parametersStr->ChiSquare = chisquare(parametersStr->L_end,
//                                         parametersStr->emissionExperimental,
//                                         parametersStr-> predicted);
    printfJac(N, P, parametersStr->fjac);

    std::cout <<"\n";
    std::cout << "Estimated Variance: "<< parametersStr->variance << "\n";
    std::cout << "Estimated Standard Deviation: " <<
    sqrt(parametersStr->variance) << "\n";
    std::cout << "Estimated StDev for each parameter: \n";
    for(size_t i=0 ; i<N ; ++i)
    {
        for(size_t j=0 ; j<N; ++j)
        {
//            if(i==j) std::cout << sqrt(parametersStr->cov[i+N*j])<< "\t";
        }
    }

    std::cout << "\nChi-Square = " << (parametersStr->fvecTotal /
                                       ExpVarianceEst) ;
    std::cout << "\nNormalized Chi-Square = " << (parametersStr->fvecTotal /
                                                  ExpVarianceEst) / v1;
    std::cout << "\n\n" << parametersStr->variance << "\n";
    std::cout << "\n" << ExpVarianceEst << "\n\n";
    std::cout <<  "\nv1 = " << v1;


    return;
}

void fitting(size_t P, size_t N, double ftol, double xtol, double gtol,
             int maxfev, double epsfcn, int mode, double factor, int nprint,
             const struct parameter_constraints *st_ptr,
             struct parameterStr * pStruct, double *xInitial,
             const size_t interants, const double factorMax,
             const double factorScale)
{
/// Scale jacobian if enabled
    double *xpredicted = new double[N];
    std::ofstream myfile;
    std::stringstream filename;
    filename <<  "../data/fittingData.dat";
    myfile.open(filename.str().c_str());
    myfile << std::setprecision(8);
    myfile << "#run\tasub_0\tgamma_0\tEsigma_0\tR1_0\tlambda_0";
    myfile << "\tasub\tgamma\tEsigma\tR1\tlambda\n";


    for(size_t i=0; i<interants; ++i)
    {
        int nfev;
        int info = 0;
        myfile << i << "\t";

        paramter_estimation(P, N, ftol, xtol, gtol, maxfev, epsfcn, mode,
                            factor, nprint, &info, &nfev, st_ptr, xInitial,
                            pStruct, factorMax, factorScale, xpredicted);
        pStruct->MSE = MSE(pStruct->L_end, pStruct->emissionExperimental,
                           pStruct->predicted);

        myfile << pStruct->gamma << "\t"
               << pStruct->a_sub << "\t"
               << pStruct->E_sigma << "\t"
               << pStruct->R1 << "\t"
               << pStruct->lambda << "\t"
               << pStruct->MSE << "\n";

        printPEstimates(N, pStruct);
//        for(size_t j=0; j< N; ++j)
//            {xInitial[j] = 0;}
           xInitial[0] = 2.3;
           xInitial[1] = 3.8;
           xInitial[2] = 42;
           xInitial[3] = 0.8;
           xInitial[4] = 0.57;

        phase99(pStruct->L_end,
                pStruct, pStruct->predicted);


        std::cout << "\n";
    }
    myfile.close();

    delete []xpredicted;

    return;
}


void bootstrap(size_t P, size_t N, double ftol, double xtol, double gtol,
               int maxfev, double epsfcn, int mode, double factor, int nprint,
               const struct parameter_constraints *st_ptr,
               struct parameterStr * parametersStr, const double ExpStddev,
               const double *Numerical_Phase,const  double *Analytical_Phase,
               double *xInitial, const size_t interants, const double factorMax,
               const double factorScale)
{
    int nfev;
    int info = 0;
/// Scale jacobian if enabled
    std::ofstream myfile;
    std::stringstream filename;
    filename <<  "../data/fittingData.dat";
    myfile.open(filename.str().c_str());
    myfile << std::setprecision(8);
    myfile << "#run\tasub_0\tgamma_0\tEsigma_0\tR1_0\tlambda_0";
    myfile << "\taub\tgamma\tEsigma\tR1\tlambda\n";
    const double ExpVarianceEst = ExpStddev * ExpStddev;
    const size_t v1 = parametersStr->L_end - N;
    double*xpredicted = new double[N];

///Setup initial parameter estimation to determine spread of residuals
    paramter_estimation(P, N, ftol, xtol, gtol, maxfev, epsfcn, mode,
                        factor, nprint, &info, &nfev, st_ptr, xInitial,
                        parametersStr, factorMax, factorScale, xpredicted);

    double *predictedOG = new double[parametersStr->L_end];
    double *fvecOG = new double[parametersStr->L_end];

    for(size_t n = 0 ; n < parametersStr->L_end ; ++n )
    {
        predictedOG[n]  = parametersStr-> predicted[n];
        fvecOG[n] = parametersStr->fvec[n];
    }

    ///Start the bootstrap process
    for(size_t i=0; i<interants; ++i)
    {
        myfile << i << "\t";
        for(size_t j=0; j < N; j++ )
            {xInitial[j] = xpredicted[j];}
        for(size_t n = 0 ; n < parametersStr->L_end ; ++n )
        {
            parametersStr-> emissionExperimental[n]  = predictedOG[n];
            parametersStr-> emissionExperimental[n] +=
            fvecOG[xINTrandom(0,parametersStr->L_end-1)];
        }

        paramter_estimation(P, N, ftol, xtol, gtol, maxfev, epsfcn, mode,
                            factor, nprint, &info, &nfev, st_ptr,
                            xInitial, parametersStr, factorMax, factorScale,
                            xpredicted);

        parametersStr->MSE = MSE(parametersStr->L_end,
                             parametersStr->emissionExperimental,
                             parametersStr-> predicted);

        myfile << parametersStr->gamma << "\t"
               << parametersStr->a_sub << "\t"
               << parametersStr->E_sigma << "\t"
               << parametersStr->R1 << "\t"
               << parametersStr->lambda << "\t"
               << (parametersStr->fvecTotal / ExpVarianceEst) / v1 << "\t"
               << parametersStr->MSE << "\n";

        printPEstimates(N, parametersStr);
    }
    myfile.close();


    delete [] predictedOG;
    delete [] fvecOG;
    delete []xpredicted;

    return;
}


double fintegrate(double x, void *p)
{
    struct funcClass &params = *reinterpret_cast<struct funcClass *>(p);

    return params.eval(x);
}

double integrate(struct funcClass *Func, double xlow, double xhigh)
{
    //http://www.bnikolic.co.uk/nqm/1dinteg/gslgk.html

    struct funcClass &params = *Func;

    gsl_function F;
    F.function = &fintegrate;
    F.params = reinterpret_cast<void *>(&params);

    Func->code = gsl_integration_qng(&F, xlow, xhigh, params.epsabs,
                                     params.epsrel, &params.result,
                                     &params.error, &params.neval);
    return Func->result;
}

double MSEarea(const size_t N, const double* const func1,
               const double* const func2)
{
    ///Startup and initialization
    double sum = 0;
    for(size_t i=0 ; i < N ; i++)
    {
        sum += fabs(func1[i] - func2[i]);
    }

    return sum / N;
}

double MSEarea1(size_t N, double* func1, double* func2, double* xvar)
{
/*
    This function calculates the area between two curves.  This is done by
    feeding in two lists of points (func1 and func2) along with the independent
    variable (xvar).  The lists of points are fitted to an interpolating
    cubic spline.  This spline is then used to evaluate the integral and area
    between the lists.

*/

    ///Startup and initialization
    struct funcClass *Func1;
    Func1 = new struct funcClass (xvar, func1, N);
    struct funcClass *Func2;
    Func2 = new struct funcClass (xvar, func2, N);

    ///Evaluate Integration
    double etol = 1e-5;
    double xStep = etol;
    double xo;
    double area = 0;

    for (double xi = xvar[0]; xi <= xvar[N-1]; xi += xStep)
    {
        xo = xi;
        if(Func1->eval(xi) > Func2->eval(xi))
        {
            while(Func1->eval(xi) > Func2->eval(xi))
            {
                xi += xStep;
            }
            area += integrate(Func1, xo, xi) - integrate(Func2, xo, xi);
            xi -= xStep;
        }

        else if(Func2->eval(xi) > Func1->eval(xi))
        {
            while(Func2->eval(xi) > Func1->eval(xi))
            {
                xi += xStep;
            }
            area += integrate(Func2, xo, xi) - integrate(Func1, xo, xi);
            xi -= xStep;
        }

        else if( fabs(Func2->eval(xi) - Func1->eval(xi)) <  etol)
        {
            area +=0;
        }
    }


    ///Cleanup
    Func1->cleanup();
    Func2->cleanup();
    delete Func1;
    delete Func2;

    return area;
}

template< typename Type >
constexpr Type maximum( Type a, Type b )
{
    return a < b ? b : a;
}


double evaluateUncertainty(const double MSEarea, double* perturbationTable,
                           const std::vector<double>& calibrationTable,
                           size_t xnum)
{
    if(MSEarea < 1e-10)
    {
        return 0;
    }


    double value = 0;
    double*calibration = new double[xnum];
    for(size_t i=0; i<xnum ; ++i)
    {
        calibration[i] = calibrationTable[i];
    }

    struct funcClass *Func1;
    Func1 = new struct funcClass(perturbationTable, calibration, xnum);

    const double stepsize = fabs(perturbationTable[1] -perturbationTable[0])/1000;
    double perturbation = 0;

    ///Start cycling through the perturbation interpolation table
    double diffminPos = perturbation;
    double diffminOld = MSEarea;

    while(perturbation >= 0
           && perturbation <= perturbationTable[xnum-1])
    {
        value = Func1->eval(perturbation);

        double diffmin = fabs(MSEarea - value);

        if(diffmin < diffminOld)
        {
            diffminPos = perturbation;
            diffminOld = diffmin;
        }

        if( (perturbation+stepsize) <= perturbationTable[xnum-1]  )
        {
            perturbation += stepsize;
        }
        else
        {
            break;
        }
    }





    delete Func1;
    delete[]calibration;

    return diffminPos;
}
