#include "../Header.h"


PopTea::PopTea(struct expEquipment::setup expSetup_,
       struct physicalModel::TBCsystem TBCsystem_, ThermalModel thermalModel_)
  :expSetup(expSetup_), TBCsystem(TBCsystem_), thermalModel(thermalModel_)
{}
