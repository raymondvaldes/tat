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
#include "investigations/sensitivity_paper.h"
#include "thermal/emission/noise.hpp"
#include "thermal/emission/phase99.hpp"

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
class math::estimation::settings
ParaEstSetting(ftol, xtol, gtol, maxfev, epsfcn, factor, mode, nprint);

constexpr double factorMax = 1;
constexpr double factorScale = 5;
constexpr size_t LendMinDecade = 50;

//void figureSensitivityIntro(class thermal::analysis::Kernal popteaCore)
//{
//    /*
//    This figure serves as an introduction to the sensitivity concept.  It will
//    show (a) a nominal curve, (b) nominal curve with error (c) a fitted curve.
//    It will also include a subplot with the error shown.

//    To create these curves
//    */
//    popteaCore.expSetup.laser.L_end = LendMinDecade;

//    ///heating constraints
//    popteaCore.expSetup.q_surface = 0;

//    ///Parameter Estimation Options
//    popteaCore.LMA.LMA_workspace.MSETol = 1e-8;

//    int nfev;
//    int info = 0;

//    ///Noise in Simulated Emission
//    constexpr double a =  .05;      // max % error (%*pi/2) (try .025)
//    constexpr double b = 2.8;       // stretching parameter  (try 2.95) (1->pi)
//    constexpr bool d1 = false;       //positive  (try false)
//    constexpr bool d2 = true;        //monotonic (try true)
//    constexpr int s1 = 0;            //-1(left bias) 0(symmetric) +1(right bias)
//    constexpr double noiseRandom = 0.004; // normal noise % of pi/2
//    const class thermal::emission::ExpNoiseSetting
//        myEmissionNoise(a, b, d1, d2, s1, noiseRandom);

////    double *Analytical_PhaseR1 = nullptr;
//    std::vector<double> Analytical_PhaseR1;

//    double *lthermalR1 = nullptr;
//    double *predictedR1 = nullptr;
//    double *emissionExpR1 = nullptr;

//    size_t LendR1, LendR2;
//    {
//        ///Set heating constraints
//        constexpr double l_min = .04;
//        constexpr double l_max = 4;
//        popteaCore.thermalSetup(l_min, l_max, LendMinDecade);

//        /// Populate the experimental phase values in parameters99
////        Analytical_PhaseR1  = new double[popteaCore.expSetup.laser.L_end]();
//        Analytical_PhaseR1.resize(popteaCore.expSetup.laser.L_end);

//        lthermalR1          = new double[popteaCore.expSetup.laser.L_end]();
//        predictedR1         = new double[popteaCore.expSetup.laser.L_end]();
//        emissionExpR1       = new double[popteaCore.expSetup.laser.L_end]();

//        ///Populate arrays
//        thermal::emission::phase99(popteaCore, Analytical_PhaseR1);

//        ///create artificial experimental data
////        pStruct->EmissionNoise(myEmissionNoise, Analytical_PhaseR1, l_min,
////                               l_max); //BUG

//        ///estimate unknown parameters using full range
//        double *xpredicted =
//            new double[ popteaCore.LMA.unknownParameters.Nsize()];
//        double *xInitial = nullptr;
//        xInitial = new double[5]{2.3, 3.8, 42, 0.80, 0.57};
//        paramter_estimation(popteaCore.expSetup.laser.L_end,
//                            popteaCore.LMA.unknownParameters.Nsize(),
//                            ParaEstSetting, &info,
//                            &nfev, xInitial, popteaCore, factorMax,
//                            factorScale, xpredicted);
//        delete [] xInitial;
//        delete [] xpredicted;
//        std::cout << info;

//        /// populate the "predicted" array using the model and the new parameter
//        /// estimations
//        thermal::emission::phase99(popteaCore, popteaCore.LMA.LMA_workspace.predicted);

//        for(size_t i = 0; i < popteaCore.expSetup.laser.L_end; ++i)
//        {
//          lthermalR1[i]       = popteaCore.expSetup.laser.l_thermal[i];
//          predictedR1[i]      = popteaCore.LMA.LMA_workspace.predicted[i];
//          emissionExpR1[i]    = popteaCore.LMA.LMA_workspace.emissionExperimental[i];
//        }

