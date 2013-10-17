// ThermalProp_Analysis
// Raymond Valdes
// Change log
// Version 0.130108
#include "Header.h"


int main( int argc, char *argv[] )
{
/// Mesh Parameters
/*
     - beta1 set to a high number (5)
     - Ttol greater than -4 is not practical
     - iter is the total number of iterations
     - beta_iter is the total number of iterations to find beta2
     - beta_tol is how close dz_sub is to dz_coat   */
    constexpr size_t M2 = 200+1; //there must be a problem (KEEP AT 200)
    assert( (M2-1) %5 == 0);     // (M2-1 / 5) must be integer!! (assert)

    constexpr size_t Rend = 20; //80
    constexpr size_t Nend = 20;
    constexpr size_t N = 5;

/// Heat Transfer and Emission models
    const enum XParaNames
    xParametersNames[] = {asub, gammaEff, E1, R1, lambda };

    class ThermalModel
    thermalModel(ThermalModel::HeatX::OneDimAnalytical,
                 ThermalModel::EmissionX::OneDimNonLin);

/// Initialize Mesh
    constexpr double beta1 = 100;
    constexpr double split = 0.5;
    class Mesh *mesh = new Mesh(M2, Rend, Nend, beta1, split);


/// Parameter Structure
    struct parameterStr *pStruct =
    new struct parameterStr(N      /*N*/,
                            mesh);
    pStruct->thermalModel = &thermalModel;

    pStruct->Ttol = 1e-3;  //keep this at 1e-3
    pStruct->iter = 1000;

/// Input Directory Information
    pStruct->dir = filesystem::workingDir();
    filesystem::makeDir(pStruct->dir, "data");

/////Parameter Estimation Options
    /* - N number of thermal parameters to be fitted
     - ftol difference in error
     - xtol difference in parameters
     - beta_iter is the total number of iterations to find beta2
     - beta_tol is how close dz_sub is to dz_coat */
    constexpr double ftol = 1.e-8;
    constexpr double xtol = 1.e-8;
    constexpr double gtol = 1.e-8;
    constexpr size_t maxfev = 1e5;

    constexpr double epsfcn = 1.e-2;
    constexpr double factor =  .01;

    pStruct->MSETol = 1e-8;
    pStruct->iterPE = 1;

    constexpr double factorMax = .01;
    constexpr double factorScale = 5;

    constexpr int mode = 1;
    constexpr int nprint = 0;

///  Physical Properties
    /*
     - L_coat = 71.7e-6 71.7e-6 [m]
     - L_substrate = L_coat *67.;
     - lambda ..optical penetration (bug when lambda > 5)
     - R0 no effect on solution
     - Reflection; R0 at surface; R1 at interface
     - E_sigma //ratio of substrate emissivity to optical thickness of the film,
     - thermal contact resistance per area
    */
    pStruct->detector_rad = .25e-3;
    pStruct->L_coat = 71.7e-6;
    pStruct->R_domain = pStruct->detector_rad;
    pStruct->L_substrate = pStruct->L_coat *99;
    pStruct->lambda = .57;
    pStruct->lambda_Sub = .1;
    pStruct->R0 = 0.2;
    pStruct->R1 = 0.8;
    pStruct->E_sigma = 42;
    pStruct->Rtc = 1e-14;

/// Heat Flux
    /* - units [W/m^2] */
    class Laser CO2Laser(30   /*Watts*/  ,
                         20e-4 /*m (500um)*/ ,
                         .95   /*offset*/ ,
                         .05   /*amplitude*/);
    pStruct->laser = &CO2Laser;


/// Thermal Properties
    /*
     - T_ref    273 use substrate as reference [K]
     - k_ref    12.7 use substrate as reference [W/mK]
     - psi_ref  3.44 use substrate as reference [J/m^3/K]
     - T_base   temperature of thermal reservoir [K]
     - T_ref    273 use substrate as reference [K]
     - detector_lam 5um detector wavelength
     - k_c     1.44 coating conductivity [W/mK]
     - psi_c   2.1e6 coating volumetric heat capacity [J/m^3/K]
     - coating volumetric heat capacity [J/m^3/K]
     - k = m_k * T + b_k
    */
    pStruct->T_ref = 300;

    pStruct->k1_thermal->offset = 1.44;
    pStruct->k2_thermal->offset = 12.7;

    pStruct->psi1_thermal->offset = 2.1e6;
    pStruct->psi2_thermal->offset = 3.44e6;

    pStruct->T_base = 273.15;
    pStruct->T_rear = 0;
    pStruct->detector_lam = 5e-6;

    pStruct->k1_thermal->slope = 0;
    pStruct->psi1_thermal->slope = 0;
    pStruct->k2_thermal->slope = 0;
    pStruct->psi2_thermal->slope = 0;


/// Thermal Penetration
    /*
        The thermal penetration depth represents the range of the
        'operability region'.
        LendMin is defined to be the minimum number of measurements or the
        number of measurements per decade (logspace).  Whichever is greater.
    */
    constexpr double l_min = .04;
    constexpr double l_max = 4;
    constexpr size_t LendMinDecade = 50;
    pStruct->L_end = LendMinDecade;
    pStruct->q_surface = 0;

/// Solver option
/*
 - Print_0_Fit_1
        0 - print emission,
        1 - read saved emission from file and fit to saved emission
 - temp_output
        0-no
        1-yes
 - e_model
        0-linear
        1-nonlinear
        2-both
 - prop_linearity
    0-nonlinear
    1-linear (MUST DEBUG NONLINEAR)
*/
    pStruct-> temp_output = 0;
    pStruct-> e_model = 0;
    pStruct-> prop_linearity = 1;

/// Parameter Estimation Constraints
/*
    parameter constraints are stored in the
    structure parameter_constraints
*/
    struct parameter_constraints *st_ptr;
    st_ptr = new struct parameter_constraints;

    st_ptr->a_sub_min = 1e-0;
    st_ptr->a_sub_max = 5;

    st_ptr->gamma_min = 2e-0;
    st_ptr->gamma_max = 10;

    st_ptr->E_sigma_min = 1e-3;
    st_ptr->E_sigma_max = 200;

    st_ptr->R1_min = 0.6;
    st_ptr->R1_max = 1;

    st_ptr->lambda_min = .1;
    st_ptr->lambda_max = 1;

    st_ptr->R0_min = 0;
    st_ptr->R0_max = 1;

    // Initial Guess
        double *xInitial;
        xInitial = new double[5]{2.3, 3.8, 42, 0.80, 0.57};

//Optimize stretching in Substrate and declare variables to be fitted
    pStruct->parametersStrSetup(xParametersNames);

//// Populate the experimental phase values in parameters99
    pStruct->thermalSetup(l_min, l_max, LendMinDecade);
    phase99(pStruct->L_end, pStruct, pStruct->emissionNominal);


 //Many fit test
    if (true)
    {
        constexpr size_t interants = 1;
        for(size_t nn = 0; nn < pStruct->L_end; ++nn )
        {
            pStruct->emissionExperimental[nn]
                    = pStruct->emissionNominal[nn];
        }

        fitting(pStruct->L_end, pStruct->N, ftol, xtol, gtol, maxfev, epsfcn,
                mode, factor, nprint, st_ptr, pStruct, xInitial,
                interants, factorMax, factorScale);
    }

//Prepare figures and data for paper Sensitivity
    SensitivityValdes2013::CC_APS2(pStruct);
//    SensitivityValdes2013::figureSensitivityIntro(pStruct);

// Clear memory
    mesh->cleanup();
    delete mesh;
    CO2Laser.cleanup();

    delete[] xInitial;
    delete st_ptr;

    pStruct->cleanup();
    delete pStruct;


    return 0;
}
