#include "Header.h"

int main( int /*argc*/, char** /*argv[]*/ )
{
  ///Setup global timer and start
  class stopwatch globalStopWatch;

  /// Setup configuration file
  const std::string filename = "config.xml";
  struct thermalAnalysisMethod::PopTea
    poptea( thermalAnalysisMethod::PopTea::loadConfig( filename ) );

/// Heat Transfer and Emission models
  const enum XParaNames xParametersNames[] = {asub, gammaEff, E1 ,R1, lambda};

/// Thermal Penetration
  constexpr double l_min = .04;  constexpr double l_max = 4;
  constexpr size_t LendMinDecade = 50;

  /// Parameter Estimation Constraints
  struct parameter_constraints paraConstraints;
  paraConstraints.a_sub_min = 1e-0;  paraConstraints.a_sub_max = 5;
  paraConstraints.gamma_min = 2e-0;  paraConstraints.gamma_max = 10;
  paraConstraints.E_sigma_min = 1;   paraConstraints.E_sigma_max = 200;
  paraConstraints.R1_min = 0.6;      paraConstraints.R1_max = 1;
  paraConstraints.lambda_min = .1;   paraConstraints.lambda_max = 1;
  paraConstraints.R0_min = 0;        paraConstraints.R0_max = 1;

  /// Input Directory Information
  poptea.thermalModel.iter = 1000;  poptea.LMA.LMA_workspace.MSETol = 1e-8;
  poptea.DataDirectory.mkdir("data");

  double *xInitial = nullptr; xInitial = new double[5]{2.1, 3.7, 40, 0.75, 0.5};
  for (size_t i=0; i < poptea.LMA.unknownParameters.Nsize(); ++i)
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
        poptea.LMA.LMA_workspace.emissionExperimental[nn] = poptea.LMA.LMA_workspace.emissionNominal[nn];
    }
    fitting(poptea.expSetup.laser.L_end, poptea.LMA.unknownParameters.Nsize(),
            poptea.LMA.Settings, &paraConstraints, poptea, xInitial, interants, 10, 5);
  }
  //Prepare figures and data for paper Sensitivity
//    SensitivityValdes2013::CC_APS2(poptea);
//    SensitivityValdes2013::figureSensitivityIntro(poptea);

// Clear memory
  delete[] xInitial;
  globalStopWatch.displayTime();

  return 0;
}
