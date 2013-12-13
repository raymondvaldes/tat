#include "../Header.h"
void perturbationTest(const size_t m, const size_t n,
                      struct parameterEstimation::settings ParaEstSetting,
                      const struct parameter_constraints *st_ptr,
                      double *xInitial,
                      class thermalAnalysisMethod::PopTea poptea,
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
    const size_t N = poptea.LMA.unknownParameters.Nsize();
///fitting constants set
    int nfev;
    int info = 0;
    const double a_subTrue    = poptea.TBCsystem.a_sub;
    const double gammaTrue    = poptea.TBCsystem.gamma;
    const double E_sigmaTrue  = poptea.TBCsystem.optical.Emit1;
    const double lambdaTrue   = poptea.TBCsystem.coating.lambda;
    const double R1True       = poptea.TBCsystem.optical.R1;
    const double R0True       = poptea.TBCsystem.optical.R0;
    double*xpredicted = new double[n];


///Prepare output file
    std::ofstream myfile;
    std::ostringstream filename;

    poptea.DataDirectory.mkdir("debug");
    if(debugPrint)
    {
        filename <<  "../debug/perturbationTestLog.dat";
        myfile.open(filename.str().c_str());
        myfile << std::setprecision(8);
        myfile << spread << "\t" << xnumber << "\t" <<
                  poptea.LMA.unknownParameters.Nsize() << "\n";
        myfile << a_subTrue<< "\t" << gammaTrue << "\t" <<E_sigmaTrue  << "\t";
        myfile << lambdaTrue  << "\t" <<R1True  << "\n";
    }

///Implement iteration
    if( poptea.LMA.unknownParameters.Nsize() >1)
    {
        poptea.LMA.unknownParameters.NAssign(poptea.N95-1);
    }

///Reset parameters to be fitted
    for(size_t currentI = 0; currentI <=  poptea.LMA.unknownParameters.Nsize() ; ++currentI)
    {
        size_t iter = 0;
        for(size_t i = 0; i < poptea.N95 ; ++i)
        {
            if( currentI != i )
            {
                poptea.xParametersNames[iter++]
                = poptea.xParameters95Names[i];
            }
        }

        double area1 = 0;
        double area2 = 0;

        ///Perturb one parameter
        for (size_t xiters = 0; xiters < xnumber;  ++xiters)
        {
            double multiplier = 0;
            multiplier = 1-spread + 2*spread*(xiters/double(xnumber-1));
            switch( poptea.xParameters95Names[currentI] )
            {
                case asub :
                    poptea.TBCsystem.a_sub = a_subTrue * multiplier;
//                    std::cout << poptea.a_sub << "\t";
                    break;
                case E1 :
                    poptea.TBCsystem.optical.Emit1 = E_sigmaTrue * multiplier;
//                    std::cout << poptea.E_sigma << "\t";
                    break;
                case gammaEff :
                    poptea.TBCsystem.gamma = gammaTrue * multiplier;
//                    std::cout << poptea.gamma << "\t";
                    break;
                case R1 :
                    poptea.TBCsystem.optical.R1 = R1True * multiplier;
//                    std::cout << poptea.R1 << "\t";
                    break;
                case lambda :
                    poptea.TBCsystem.coating.lambda = lambdaTrue * multiplier;
//                    std::cout << poptea.lambda << "\t";
                    break;
                case R0 :
                    poptea.TBCsystem.optical.R0 = R0True * multiplier;
//                    std::cout << parametersStr.R0 << "\t";
                    break;
                default:
                    std::cout << "\nSwitch Error!!\n";
                    exit(-66);
                    break;
            }

            poptea.TBCsystem.updateCoat();

//            std::cout << "\n";
            for(size_t i = 0 ; i < N ; ++i)
            {
                ///Set Initial conditions
                switch( poptea.xParametersNames[i] )
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
            }

            paramter_estimation(m, N, ParaEstSetting, &info,
                                &nfev, st_ptr, xInitial, poptea,
                                factorMax, factorScale, xpredicted);
            phase99(poptea.expSetup.laser.L_end, poptea,
                    poptea.LMA.LMA_workspace.predicted);

            const double msearea =
            MSEarea(poptea.expSetup.laser.L_end,
                    poptea.LMA.LMA_workspace.emissionNominal,
                    poptea.LMA.LMA_workspace.predicted);
            pStruct->temp[xiters + xnumber*currentI ] = msearea;

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
                myfile << std::setprecision(8)
                       << poptea.TBCsystem.a_subEval() << "\t"
                       << poptea.TBCsystem.gammaEval() << "\t"
                       << poptea.TBCsystem.optical.Emit1 << "\t"
                       << poptea.TBCsystem.coating.lambda << "\t"
                       << poptea.TBCsystem.optical.R1 << "\t"
                       << msearea;
                myfile << "\n";
            }
        }



    }
    myfile.close();
    delete []xpredicted;

