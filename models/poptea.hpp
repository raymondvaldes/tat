#ifndef POPTEA_HPP
#define POPTEA_HPP

namespace thermalAnalysisMethod
{
  class PopTea
  {
  public:
    class expEquipment::setup expSetup;
    class physicalModel::TBCsystem TBCsystem;
    class ThermalModel thermalModel;
    struct parameterEstimation::settings Settings;
    struct parameterEstimation::unknownList unknownParameters;

    PopTea(struct expEquipment::setup expSetup_,
           struct physicalModel::TBCsystem TBCsystem_,
           class ThermalModel thermalModel_,
           struct parameterEstimation::settings Settings_,
           struct parameterEstimation::unknownList unknownParameters_);

    double bEval(void);
  };
}

#endif // POPTEA_HPP
