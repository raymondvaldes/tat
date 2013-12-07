#include "Header.h"

int main( int /*argc*/, char** /*argv[]*/ )
{
  ///Setup global timer and start
  class stopwatch globalStopWatch;

  /// Input file
  const std::string filename = "config.xml";


  // Create empty property tree object
  using boost::property_tree::ptree;
  ptree pt;
  read_xml(filename, pt);
  const double stuff = pt.get<double>( "poptea.experimentalSetup.Laser.power" );
  std::cout << stuff << "\n\n";
  exit(-3);

  class parameterEstimation::settings ParaEstSetting(filename);
  class physicalModel::temperatureScale TemperatureScale(filename);
  class physicalModel::radiativeSysProp radProp(filename);
  class expEquipment::Laser CO2Laser(filename);
  class expEquipment::Detector Emissiondetector(filename);

  class expEquipment::setup expSetup(CO2Laser, Emissiondetector);

  // Model system
  constexpr double kcoat_off = 1.44;
  constexpr double kcoat_slope = 0;
  class property kthermalCoating(kcoat_off, kcoat_slope);

  constexpr double psicoat_off = 2.1e6;
  constexpr double psicoat_slope = 0;
  class property psithermalCoating(psicoat_off, psicoat_slope);

  constexpr double L_coat = 71.7e-6;
  constexpr double lambdaCoat = 0.57;
  struct physicalModel::layer coating(kthermalCoating, psithermalCoating,
                                      L_coat, lambdaCoat);

  constexpr double ksub_off = 12.7;
  constexpr double ksub_slope = 0;
  struct property kthermalSubstrate(ksub_off, ksub_slope);

  constexpr double psisub_off = 3.44e6;
  constexpr double psisub_slope = 0;
  struct property psithermalSubstrate(psisub_off, psisub_slope);

  constexpr double L_substrate = L_coat *99;
  constexpr double lambdaSub = 0;
  struct physicalModel::layer substrate(kthermalSubstrate,
                                        psithermalSubstrate, L_substrate,
                                        lambdaSub);
  constexpr double R_domain = 0.25e-3;
  class physicalModel::TBCsystem EBPVD(coating, substrate, TemperatureScale,
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

  /// Initialize Mesh
  /// Mesh Parameters
/*
   - beta1 set to a high number (5)
   - Ttol greater than -4 is not practical
   - iter is the total number of iterations */

  constexpr size_t M2 = 220+1;
  constexpr size_t Rend = 20;
  constexpr size_t Nend = 80;
  constexpr double beta1 = 100;
  constexpr double split = 0.5;

  class numericalModel::Mesh mesh(M2, Rend, Nend, beta1, split,
                                  EBPVD.coating.depth,
                                  EBPVD.substrate.depth,
                                  expSetup.laser.radius,
                                  EBPVD.radius);

  class thermal::ThermalModelSelection
  thermalModel(thermal::ThermalModelSelection::HeatX::OneDimAnalytical,
               thermal::ThermalModelSelection::EmissionX::OneDimNonLin,
               mesh);

  struct thermalAnalysisMethod::PopTea poptea(expSetup,
                                              EBPVD,
                                              thermalModel,
                                              ParaEstSetting,
                                              unknownParameters);
//  struct thermalAnalysisMethod::PopTea poptea = InitilizeConfigFile();

  /// Input Directory Information
  poptea.thermalModel.iter = 1000;
  poptea.LMA.LMA_workspace.MSETol = 1e-8;
  poptea.DataDirectory.mkdir("data");

  // Initial Guess
  double *xInitial = nullptr;
  xInitial = new double[5]{2.1, 3.7, 40, 0.75, 0.5};

  /// Heat Transfer and Emission models
  const enum XParaNames
  xParametersNames[] = {asub, gammaEff, E1 ,R1, lambda};
  constexpr size_t N = 5;

  for (size_t i=0; i < N; ++i)
  {
    poptea.xParametersNames[i] = xParametersNames[i];
    poptea.xParameters95Names[i] = xParametersNames[i];
  }
// Populate the experimental phase values in parameters99
  poptea.expSetup.laser.L_end = LendMinDecade;
  poptea.expSetup.q_surface = 0;
  poptea.thermalSetup(l_min, l_max, LendMinDecade);

  phase99(poptea.expSetup.laser.L_end, poptea,
          poptea.LMA.LMA_workspace.emissionNominal);

  //Many fit test
  if (true)
  {
    constexpr size_t interants = 1;
    for(size_t nn = 0; nn < poptea.expSetup.laser.L_end; ++nn )
    {
        poptea.LMA.LMA_workspace.emissionExperimental[nn] =
            poptea.LMA.LMA_workspace.emissionNominal[nn];
    }
    constexpr double factorMax = 10;
    constexpr double factorScale = 5;
    fitting(poptea.expSetup.laser.L_end,
            poptea.LMA.unknownParameters.Nsize(),
            ParaEstSetting, &paraConstraints, poptea, xInitial, interants,
            factorMax, factorScale);
  }
  delete[] xInitial;

  //Prepare figures and data for paper Sensitivity
//    SensitivityValdes2013::CC_APS2(poptea);
//    SensitivityValdes2013::figureSensitivityIntro(poptea);


  globalStopWatch.displayTime();
  return 0;
}
