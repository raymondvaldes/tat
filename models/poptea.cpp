#include "../Header.h"

namespace thermalAnalysisMethod
{

PopTea::PopTea(struct expEquipment::setup expSetup_,
               struct physicalModel::TBCsystem TBCsystem_,
               class ThermalModel thermalModel_,
               struct parameterEstimation::settings Settings_,
               struct parameterEstimation::unknownList unknownParameters_)
  : expSetup(expSetup_),
    TBCsystem(TBCsystem_),
    thermalModel(thermalModel_),
    Settings(Settings_),
    unknownParameters(unknownParameters_)
{}

double PopTea::bEval(void)
{
  return expSetup.laser.radius / TBCsystem.coating.depth;
}

}
