#include "Header.h"

int main( int /*argc*/, char** /*argv[]*/ )
{
  ///Setup global timer and start
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
  class thermal::ThermalModelSelection
  thermalModel(thermal::ThermalModelSelection::HeatX::OneDimAnalytical,
               thermal::ThermalModelSelection::EmissionX::OneDimNonLin);

/// Initialize Mesh
  constexpr double beta1 = 100;
  constexpr double split = 0.5;

/// Parameter Structure
  struct parameterStr *pStruct =
  new struct parameterStr;

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
  struct parameterEstimation::settings
  ParaEstSetting(ftol, xtol, gtol, maxfev, epsfcn, factor, mode, nprint);

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
  constexpr double Ttol = 1e-3;
  constexpr double T_ref =  300;
  constexpr double T_base = 273.15;
  constexpr double T_rear = 0;
  struct physicalModel::temperatureScale
          TemperatureScale(Ttol, T_ref, T_base, T_rear);

  // Model system
  constexpr double detector_rad = .25e-3;
  constexpr double R_domain = detector_rad;
  constexpr double L_coat = 71.7e-6;
  constexpr double L_substrate = L_coat *99;

  //Optical Properties
  const double R0 = 0.2;
  const double R1 = 0.8;
  const double Emit1 = 42;
  struct physicalModel::radiativeSysProp radProp(R0, R1, Emit1);

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

  /// Heat Flux
  /* - units [W/m^2] */
  constexpr double power     = 30   /*Watts*/ ;
  constexpr double radius    = 20e-4 /*m (500um)*/ ;
  constexpr double offset    = .95   /*offset*/ ;
  constexpr double amplitude = .05   /*amplitude*/;
  class expEquipment::Laser CO2Laser(power, radius, offset, amplitude);

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
  struct physicalModel::layer coating(kthermalCoating, psithermalCoating,
                                      L_coat, lambdaCoat);

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

/// Thermal Penetration
  /* The thermal penetration depth represents the range of the 'operability
   * region'. LendMin is defined to be the minimum number of measurements or
   * the number of measurements per decade (logspace). Whichever is greater.*/
  constexpr double l_min = .04;
  constexpr double l_max = 4;
  constexpr size_t LendMinDecade = 50;

  /// Parameter Estimation Constraints
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

  using pNames = physicalModel::labels::Name;
  struct parameterEstimation::unknownList unknownParameters;
  unknownParameters.addUnknown(pNames::asub,        1e-0, 5);
  unknownParameters.addUnknown(pNames::gammaEff,    2e-0, 10);
  unknownParameters.addUnknown(pNames::E1,          1,   200);
  unknownParameters.addUnknown(pNames::R1,          0.6, 1);
  unknownParameters.addUnknown(pNames::lambda,      .1,  1);

  struct thermalAnalysisMethod::PopTea poptea(expSetup, EBPVD,
                                              thermalModel, ParaEstSetting,
                                              unknownParameters);
  poptea.thermalModel.iter = 1000;
  /// Input Directory Information
  poptea.dir = filesystem::workingDir();
  filesystem::makeDir(poptea.dir, "data");

  //Optimize stretching in Substrate and declare variables to be fitted
  class Mesh *mesh = new Mesh(M2, Rend, Nend, beta1, split,
                              poptea.TBCsystem.coating.depth,
                              poptea.TBCsystem.substrate.depth,
                              poptea.expSetup.laser.radius,
                              poptea.TBCsystem.radius);
  poptea.thermalModel.mesh = mesh;
  poptea.LMA.LMA_workspace.MSETol = 1e-8;

  // Initial Guess
  double *xInitial = nullptr;
  xInitial = new double[5]{2.1, 3.7, 40, 0.75, 0.5};

  for (size_t i=0; i < N; ++i)
  {
    poptea.xParametersNames[i] = xParametersNames[i];
    poptea.xParameters95Names[i] = xParametersNames[i];
  }

// Populate the experimental phase values in parameters99
  poptea.expSetup.laser.L_end = LendMinDecade;
  poptea.expSetup.q_surface = 0;
  poptea.thermalSetup(l_min, l_max, LendMinDecade);

  pStruct->poptea = &poptea;
  phase99(pStruct->poptea->expSetup.laser.L_end, pStruct,
          pStruct->poptea->LMA.LMA_workspace.emissionNominal);



  //Many fit test
  if (true)
  {
    constexpr size_t interants = 1;
    for(size_t nn = 0; nn < pStruct->poptea->expSetup.laser.L_end; ++nn )
    {
        pStruct->poptea->LMA.LMA_workspace.emissionExperimental[nn] =
            pStruct->poptea->LMA.LMA_workspace.emissionNominal[nn];
    }

    fitting(pStruct->poptea->expSetup.laser.L_end,
            pStruct->poptea->LMA.unknownParameters.Nsize(),
            ParaEstSetting, &paraConstraints, pStruct, xInitial, interants,
            factorMax, factorScale);
  }

  //Prepare figures and data for paper Sensitivity
//    SensitivityValdes2013::CC_APS2(pStruct);
//    SensitivityValdes2013::figureSensitivityIntro(pStruct);


// Clear memory
  delete mesh;
  delete[] xInitial;
  delete pStruct;

  globalStopWatch.displayTime();
  return 0;
}
