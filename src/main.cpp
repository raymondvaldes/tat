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

  /// Test loop
  //Many fit test
  if (true)
  {
    double *xInitial = nullptr;
    xInitial = new double[5]{2.1, 3.7, 40, 0.75, 0.5};

    constexpr size_t interants = 1;
    phase99(poptea, poptea.LMA.LMA_workspace.emissionNominal);

    for(size_t nn = 0; nn < poptea.expSetup.laser.L_end; ++nn )
    {
      poptea.LMA.LMA_workspace.emissionExperimental[nn]
            = poptea.LMA.LMA_workspace.emissionNominal[nn];
    }
    fitting(poptea, xInitial, interants, 10, 5);
    delete[] xInitial;
  }

  //Prepare figures and data for paper Sensitivity
//    SensitivityValdes2013::CC_APS2(poptea);
//    SensitivityValdes2013::figureSensitivityIntro(poptea);

  /// end
  globalStopWatch.displayTime();
  return 0;
}