//        LendR1 = popteaCore.expSetup.laser.L_end;
//    }

////    double *Analytical_PhaseR2 = nullptr;
//    std::vector<double> Analytical_PhaseR2;


//    double *lthermalR2 = nullptr;
//    double *predictedR2 = nullptr;
//    double *emissionExpR2 = nullptr;

//    {
//        ///Reset properties
//        popteaCore.TBCsystem.optical.Emit1 = 42;
//        popteaCore.TBCsystem.optical.R1 = 0.8;

//        popteaCore.TBCsystem.coating.lambda = 0.57;
//        popteaCore.TBCsystem.updateCoat();

//        ///Set heating constraints
//        constexpr double l_min = .2;
//        constexpr double l_max = .8;
//        popteaCore.thermalSetup(l_min, l_max, LendMinDecade);
//        LendR2 = popteaCore.expSetup.laser.L_end;

//        /// Populate the experimental phase values in parameters99
////        Analytical_PhaseR2  = new double[popteaCore.expSetup.laser.L_end]();
//        Analytical_PhaseR2.resize(popteaCore.expSetup.laser.L_end);

//        lthermalR2          = new double[popteaCore.expSetup.laser.L_end]();
//        predictedR2         = new double[popteaCore.expSetup.laser.L_end]();
//        emissionExpR2       = new double[popteaCore.expSetup.laser.L_end]();

//        ///Populate arrays
//        thermal::emission::phase99(popteaCore, Analytical_PhaseR2);

//        ///create artificial experimental data
////        pStruct->EmissionNoise(myEmissionNoise, Analytical_PhaseR2, .04, 4); //BUG MUST IMPLEMENT

//        ///estimate unknown parameters using full range
//        double *xpredicted =
//            new double[popteaCore.LMA.unknownParameters.Nsize()];
//        double *xInitial = nullptr;
//        xInitial = new double[5]{2.3, 3.8, 42, 0.80, 0.57};
//        paramter_estimation(popteaCore.expSetup.laser.L_end,
//                            popteaCore.LMA.unknownParameters.Nsize(),
//                            ParaEstSetting, &info, &nfev, xInitial,
//                            popteaCore, factorMax, factorScale, xpredicted);
//        delete [] xInitial;
//        delete [] xpredicted;
//        std::cout << info;

//        /// populate the "predicted" array using the model and the new parameter
//        /// estimations
//        thermal::emission::phase99(popteaCore, popteaCore.LMA.LMA_workspace.predicted);
//        LendR2 = popteaCore.expSetup.laser.L_end;

//        for(size_t i = 0; i < LendR2; ++i)
//        {
//          lthermalR2[i]     = popteaCore.expSetup.laser.l_thermal[i];
//          predictedR2[i]    = popteaCore.LMA.LMA_workspace.predicted[i];
//          emissionExpR2[i]  = popteaCore.LMA.LMA_workspace.emissionExperimental[i];
//        }
//    }

//    ///Print stuff

//    std::ofstream myfile;
//    std::stringstream filename;
//    filename <<  "data/figureSensitivityIntro.dat";
//    myfile.open(filename.str().c_str());
//    myfile << std::setprecision(8);

//    for(size_t i = 0; i < LendR1; ++i)
//    {
//        myfile << lthermalR1[i] << "\t";
//        myfile << Analytical_PhaseR1[i] << "\t" ;
//        myfile << emissionExpR1[i] << "\t";
//        myfile << predictedR1[i] << "\t";

//        if( i < LendR2 )
//        {
//            myfile << lthermalR2[i] << "\t";
//            myfile << Analytical_PhaseR2[i] << "\t" ;
//            myfile << emissionExpR2[i] << "\t";
//            myfile << predictedR2[i] ;
//        }
//        myfile << "\n";
//    }
//    myfile.close();


//    delete []lthermalR1;
////    delete []Analytical_PhaseR1;
//    delete []predictedR1;
//    delete []emissionExpR1;

//    delete []lthermalR2;
////    delete []Analytical_PhaseR2;
//    delete []predictedR2;
//    delete []emissionExpR2;
//}





}
