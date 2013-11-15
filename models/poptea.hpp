#ifndef POPTEA_HPP
#define POPTEA_HPP

namespace thermalAnalysisMethod
{
  class PopTea
  {
//    POPTEA
//    {
//      poptea <- lasersweep <- frequencies, omega, lmin, lmax
//      parameterEstimationArrays <- fvec...etc...
//    }
  public:
    class expEquipment::setup expSetup;
    class physicalModel::TBCsystem TBCsystem;
    class ThermalModelSelection thermalModel;
    struct parameterEstimation::settings Settings;
    class parameterEstimation::unknownList unknownParameters;
    struct parameterEstimation::LMA_workingArrays LMA_workspace;

    PopTea(class expEquipment::setup expSetup_,
           class physicalModel::TBCsystem TBCsystem_,
           class ThermalModelSelection thermalModel_,
           class parameterEstimation::settings Settings_,
           class parameterEstimation::unknownList unknownParameters_);

    double bEval(void);
  };
}

#endif // POPTEA_HPP
