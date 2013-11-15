#include "../Header.h"

namespace SensitivityValdes2013
{
/*
This namespace will hold all the functions necessary to reproduce the work
in the Valdes2013 Sensitivity Paper.
*/
///Parameter Estimation Options
/* - N number of thermal parameters to be fitted
 - ftol difference in error
 - xtol difference in parameters
 - beta_iter is the total number of iterations to find beta2
 - beta_tol is how close dz_sub is to dz_coat */
constexpr double ftol = 1.e-12;
constexpr double xtol = 1.e-12;
constexpr double gtol = 1.e-12;
constexpr size_t maxfev = 1e5;
constexpr double epsfcn = 1.e-8;
constexpr double factor =  .01;
constexpr int mode = 1;
constexpr int nprint = 0;
struct parameterEstimation::settings
ParaEstSetting(ftol, xtol, gtol, maxfev, epsfcn, factor, mode, nprint);

constexpr double factorMax = 1;
constexpr double factorScale = 5;
constexpr size_t LendMinDecade = 50;

void figureSensitivityIntro(struct parameterStr *pStruct)
{
    /*
    This figure serves as an introduction to the sensitivity concept.  It will
    show (a) a nominal curve, (b) nominal curve with error (c) a fitted curve.
    It will also include a subplot with the error shown.

    To create these curves
    */
    pStruct->L_end = LendMinDecade;

    ///heating constraints
    pStruct->q_surface = 0;

    ///Parameter Estimation Options
    pStruct->MSETol = 1e-8;
    int nfev;
    int info = 0;

    /// Parameter Estimation Constraints
    /*  parameter constraints are stored in the
        structure parameter_constraints */
    struct ::parameter_constraints st_ptr;
    st_ptr.a_sub_min = 1e-0;
    st_ptr.a_sub_max = 5;

    st_ptr.gamma_min = 2e-0;
    st_ptr.gamma_max = 10;

    st_ptr.E_sigma_min = 1e-3;
    st_ptr.E_sigma_max = 200;

    st_ptr.R1_min = 0.6;
    st_ptr.R1_max = 1;

    st_ptr.lambda_min = .1;
    st_ptr.lambda_max = 1;

    st_ptr.R0_min = 0;
    st_ptr.R0_max = 1;

    ///Noise in Simulated Emission
    constexpr double a =  .05;      // max % error (%*pi/2) (try .025)
    constexpr double b = 2.8;       // stretching parameter  (try 2.95) (1->pi)
    constexpr bool d1 = false;       //positive  (try false)
    constexpr bool d2 = true;        //monotonic (try true)
    constexpr int s1 = 0;            //-1(left bias) 0(symmetric) +1(right bias)
    constexpr double noiseRandom = 0.004; // normal noise % of pi/2
    const class emissionNoiseParameters myEmissionNoise(a, b, d1, d2, s1,
                                                        noiseRandom);

    double *Analytical_PhaseR1 = nullptr;
    double *lthermalR1 = nullptr;
    double *predictedR1 = nullptr;
    double *emissionExpR1 = nullptr;

    size_t LendR1, LendR2;
    {
        ///Set heating constraints
        constexpr double l_min = .04;
        constexpr double l_max = 4;
        pStruct->thermalSetup(l_min, l_max, LendMinDecade);

        /// Populate the experimental phase values in parameters99
        Analytical_PhaseR1  = new double[pStruct->L_end]();
        lthermalR1          = new double[pStruct->L_end]();
        predictedR1         = new double[pStruct->L_end]();
        emissionExpR1       = new double[pStruct->L_end]();

        ///Populate arrays
        phase99(pStruct->L_end, pStruct,
                Analytical_PhaseR1);

        ///create artificial experimental data
        pStruct->EmissionNoise(myEmissionNoise, Analytical_PhaseR1, l_min,
                               l_max);

        ///estimate unknown parameters using full range
        double *xpredicted = new double[ pStruct->N];
        double *xInitial = nullptr;
        xInitial = new double[5]{2.3, 3.8, 42, 0.80, 0.57};    
        paramter_estimation(pStruct->L_end, pStruct->N, ParaEstSetting, &info,
                            &nfev, &st_ptr, xInitial, pStruct, factorMax,
                            factorScale, xpredicted);
        delete [] xInitial;
        delete [] xpredicted;
        std::cout << info;

        /// populate the "predicted" array using the model and the new parameter
        /// estimations
        phase99(pStruct->L_end,  pStruct,
                pStruct->predicted);
        for(size_t i = 0; i < pStruct->laser->L_end; ++i)
        {
            lthermalR1[i]       = pStruct->laser->l_thermal[i];
            predictedR1[i]      = pStruct->predicted[i];
            emissionExpR1[i]    = pStruct->emissionExperimental[i];
        }

        LendR1 = pStruct->laser->L_end;
    }

    double *Analytical_PhaseR2 = nullptr;
    double *lthermalR2 = nullptr;
    double *predictedR2 = nullptr;
    double *emissionExpR2 = nullptr;

    {
        ///Reset properties
        pStruct->poptea->TBCsystem.optical.Emit1 = 42;
        pStruct->poptea->TBCsystem.optical.R1 = 0.8;

        pStruct->poptea->TBCsystem.coating.lambda = 0.57;
//        parameters_agamma_update(pStruct, 1.44, 2.1e6);  //BUG??
        pStruct->poptea->TBCsystem.updateCoat();

        ///Set heating constraints
        constexpr double l_min = .2;
        constexpr double l_max = .8;
        pStruct->thermalSetup(l_min, l_max, LendMinDecade);
        LendR2 = pStruct->laser->L_end;

        /// Populate the experimental phase values in parameters99
        Analytical_PhaseR2  = new double[pStruct->L_end]();
        lthermalR2          = new double[pStruct->L_end]();
        predictedR2         = new double[pStruct->L_end]();
        emissionExpR2       = new double[pStruct->L_end]();

        ///Populate arrays
        phase99(pStruct->L_end,  pStruct,
                Analytical_PhaseR2);

        ///create artificial experimental data
        pStruct->EmissionNoise(myEmissionNoise, Analytical_PhaseR2, .04, 4);

        ///estimate unknown parameters using full range
        double *xpredicted = new double[ pStruct->N];
        double *xInitial = nullptr;
        xInitial = new double[5]{2.3, 3.8, 42, 0.80, 0.57};
        paramter_estimation(pStruct->L_end, pStruct->N, ParaEstSetting, &info,
                            &nfev, &st_ptr, xInitial, pStruct, factorMax,
                            factorScale, xpredicted);
        delete [] xInitial;
        delete [] xpredicted;
        std::cout << info;

        /// populate the "predicted" array using the model and the new parameter
        /// estimations
        phase99(pStruct->L_end, pStruct,
                pStruct->predicted);
        LendR2 = pStruct->laser->L_end;

        for(size_t i = 0; i < pStruct->laser->L_end; ++i)
        {
            lthermalR2[i]       = pStruct->laser->l_thermal[i];
            predictedR2[i]      = pStruct->predicted[i];
            emissionExpR2[i]    = pStruct->emissionExperimental[i];
        }
    }

    ///Print stuff

    std::ofstream myfile;
    std::stringstream filename;
    filename <<  "data/figureSensitivityIntro.dat";
    myfile.open(filename.str().c_str());
    myfile << std::setprecision(8);

    for(size_t i = 0; i < LendR1; ++i)
    {
        myfile << lthermalR1[i] << "\t";
        myfile << Analytical_PhaseR1[i] << "\t" ;
        myfile << emissionExpR1[i] << "\t";
        myfile << predictedR1[i] << "\t";

        if( i < LendR2 )
        {
            myfile << lthermalR2[i] << "\t";
            myfile << Analytical_PhaseR2[i] << "\t" ;
            myfile << emissionExpR2[i] << "\t";
            myfile << predictedR2[i] ;
        }
        myfile << "\n";
    }
    myfile.close();


    delete []lthermalR1;
    delete []Analytical_PhaseR1;
    delete []predictedR1;
    delete []emissionExpR1;

    delete []lthermalR2;
    delete []Analytical_PhaseR2;
    delete []predictedR2;
    delete []emissionExpR2;
}

void CC_APS2(struct parameterStr *pStruct)
{
    /* This function is designed to complete the following 5 steps:
     (1) to create the calibration curves for an APS sample
     (2) export data to a data-file
     (3) create experimental data and explort to data-file
     (4) fit the experimental data to the model
     (5) report parameteres and uncertainty using the calibration curves */
    filesystem::makeDir(pStruct->dir, "data/APS2");
    pStruct->L_end = LendMinDecade;

    /// Parameter Estimation Constraints
    /*  parameter constraints are stored in the
        structure parameter_constraints */
    struct ::parameter_constraints st_ptr;
    st_ptr.a_sub_min = 1e-0;
    st_ptr.a_sub_max = 5;

    st_ptr.gamma_min = 2e-0;
    st_ptr.gamma_max = 10;

    st_ptr.E_sigma_min = 1e-3;
    st_ptr.E_sigma_max = 200;

    st_ptr.R1_min = 0.6;
    st_ptr.R1_max = 1;

    st_ptr.lambda_min = .1;
    st_ptr.lambda_max = 1;

    st_ptr.R0_min = 0;
    st_ptr.R0_max = 1;

///Set heating constraints
    constexpr double l_min = .04;
    constexpr double l_max = 4;
    pStruct->thermalSetup(l_min, l_max, LendMinDecade);

/// Populate the experimental phase values in parameters99
    /* Step 1: l_thermal sweep to create calibration tables */
    constexpr size_t iterates = 20;
    const std::string filename("../data/APS2/calibrationCurves_APS2.dat");

/// Setup calibration curves
    constexpr size_t xnumber = 111;
    assert( (xnumber) %2 == 1);
    constexpr double bandSize = .01;
    constexpr double spread = 0.20;
    class ::perturbStruct *pertStruct = nullptr;
    pertStruct = new class perturbStruct(pStruct->N, xnumber, spread,
                                         l_min, l_max, iterates);
    pertStruct->lthermalBands(bandSize);

/// Initial guess
    double *xInitial = nullptr;
    xInitial = new double[5]
    {x_ini10(2.3), x_ini10(3.5), x_ini10(35), x_ini10(.8), x_ini10(0.57)};

    if(false)
    {
        /* There are three ways to layout the thermal spread.  The
        deterministic approach systematically varies the thermal penetration
        spread from lmin1 to lmin2 and lmax1 to lmax2.

        The lthermalMC() function results in a similar result; however, the
        selection of the lmin and lmax for each iteration is determined
        with a random simulation. The argument for teh lthermalMC() function
        provides the band resolution. */
        calibrationSweep(ParaEstSetting, &st_ptr, xInitial, pStruct, factorMax,
                         factorScale, pertStruct, filename, LendMinDecade);
    }

    /*At this point I can output a figure that has the sensitivity curve data
    for each of the five parameters. The figure with the artificial data and
    fitted curve with error bars will be shown next.*/
     ///Noise in Simulated Emission
    constexpr double a =  .01;   // max % error (%*pi/2) (try .025)
    constexpr double b = 2.95;   // stretching parameter  (try 2.95) (1->pi)
    constexpr bool d1 = true;    //positive  (try false)
    constexpr bool d2 = true;    //monotonic (try true)
    constexpr int s1 = 0;        //-1(left bias) 0(symmetric) +1(right bias)
    constexpr double noiseRandom = 0.005*0; // normal noise % of pi/2
    const class emissionNoiseParameters myEmissionNoise(a, b, d1, d2, s1,
                                                        noiseRandom);

    if(false)
    {
        /* Create Initial Experimental Data for figure */
        pStruct->thermalSetup(l_min, l_max, LendMinDecade);
        phase99(pStruct->L_end, pStruct, pStruct->emissionNominal);
        pStruct->EmissionNoise(myEmissionNoise, pStruct->emissionNominal, l_min,
                               l_max);
        fitting(pStruct->L_end, pStruct->N, ParaEstSetting, &st_ptr, pStruct,
                xInitial, 1, factorMax, factorScale);

        ///output data for printing
        std::ofstream myoutputfile;
        std::stringstream filename1;
        filename1 <<  "../data/APS2/experimentalFitted.dat";
        myoutputfile.open(filename1.str().c_str());
        myoutputfile << std::setprecision(8);

        for(size_t i = 0 ; i < pStruct->L_end; ++i)
        {
            myoutputfile << pStruct->laser->l_thermal[i] << "\t";
            myoutputfile << pStruct->emissionExperimental[i] << "\t";
            myoutputfile << pStruct->predicted[i] << "\t";
            myoutputfile << pStruct->emissionNominal[i] << "\n";
        }
        myoutputfile.close();
    }

///* Optimization Procedure for l-thermal  */
    if(true)
    {
        parameterUncertainty(pStruct->N, ParaEstSetting, &st_ptr, xInitial,
                             pStruct, factorMax, factorScale, pertStruct,
                             myEmissionNoise, filename);
        pertStruct->cleanup2();
        delete pertStruct;
    }
    delete[] xInitial;
}



}
