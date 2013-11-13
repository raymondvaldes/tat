#ifndef POPTEA_HPP
#define POPTEA_HPP

namespace thermalAnalysisMethod
{
    struct PopTea
    {
      struct expEquipment::setup expSetup;
      struct physicalModel::TBCsystem TBCsystem;
      class ThermalModel thermalModel;
      struct parameterEstimation::settings Settings;
      struct parameterEstimation::unknownList unknownParameters;

//      struct emission model and heat model
//      parameter estimation settings - this means ftol etc
//      parameter estimation algorithms -
//      parameter estimation constraints
      PopTea(struct expEquipment::setup expSetup_,
             struct physicalModel::TBCsystem TBCsystem_,
             class ThermalModel thermalModel_,
             struct parameterEstimation::settings Settings_,
             struct parameterEstimation::unknownList unknownParameters_);
    };
}

#endif // POPTEA_HPP
