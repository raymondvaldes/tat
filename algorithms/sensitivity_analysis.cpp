#include "../Header.h"
void perturbationTest(const size_t m, const size_t n,
                      struct parameterEstimation::settings ParaEstSetting,
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
    const double a_subTrue    = parametersStr->poptea->TBCsystem.a_sub;
    const double gammaTrue    = parametersStr->poptea->TBCsystem.gamma;
    const double E_sigmaTrue  = parametersStr->poptea->TBCsystem.optical.Emit1;
    const double lambdaTrue   = parametersStr->poptea->TBCsystem.coating.lambda;
    const double R1True       = parametersStr->poptea->TBCsystem.optical.R1;
    const double R0True       = parametersStr->poptea->TBCsystem.optical.R0;
    double*xpredicted = new double[n];

//    std::cout << a_subTrue << "\t" << gammaTrue << "\t" << E_sigmaTrue << "\t";
//    std::cout << lambdaTrue << "\t" << R1True << "\n" ;

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
        parametersStr->N = parametersStr->poptea->N95-1;
    }

///Reset parameters to be fitted
    for(size_t currentI = 0; currentI <=  parametersStr->N ; ++currentI)
    {
        size_t iter = 0;
        for(size_t i = 0; i < parametersStr->poptea->N95 ; ++i)
        {
            if( currentI != i )
            {
                parametersStr->xParametersNames[iter++]
                = parametersStr->xParameters95Names[i];
            }
        }

        double area1 = 0;
        double area2 = 0;

        ///Perturb one parameter
        for (size_t xiters = 0; xiters < xnumber;  ++xiters)
        {
            double multiplier = 0;
            multiplier = 1-spread + 2*spread*(xiters/double(xnumber-1));
            switch( parametersStr->xParameters95Names[currentI] )
            {
                case asub :
                    parametersStr->poptea->TBCsystem.a_sub = a_subTrue * multiplier;
//                    std::cout << parametersStr->a_sub << "\t";
                    break;
                case E1 :
                    parametersStr->poptea->TBCsystem.optical.Emit1 = E_sigmaTrue * multiplier;
//                    std::cout << parametersStr->E_sigma << "\t";
                    break;
                case gammaEff :
                    parametersStr->poptea->TBCsystem.gamma = gammaTrue * multiplier;
//                    std::cout << parametersStr->gamma << "\t";
                    break;
                case R1 :
                    parametersStr->poptea->TBCsystem.optical.R1 = R1True * multiplier;
//                    std::cout << parametersStr->R1 << "\t";
                    break;
                case lambda :
                    parametersStr->poptea->TBCsystem.coating.lambda = lambdaTrue * multiplier;
//                    std::cout << parametersStr->lambda << "\t";
                    break;
                case R0 :
                    parametersStr->poptea->TBCsystem.optical.R0 = R0True * multiplier;
//                    std::cout << parametersStr->R0 << "\t";
                    break;
                default:
                    std::cout << "\nSwitch Error!!\n";
                    exit(-66);
                    break;
            }

            parametersStr->poptea->TBCsystem.updateCoat();
//            parameters_kcp_update(parametersStr, parametersStr->gamma,
//                                  parametersStr->a_sub);
//            std::cout << "\n";
            for(size_t i = 0 ; i < parametersStr->N ; ++i)
            {
                ///Set Initial conditions
                switch( parametersStr->xParametersNames[i] )
                {
                    case asub :
                        xInitial[i] = x_ini10(a_subTrue);
                        break;
                    case E1 :
                        xInitial[i] = x_ini10(E_sigmaTrue);
                        break;
                    case gammaEff :
                        xInitial[i] = x_ini10(gammaTrue);
                        break;
                    case R1 :
                        xInitial[i] = x_ini10(R1True);
                        break;
                    case lambda :
                        xInitial[i] = x_ini10(lambdaTrue);
                        break;
                    case R0 :
                        xInitial[i] = x_ini10(R0True);
                        break;
                    default:
                        std::cout << "\nSwitch Error!!\n";
                        exit(-67);
                        break;
                }
//            std::cout <<  xInitial[i] <<"\t";
            }
//            std::cout << "<-- initial guess\n";

//            std::cout <<  multiplier << "\t" <<
//                          parametersStr->xParameters95Names[currentI]
//                      << "\t";
//            std::cout << parametersStr->gamma << "\t" <<
//                         parametersStr->a_sub << "\t\t";
//            std::cout << parametersStr->k1_thermal->offset << "\t" <<
//                         parametersStr->psi1_thermal->offset << "\n";

            paramter_estimation(m, parametersStr->N, ParaEstSetting, &info,
                                &nfev, st_ptr, xInitial, parametersStr,
                                factorMax, factorScale, xpredicted);
//            std::cout << "\n";
            phase99(parametersStr->L_end, parametersStr,
                    parametersStr->predicted);

            const double msearea =
            MSEarea(parametersStr->L_end, parametersStr->emissionNominal,
                    parametersStr->predicted);
            pStruct->temp[xiters + xnumber*currentI ] = msearea;

            /*Select larger of two possible extremes.*/ //TODO replace with func
            pStruct->xArea[currentI] =  msearea;
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
                       << parametersStr->poptea->TBCsystem.a_subEval() << "\t"
                       << parametersStr->poptea->TBCsystem.gammaEval() << "\t"
                       << parametersStr->poptea->TBCsystem.optical.Emit1 << "\t"
                       << parametersStr->poptea->TBCsystem.coating.lambda << "\t"
                       << parametersStr->poptea->TBCsystem.optical.R1 << "\t"
                       << msearea;
                myfile << "\n";
            }
        }



    }
    myfile.close();
    delete []xpredicted;

