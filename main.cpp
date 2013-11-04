#include "Header.h"

int main( int /*argc*/, char** /*argv[]*/ )
{
  ///Setup global timer
  class stopwatch globalStopWatch;

  /// Mesh Parameters
/*
   - beta1 set to a high number (5)
   - Ttol greater than -4 is not practical
   - iter is the total number of iterations
   - beta_iter is the total number of iterations to find beta2
   - beta_tol is how close dz_sub is to dz_coat   */
  constexpr size_t M2 = 220+1; //there must be a problem (KEEP AT 200)
  assert( (M2-1) %5 == 0);     // (M2-1 / 5) must be integer!! (assert)
  constexpr size_t Rend = 20; //80
  constexpr size_t Nend = 80;
  constexpr size_t N = 5;

/// Heat Transfer and Emission models
  const enum XParaNames
  xParametersNames[] = {asub, gammaEff, E1 ,R1, lambda};
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
  constexpr double epsfcn = 1.e-4;
  constexpr double factor =  10;
  constexpr int mode = 0;
  constexpr int nprint = 0;
  struct ParameterEstimation::settings
  ParaEstSetting(ftol, xtol, gtol, maxfev, epsfcn, factor, mode, nprint);

  pStruct->MSETol = 1e-8;
  pStruct->iterPE = 1;
  constexpr double factorMax = 10;
  constexpr double factorScale = 5;

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
//    pStruct->T_base = 273.15;
//    pStruct->T_rear = 0;
  constexpr double Ttol = 1e-3;
  constexpr double T_ref =  300;
  constexpr double T_base = 273.15;
  constexpr double T_rear = 0;
  struct physicalModel::temperatureScale
          TemperatureScale(Ttol, T_ref, T_base, T_rear);
  pStruct->TemperatureScale = &TemperatureScale;

  // Model system
  constexpr double detector_rad = .25e-3;
  constexpr double R_domain = detector_rad;
  pStruct->detector_rad = detector_rad;
  pStruct->R_domain = R_domain;

  constexpr double L_coat = 71.7e-6;
  pStruct->L_coat = L_coat;

  constexpr double L_substrate = L_coat *99;
  pStruct->L_substrate = L_substrate;
  pStruct->lambda = .57;
  pStruct->lambda_Sub = .1;

  pStruct->E_sigma = 42;

  //Optical Properties
  const double R0 = 0.2;
  const double R1 = 0.8;
  const double Emit1 = 42;
  struct physicalModel::radiativeSysProp radProp(R0, R1, Emit1);
  pStruct->opticalProp = &radProp;

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
  pStruct->detector_lam = 5e-6;

  pStruct->k1_thermal->offset = 1.44;
  pStruct->k2_thermal->offset = 12.7;

  pStruct->psi1_thermal->offset = 2.1e6;
  pStruct->psi2_thermal->offset = 3.44e6;

  pStruct->k1_thermal->slope = 0;
  pStruct->psi1_thermal->slope = 0;
  pStruct->k2_thermal->slope = 0;
  pStruct->psi2_thermal->slope = 0;

  /// Heat Flux
  /* - units [W/m^2] */
  constexpr double power     = 30   /*Watts*/ ;
  constexpr double radius    = 20e-4 /*m (500um)*/ ;
  constexpr double offset    = .95   /*offset*/ ;
  constexpr double amplitude = .05   /*amplitude*/;
  class expEquipment::Laser CO2Laser(power, radius, offset, amplitude);
  pStruct->laser = &CO2Laser;

  constexpr double detector_lam = 5e-6;
  struct expEquipment::Detector Emissiondetector(detector_lam, detector_rad);

  struct expEquipment::setup expSetup(CO2Laser, Emissiondetector);

  constexpr double kcoat_off = 1.44;
  constexpr double kcoat_slope = 0;
  struct property kthermalCoating(kcoat_off, kcoat_slope);

  constexpr double psicoat_off = 2.1e6;
  constexpr double psicoat_slope = 0;
  struct property psithermalCoating(psicoat_off, psicoat_slope);

  constexpr double lambdaCoat = 0.57;
  struct physicalModel::layer coating(kthermalCoating,
                                      psithermalCoating, L_coat, lambdaCoat);

  constexpr double ksub_off = 12.7;
  constexpr double ksub_slope = 0;
  struct property kthermalSubstrate(ksub_off, ksub_slope);

  constexpr double psisub_off = 3.44e6;
  constexpr double psisub_slope = 0;
  struct property psithermalSubstrate(psisub_off, psisub_slope);
  constexpr double lambdaSub = 0;
  struct physicalModel::layer substrate(kthermalSubstrate,
                                        psithermalSubstrate, L_substrate,
                                        lambdaSub);

  struct physicalModel::TBCsystem EBPVD(coating, substrate, TemperatureScale,
                                        radProp, R_domain);

  struct PopTea poptea(expSetup, EBPVD, thermalModel);


/// Thermal Penetration
  /* The thermal penetration depth represents the range of the 'operability
   * region'. LendMin is defined to be the minimum number of measurements or
   * the number of measurements per decade (logspace). Whichever is greater.*/
  constexpr double l_min = .04;
  constexpr double l_max = 4;
  constexpr size_t LendMinDecade = 50;
  pStruct->L_end = LendMinDecade;
  pStruct->q_surface = 0;

/// Parameter Estimation Constraints
  /* parameter constraints are stored in the
  structure parameter_constraints */
  struct parameter_constraints paraConstraints;
  paraConstraints.a_sub_min = 1e-0;
  paraConstraints.a_sub_max = 5;

  paraConstraints.gamma_min = 2e-0;
  paraConstraints.gamma_max = 10;

  paraConstraints.E_sigma_min = 1;
  paraConstraints.E_sigma_max = 200;

  paraConstraints.R1_min = 0.6;
  paraConstraints.R1_max = 1;

  paraConstraints.lambda_min = .1;
  paraConstraints.lambda_max = 1;

  paraConstraints.R0_min = 0;
  paraConstraints.R0_max = 1;

  //Create useful bounds for the parameter estimatio algorithms
  {
  struct parameterEstimation::constraints::bounds a_sub (1e-0, 5);
  struct parameterEstimation::constraints::bounds gamma (2e-0, 10);
  struct parameterEstimation::constraints::bounds E1emit(1,   200);
  struct parameterEstimation::constraints::bounds R1    (0.6, 1);
  struct parameterEstimation::constraints::bounds R0    (0,   1);
  struct parameterEstimation::constraints::bounds lambda(.1,  1);
  struct parameterEstimation::constraints paraConstraints(a_sub, gamma, E1emit,
                                                          R1, R0, lambda);
  }

  // Initial Guess
  double *xInitial = nullptr;
  xInitial = new double[5]{2.1, 3.7, 40, 0.75, 0.5};

//Optimize stretching in Substrate and declare variables to be fitted
  pStruct->parametersStrSetup(xParametersNames);

// Populate the experimental phase values in parameters99
  pStruct->thermalSetup(l_min, l_max, LendMinDecade);
  phase99(pStruct->L_end, pStruct, pStruct->emissionNominal);

//Many fit test
  if (true)
  {
      constexpr size_t interants = 1;
      for(size_t nn = 0; nn < pStruct->L_end; ++nn )
      {
          pStruct->emissionExperimental[nn] = pStruct->emissionNominal[nn];
      }
      fitting(pStruct->L_end, pStruct->N, ParaEstSetting, &paraConstraints,
              pStruct, xInitial, interants, factorMax, factorScale);
  }

//Prepare figures and data for paper Sensitivity
//    SensitivityValdes2013::CC_APS2(pStruct);
//    SensitivityValdes2013::figureSensitivityIntro(pStruct);

// Clear memory
  mesh->cleanup();
  delete mesh;
  CO2Laser.cleanup();

  delete[] xInitial;

  pStruct->cleanup();
  delete pStruct;


  globalStopWatch.displayTime();
  return 0;
}