///RESET
    poptea.LMA.unknownParameters.NAssign(poptea.N95);
    for(size_t i = 0; i < poptea.LMA.unknownParameters.Nsize(); ++i)
    {
        poptea.xParametersNames[i]
        = poptea.xParameters95Names[i];
        ///Set Initial conditions
        switch( poptea.xParametersNames[i] )
        {
            case asub :
                poptea.TBCsystem.a_sub = a_subTrue;
                break;
            case E1 :
                poptea.TBCsystem.optical.Emit1  = E_sigmaTrue;
                break;
            case gammaEff :
                poptea.TBCsystem.gamma = gammaTrue;
                break;
            case R1 :
                poptea.TBCsystem.optical.R1 = R1True;
                break;
            case lambda :
                poptea.TBCsystem.coating.lambda = lambdaTrue;
                break;
            case R0 :
                poptea.TBCsystem.optical.R0 = R0True;
                break;
            default:
                std::cout << "\nSwitch Error!!\n";
                exit(-67);
                break;
        }
    }
    poptea.TBCsystem.updateCoat();

    return;
}

void calibrationSweep(struct parameterEstimation::settings ParaEstSetting,
                      const struct parameter_constraints *st_ptr,
                      double *xInitial,
                      class thermalAnalysisMethod::PopTea poptea,
                      const double factorMax, const double factorScale,
                      class perturbStruct *pStruct, const std::string filename,
                      const size_t lEndMin)
{
    /*  The idea with the perturbation test is that I have my "perfect fit" and
    then refit each while changing one paramter +-20% for example. */

    const int xnum = pStruct->xnumber;

    const double gammaTrue    = poptea.TBCsystem.gammaEval();
    const double a_subTrue    = poptea.TBCsystem.a_subEval();
    const double R1True       = poptea.TBCsystem.optical.R1;
    const double E_sigmaTrue  = poptea.TBCsystem.optical.Emit1;
    const double lambdaTrue   = poptea.TBCsystem.coating.lambda;


///Prepare output file
    std::ofstream myfile;
    myfile.open(filename);
    myfile << std::setprecision(8);
    myfile << pStruct->spread << "\t" << xnum << "\t" <<
              poptea.LMA.unknownParameters.Nsize();
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
        poptea.thermalSetup(lmin, lmax, lEndMin);

        phase99(poptea.expSetup.laser.L_end, poptea,
                poptea.LMA.LMA_workspace.emissionNominal);
        for(size_t i = 0 ; i < poptea.expSetup.laser.L_end; ++i)
        {
            poptea.LMA.LMA_workspace.emissionExperimental[i]
            = poptea.LMA.LMA_workspace.emissionNominal[i];
        }

        perturbationTest(poptea.expSetup.laser.L_end,
                         poptea.LMA.unknownParameters.Nsize(),
                         ParaEstSetting, st_ptr, xInitial, poptea, factorMax,
                         factorScale, pStruct);

        ///Print some information to terminal
        std::cout << j <<" "<< pStruct->bands[j]<<" "<< lmin <<" "<< lmax;
        for(size_t i = 0; i < poptea.LMA.unknownParameters.Nsize(); ++i)
            std::cout << " " << pStruct->xArea[i];
        std::cout << "\n";

        myfile << j << "\t" <<  pStruct->bands[j] <<  "\t" << lmin << "\t";
        myfile << lmax;

        for( size_t k = 0 ; k < poptea.LMA.unknownParameters.Nsize() ; k++)
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
                          double *xInitial,
                          class thermalAnalysisMethod::PopTea poptea,
                          const double factorMax, const double factorScale,
                          class perturbStruct *pStruct,
                          const class emissionNoiseParameters myEmissionNoise,
                          const std::string filename)
{
    /*The idea with the perturbation test is that I have my "perfect fit" and
    then refit each while changing one paramter +-20% for example. */
    const int xnum = pStruct->xnumber;
    const double gammaTrue    = poptea.TBCsystem.gammaEval();
    const double a_subTrue    = poptea.TBCsystem.a_subEval();
    const double R1True       = poptea.TBCsystem.optical.R1;
    const double E_sigmaTrue  = poptea.TBCsystem.optical.Emit1;
    const double lambdaTrue   = poptea.TBCsystem.coating.lambda;
    const double R0True       = poptea.TBCsystem.optical.R0;
    const double lminN  = poptea.expSetup.laser.l_thermal[0];
    const double lmaxN  = poptea.expSetup.laser.l_thermal[poptea.expSetup.laser.L_end-1];
    double*xpredicted = new double[n];
    int nfev;
    int info = 0;

///Input calibration file and read data
    class calibration_curves *CCurves = nullptr;
    CCurves = new class calibration_curves(filename);

///Create Initial Experimental Data
    ///setup the nominal data
    phase99(poptea.expSetup.laser.L_end,
            poptea,
            poptea.LMA.LMA_workspace.emissionNominal);

    ///let the experimental be equal to the nominal data
    for(size_t i =0 ; i < poptea.expSetup.laser.L_end; i++)
    {
        poptea.LMA.LMA_workspace.emissionExperimental[i]
                = poptea.LMA.LMA_workspace.emissionNominal[i];
    }

///Initial Fit to get initial guesses
    constexpr size_t interants = 0;
    fitting(poptea.expSetup.laser.L_end,
            poptea.LMA.unknownParameters.Nsize(), ParaEstSetting,
            st_ptr, poptea, xInitial, interants, factorMax, factorScale);

///prepare output file with parameter uncertainty data
    poptea.DataDirectory.mkdir("debug");
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
        poptea.thermalSetup(lmin, lmax, lEndMin);

        ///Create Initial Experimental Data
        phase99(poptea.expSetup.laser.L_end, poptea,
                poptea.LMA.LMA_workspace.emissionNominal);
        for(size_t i =0 ; i < poptea.expSetup.laser.L_end; i++)
        {
            poptea.LMA.LMA_workspace.emissionExperimental[i]
            = poptea.LMA.LMA_workspace.emissionNominal[i];
        }

        ///add artificial experimental data

//        poptea.EmissionNoise(myEmissionNoise,
//                                     poptea->emissionNominal, lminN,
//                                     lmaxN); //BUG MUST MOVE

        ///estimate unknown parameters
        paramter_estimation(poptea.expSetup.laser.L_end,
                            poptea.LMA.unknownParameters.Nsize(),
                            ParaEstSetting, &info, &nfev, st_ptr, xInitial,
                            poptea, factorMax, factorScale, xpredicted);
        phase99(poptea.expSetup.laser.L_end, poptea,
                poptea.LMA.LMA_workspace.predicted);

        ///develop the uncertainties
        double msearea = MSEarea(poptea.expSetup.laser.L_end,
                                 poptea.LMA.LMA_workspace.emissionNominal,
                                 poptea.LMA.LMA_workspace.predicted);
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
            switch ( poptea.xParametersNames[i] )
            {
                case asub :
                    poptea.TBCsystem.a_sub = a_subTrue;
                    break;

                case E1 :
                    poptea.TBCsystem.optical.Emit1=E_sigmaTrue;
                    break;

                case gammaEff :
                    poptea.TBCsystem.gamma = gammaTrue;
                    break;

                case R1 :
                    poptea.TBCsystem.optical.R1 = R1True;
                    break;

                case lambda :
                    poptea.TBCsystem.coating.lambda = lambdaTrue;
                    break;

                case R0 :
                    poptea.TBCsystem.optical.R0 = R0True;
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
             class thermalAnalysisMethod::PopTea poptea, double *xInitial,
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
                            xInitial, poptea, factorMax, factorScale,
                            xpredicted);
        poptea.LMA.LMA_workspace.MSE =
            MSE(poptea.expSetup.laser.L_end,
                poptea.LMA.LMA_workspace.emissionExperimental,
                poptea.LMA.LMA_workspace.predicted);

        myfile << poptea.TBCsystem.gammaEval() << "\t"
               << poptea.TBCsystem.a_subEval() << "\t"
               << poptea.TBCsystem.optical.Emit1 << "\t"
               << poptea.TBCsystem.optical.R1<< "\t"
               << poptea.TBCsystem.coating.lambda << "\t"
               << poptea.LMA.LMA_workspace.MSE << "\n";

        printPEstimates(N, poptea);
        xInitial = new double[5]{x_ini10(2.3), x_ini10(3.8), x_ini10(42),
                x_ini10(.8), x_ini10(0.57)};

    }

    myfile.close();

    delete []xSave;
    delete []xpredicted;



    return;
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