///RESET
    parametersStr->N = parametersStr->poptea->N95;
    for(size_t i = 0; i < parametersStr->N ; ++i)
    {
        parametersStr->xParametersNames[i]
        = parametersStr->xParameters95Names[i];
        ///Set Initial conditions
        switch( parametersStr->xParametersNames[i] )
        {
            case asub :
                parametersStr->poptea->TBCsystem.a_sub = a_subTrue;
//                std::cout << parametersStr->a_sub << "\t";
                break;
            case E1 :
                parametersStr->poptea->TBCsystem.optical.Emit1  = E_sigmaTrue;
//                std::cout << parametersStr->E_sigma << "\t";
                break;
            case gammaEff :
                parametersStr->poptea->TBCsystem.gamma = gammaTrue;
//                std::cout << parametersStr->gamma << "\t";
                break;
            case R1 :
                parametersStr->poptea->TBCsystem.optical.R1 = R1True;
//                std::cout << parametersStr->R1 << "\t";
                break;
            case lambda :
                parametersStr->poptea->TBCsystem.coating.lambda = lambdaTrue;
//                std::cout << parametersStr->lambda << "\t";
                break;
            case R0 :
                parametersStr->poptea->TBCsystem.optical.R0 = R0True;
//                std::cout << parametersStr->R0 << "\t";
                break;
            default:
                std::cout << "\nSwitch Error!!\n";
                exit(-67);
                break;
        }
    }
    parametersStr->poptea->TBCsystem.updateCoat();
//    parameters_kcp_update(parametersStr, parametersStr->gamma,
//                          parametersStr->a_sub);
    return;
}

