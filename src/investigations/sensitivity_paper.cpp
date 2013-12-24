/*----------------------------------------------------------------------------*\
  ========                  |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |        
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  				|
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
#include "investigations/sensitivity_paper.h"

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

void figureSensitivityIntro(class thermalAnalysisMethod::PopTea poptea)
{
    /*
    This figure serves as an introduction to the sensitivity concept.  It will
    show (a) a nominal curve, (b) nominal curve with error (c) a fitted curve.
    It will also include a subplot with the error shown.

    To create these curves
    */
    poptea.expSetup.laser.L_end = LendMinDecade;

    ///heating constraints
    poptea.expSetup.q_surface = 0;

    ///Parameter Estimation Options
    poptea.LMA.LMA_workspace.MSETol = 1e-8;

    int nfev;
    int info = 0;

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
        poptea.thermalSetup(l_min, l_max, LendMinDecade);

        /// Populate the experimental phase values in parameters99
        Analytical_PhaseR1  = new double[poptea.expSetup.laser.L_end]();
        lthermalR1          = new double[poptea.expSetup.laser.L_end]();
        predictedR1         = new double[poptea.expSetup.laser.L_end]();
        emissionExpR1       = new double[poptea.expSetup.laser.L_end]();

        ///Populate arrays
        phase99(poptea, Analytical_PhaseR1);

        ///create artificial experimental data
//        pStruct->EmissionNoise(myEmissionNoise, Analytical_PhaseR1, l_min,
//                               l_max); //BUG

        ///estimate unknown parameters using full range
        double *xpredicted =
            new double[ poptea.LMA.unknownParameters.Nsize()];
        double *xInitial = nullptr;
        xInitial = new double[5]{2.3, 3.8, 42, 0.80, 0.57};    
        paramter_estimation(poptea.expSetup.laser.L_end,
                            poptea.LMA.unknownParameters.Nsize(),
                            ParaEstSetting, &info,
                            &nfev, xInitial, poptea, factorMax,
                            factorScale, xpredicted);
        delete [] xInitial;
        delete [] xpredicted;
        std::cout << info;

        /// populate the "predicted" array using the model and the new parameter
        /// estimations
        phase99(poptea, poptea.LMA.LMA_workspace.predicted);

        for(size_t i = 0; i < poptea.expSetup.laser.L_end; ++i)
        {
            lthermalR1[i]       = poptea.expSetup.laser.l_thermal[i];
            predictedR1[i]      = poptea.LMA.LMA_workspace.predicted[i];
            emissionExpR1[i]    = poptea.LMA.LMA_workspace.emissionExperimental[i];
        }

        LendR1 = poptea.expSetup.laser.L_end;
    }

    double *Analytical_PhaseR2 = nullptr;
    double *lthermalR2 = nullptr;
    double *predictedR2 = nullptr;
    double *emissionExpR2 = nullptr;

    {
        ///Reset properties
        poptea.TBCsystem.optical.Emit1 = 42;
        poptea.TBCsystem.optical.R1 = 0.8;

        poptea.TBCsystem.coating.lambda = 0.57;
        poptea.TBCsystem.updateCoat();

        ///Set heating constraints
        constexpr double l_min = .2;
        constexpr double l_max = .8;
        poptea.thermalSetup(l_min, l_max, LendMinDecade);
        LendR2 = poptea.expSetup.laser.L_end;

        /// Populate the experimental phase values in parameters99
        Analytical_PhaseR2  = new double[poptea.expSetup.laser.L_end]();
        lthermalR2          = new double[poptea.expSetup.laser.L_end]();
        predictedR2         = new double[poptea.expSetup.laser.L_end]();
        emissionExpR2       = new double[poptea.expSetup.laser.L_end]();

        ///Populate arrays
        phase99(poptea, Analytical_PhaseR2);

        ///create artificial experimental data
//        pStruct->EmissionNoise(myEmissionNoise, Analytical_PhaseR2, .04, 4); //BUG MUST IMPLEMENT

        ///estimate unknown parameters using full range
        double *xpredicted =
            new double[poptea.LMA.unknownParameters.Nsize()];
        double *xInitial = nullptr;
        xInitial = new double[5]{2.3, 3.8, 42, 0.80, 0.57};
        paramter_estimation(poptea.expSetup.laser.L_end,
                            poptea.LMA.unknownParameters.Nsize(),
                            ParaEstSetting, &info, &nfev, xInitial,
                            poptea, factorMax, factorScale, xpredicted);
        delete [] xInitial;
        delete [] xpredicted;
        std::cout << info;

        /// populate the "predicted" array using the model and the new parameter
        /// estimations
        phase99(poptea, poptea.LMA.LMA_workspace.predicted);
        LendR2 = poptea.expSetup.laser.L_end;

        for(size_t i = 0; i < LendR2; ++i)
        {
            lthermalR2[i]       = poptea.expSetup.laser.l_thermal[i];
            predictedR2[i]      = poptea.LMA.LMA_workspace.predicted[i];
            emissionExpR2[i]    = poptea.LMA.LMA_workspace.emissionExperimental[i];
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

void CC_APS2(class thermalAnalysisMethod::PopTea poptea)
{
    /* This function is designed to complete the following 5 steps:
     (1) to create the calibration curves for an APS sample
     (2) export data to a data-file
     (3) create experimental data and explort to data-file
     (4) fit the experimental data to the model
     (5) report parameteres and uncertainty using the calibration curves */
    poptea.DataDirectory.mkdir("data/APS2");
    poptea.expSetup.laser.L_end = LendMinDecade;

///Set heating constraints
    constexpr double l_min = .04;
    constexpr double l_max = 4;
    poptea.thermalSetup(l_min, l_max, LendMinDecade);

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
    const size_t N = poptea.LMA.unknownParameters.Nsize();
    pertStruct = new class perturbStruct(N, xnumber, spread,
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
        calibrationSweep(ParaEstSetting, xInitial, poptea, factorMax,
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
        poptea.thermalSetup(l_min, l_max, LendMinDecade);
        phase99(poptea, poptea.LMA.LMA_workspace.emissionNominal);
//        pStruct->EmissionNoise(myEmissionNoise, pStruct->emissionNominal, l_min,
//                               l_max); //BUG MUST IMPLEMENT
        fitting(poptea, xInitial, 1, factorMax, factorScale);

        ///output data for printing
        std::ofstream myoutputfile;
        std::stringstream filename1;
        filename1 <<  "../data/APS2/experimentalFitted.dat";
        myoutputfile.open(filename1.str().c_str());
        myoutputfile << std::setprecision(8);

        for(size_t i = 0 ; i < poptea.expSetup.laser.L_end; ++i)
        {
            myoutputfile << poptea.expSetup.laser.l_thermal[i] << "\t";
            myoutputfile << poptea.LMA.LMA_workspace.emissionExperimental[i] << "\t";
            myoutputfile << poptea.LMA.LMA_workspace.predicted[i] << "\t";
            myoutputfile << poptea.LMA.LMA_workspace.emissionNominal[i] << "\n";
        }
        myoutputfile.close();
    }

///* Optimization Procedure for l-thermal  */
    if(true)
    {
        parameterUncertainty(poptea.LMA.unknownParameters.Nsize(),
                             ParaEstSetting, xInitial,
                             poptea, factorMax, factorScale, pertStruct,
                             myEmissionNoise, filename);
        pertStruct->cleanup2();
        delete pertStruct;
    }
    delete[] xInitial;
}



}
