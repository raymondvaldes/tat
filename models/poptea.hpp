#ifndef POPTEA_HPP
#define POPTEA_HPP

namespace thermalAnalysisMethod
{
  class PopTea
  {
  public:
    class expEquipment::setup expSetup;
    class physicalModel::TBCsystem TBCsystem;
    class ThermalModelSelection thermalModel;
    struct parameterEstimation::settings Settings;
    struct parameterEstimation::unknownList unknownParameters;

    PopTea(class expEquipment::setup expSetup_,
           class physicalModel::TBCsystem TBCsystem_,
           class ThermalModelSelection thermalModel_,
           class parameterEstimation::settings Settings_,
           class parameterEstimation::unknownList unknownParameters_);

    double bEval(void);
  };
}

#endif // POPTEA_HPP