void calibrationSweep(
                      struct parameterEstimation::settings ParaEstSetting,
                      const struct parameter_constraints *st_ptr,
                      double *xInitial, struct parameterStr *pStructp,
                      const double factorMax, const double factorScale,
                      class perturbStruct *pStruct, const std::string filename,
                      const size_t lEndMin)
{
    /*  The idea with the perturbation test is that I have my "perfect fit" and
    then refit each while changing one paramter +-20% for example. */

    const int xnum = pStruct->xnumber;

    const double gammaTrue    = pStructp->poptea->TBCsystem.gammaEval();
    const double a_subTrue    = pStructp->poptea->TBCsystem.a_subEval();
    const double R1True       = pStructp->poptea->TBCsystem.optical.R1;
    const double E_sigmaTrue  = pStructp->poptea->TBCsystem.optical.Emit1;
    const double lambdaTrue   = pStructp->poptea->TBCsystem.coating.lambda;


///Prepare output file
    std::ofstream myfile;
    myfile.open(filename);
    myfile << std::setprecision(8);
    myfile << pStruct->spread << "\t" << xnum << "\t" << pStructp->N;
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

        pStructp->thermalSetup(lmin, lmax, lEndMin);
        phase99(pStructp->L_end, pStructp, pStructp->emissionNominal);
        for(size_t i = 0 ; i < pStructp->L_end; ++i)
        {
            pStructp->emissionExperimental[i]
            = pStructp->emissionNominal[i];
        }
        perturbationTest(pStructp->L_end, pStructp->N, ParaEstSetting, st_ptr,
                         xInitial, pStructp,factorMax, factorScale, pStruct);

        ///Print some information to terminal
        std::cout << j <<" "<< pStruct->bands[j]<<" "<< lmin <<" "<< lmax;
        for(size_t i = 0; i < pStructp->N; ++i)
            std::cout << " " << pStruct->xArea[i];
        std::cout << "\n";

        myfile << j << "\t" <<  pStruct->bands[j] <<  "\t" << lmin << "\t";
        myfile << lmax;

        for( size_t k = 0 ; k < pStructp->N ; k++)
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

void parameterUncertainty(const size_t n,
                          struct parameterEstimation::settings ParaEstSetting,
                          const struct parameter_constraints *st_ptr,
                          double *xInitial, struct parameterStr * parametersStr,
                          const double factorMax, const double factorScale,
                          class perturbStruct *pStruct,
                          const class emissionNoiseParameters myEmissionNoise,
                          const std::string filename)
{
    /*The idea with the perturbation test is that I have my "perfect fit" and
    then refit each while changing one paramter +-20% for example. */
    const int xnum = pStruct->xnumber;
    const double gammaTrue    = parametersStr->poptea->TBCsystem.gammaEval();
    const double a_subTrue    = parametersStr->poptea->TBCsystem.a_subEval();
    const double R1True       = parametersStr->poptea->TBCsystem.optical.R1;
    const double E_sigmaTrue  = parametersStr->poptea->TBCsystem.optical.Emit1;
    const double lambdaTrue   = parametersStr->poptea->TBCsystem.coating.lambda;
    const double R0True       = parametersStr->poptea->TBCsystem.optical.R0;
    const double lminN  = parametersStr->laser->l_thermal[0];
    const double lmaxN  = parametersStr->laser->l_thermal[parametersStr->L_end-1];
    double*xpredicted = new double[n];

    int nfev;
    int info = 0;

///Input calibration file and read data
    class calibration_curves *CCurves = nullptr;
    CCurves = new class calibration_curves(filename);

///Create Initial Experimental Data
    ///setup the nominal data
    phase99(parametersStr->L_end, parametersStr,parametersStr->emissionNominal);

    ///let the experimental be equal to the nominal data
    for(size_t i =0 ; i < parametersStr->L_end; i++)
    {
        parametersStr->emissionExperimental[i]
                = parametersStr->emissionNominal[i];
    }

///Initial Fit to get initial guesses
    constexpr size_t interants = 0;
    fitting(parametersStr->L_end, parametersStr->N, ParaEstSetting,
            st_ptr, parametersStr, xInitial, interants, factorMax, factorScale);

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
        phase99(parametersStr->L_end, parametersStr,
                parametersStr->emissionNominal);
        for(size_t i =0 ; i < parametersStr->L_end; i++)
        {
            parametersStr->emissionExperimental[i]
            = parametersStr->emissionNominal[i];
        }

        ///add artificial experimental data

        parametersStr->EmissionNoise(myEmissionNoise,
                                     parametersStr->emissionNominal, lminN,
                                     lmaxN);

        ///estimate unknown parameters
        paramter_estimation(parametersStr->L_end, parametersStr->N,
                            ParaEstSetting, &info, &nfev, st_ptr, xInitial,
                            parametersStr, factorMax, factorScale, xpredicted);
        phase99(parametersStr->L_end, parametersStr, parametersStr->predicted);

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
                    parametersStr->poptea->TBCsystem.a_sub = a_subTrue;
                    break;

                case E1 :
                    parametersStr->poptea->TBCsystem.optical.Emit1=E_sigmaTrue;
                    break;

                case gammaEff :
                    parametersStr->poptea->TBCsystem.gamma = gammaTrue;
                    break;

                case R1 :
                    parametersStr->poptea->TBCsystem.optical.R1 = R1True;
                    break;

                case lambda :
                    parametersStr->poptea->TBCsystem.coating.lambda = lambdaTrue;
                    break;

                case R0 :
                    parametersStr->poptea->TBCsystem.optical.R0 = R0True;
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

void fitting(size_t P, size_t N,
             struct parameterEstimation::settings ParaEstSetting,
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

    double*xSave = new double[N];
    for(size_t i =0 ; i < N ; ++i)
    {
        xSave[i] = xInitial[i];
    }

    for(size_t i=0; i<interants; ++i)
    {
        int nfev;
        int info = 0;
        myfile << i << "\t";

        paramter_estimation(P, N, ParaEstSetting, &info, &nfev, st_ptr,
                            xInitial, pStruct, factorMax, factorScale,
                            xpredicted);
        pStruct->MSE = MSE(pStruct->L_end, pStruct->emissionExperimental,
                           pStruct->predicted);

        myfile << pStruct->poptea->TBCsystem.gammaEval() << "\t"
               << pStruct->poptea->TBCsystem.a_subEval() << "\t"
               << pStruct->poptea->TBCsystem.optical.Emit1 << "\t"
               << pStruct->poptea->TBCsystem.optical.R1<< "\t"
               << pStruct->poptea->TBCsystem.coating.lambda << "\t"
               << pStruct->MSE << "\n";

        printPEstimates(N, pStruct);
        xInitial = new double[5]{x_ini10(2.3), x_ini10(3.8), x_ini10(42),
                x_ini10(.8), x_ini10(0.57)};

    }

    myfile.close();

    delete []xSave;
    delete []xpredicted;



    return;
}


//void bootstrap(size_t P, size_t N, double ftol, double xtol, double gtol,
//               int maxfev, double epsfcn, int mode, double factor, int nprint,
//               const struct parameter_constraints *st_ptr,
//               struct parameterStr * parametersStr, const double ExpStddev,
//               const double *Numerical_Phase,const  double *Analytical_Phase,
//               double *xInitial, const size_t interants, const double factorMax,
//               const double factorScale)
//{
//    int nfev;
//    int info = 0;
///// Scale jacobian if enabled
//    std::ofstream myfile;
//    std::stringstream filename;
//    filename <<  "../data/fittingData.dat";
//    myfile.open(filename.str().c_str());
//    myfile << std::setprecision(8);
//    myfile << "#run\tasub_0\tgamma_0\tEsigma_0\tR1_0\tlambda_0";
//    myfile << "\taub\tgamma\tEsigma\tR1\tlambda\n";
//    const double ExpVarianceEst = ExpStddev * ExpStddev;
//    const size_t v1 = parametersStr->L_end - N;
//    double*xpredicted = new double[N];

/////Setup initial parameter estimation to determine spread of residuals
//    paramter_estimation(P, N, ftol, xtol, gtol, maxfev, epsfcn, mode,
//                        factor, nprint, &info, &nfev, st_ptr, xInitial,
//                        parametersStr, factorMax, factorScale, xpredicted);

//    double *predictedOG = new double[parametersStr->L_end];
//    double *fvecOG = new double[parametersStr->L_end];

//    for(size_t n = 0 ; n < parametersStr->L_end ; ++n )
//    {
//        predictedOG[n]  = parametersStr-> predicted[n];
//        fvecOG[n] = parametersStr->fvec[n];
//    }

//    ///Start the bootstrap process
//    for(size_t i=0; i<interants; ++i)
//    {
//        myfile << i << "\t";
//        for(size_t j=0; j < N; j++ )
//            {xInitial[j] = xpredicted[j];}
//        for(size_t n = 0 ; n < parametersStr->L_end ; ++n )
//        {
//            parametersStr-> emissionExperimental[n]  = predictedOG[n];
//            parametersStr-> emissionExperimental[n] +=
//            fvecOG[xINTrandom(0,parametersStr->L_end-1)];
//        }

//        paramter_estimation(P, N, ftol, xtol, gtol, maxfev, epsfcn, mode,
//                            factor, nprint, &info, &nfev, st_ptr,
//                            xInitial, parametersStr, factorMax, factorScale,
//                            xpredicted);

//        parametersStr->MSE = MSE(parametersStr->L_end,
//                             parametersStr->emissionExperimental,
//                             parametersStr-> predicted);

//        myfile << parametersStr->gamma << "\t"
//               << parametersStr->a_sub << "\t"
//               << parametersStr->E_sigma << "\t"
//               << parametersStr->R1 << "\t"
//               << parametersStr->lambda << "\t"
//               << (parametersStr->fvecTotal / ExpVarianceEst) / v1 << "\t"
//               << parametersStr->MSE << "\n";

//        printPEstimates(N, parametersStr);
//    }
//    myfile.close();


//    delete [] predictedOG;
//    delete [] fvecOG;
//    delete []xpredicted;

//    return;
//}




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
