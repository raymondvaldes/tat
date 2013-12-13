#include "Header.h"

int main( int /*argc*/, char* argv[] )
{
  class stopwatch globalStopWatch;

  /// Figure out working directory
  namespace bf = boost::filesystem;
  const bf::path pProgram(bf::system_complete(argv[0]));
  class filesystem::directory DataDirectory(pProgram.parent_path().string());

  /// poptea by inputting configuration files
  const std::string filename = "config.xml";
  class thermalAnalysisMethod::PopTea
    poptea( thermalAnalysisMethod::PopTea::loadConfig(
              DataDirectory.abs(filename),DataDirectory ) );

  phase99(poptea.expSetup.laser.L_end, poptea,
          poptea.LMA.LMA_workspace.emissionNominal);

  /// Input Directory Information
  double *xInitial = nullptr;
  xInitial = new double[5]{2.1, 3.7, 40, 0.75, 0.5};

  //Many fit test
  if (true)
  {
    constexpr size_t interants = 1;

    for(size_t nn = 0; nn < poptea.expSetup.laser.L_end; ++nn )
    {
      poptea.LMA.LMA_workspace.emissionExperimental[nn]
            = poptea.LMA.LMA_workspace.emissionNominal[nn];
    }
    fitting(poptea, xInitial, interants, 10, 5);
  }

  //Prepare figures and data for paper Sensitivity
//    SensitivityValdes2013::CC_APS2(poptea);
//    SensitivityValdes2013::figureSensitivityIntro(poptea);

// Clear memory
  delete[] xInitial; globalStopWatch.displayTime();
  return 0;
}
