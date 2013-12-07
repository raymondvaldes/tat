#include "../Header.h"

namespace thermalAnalysisMethod
{





PopTea::PopTea(class expEquipment::setup expSetup_,
               class physicalModel::TBCsystem TBCsystem_,
               class thermal::ThermalModelSelection thermalModel_,
               class parameterEstimation::settings Settings_,
               class parameterEstimation::unknownList unknownParameters_)
  : expSetup(expSetup_),
    TBCsystem(TBCsystem_),
    thermalModel(thermalModel_),
    LMA(Settings_, unknownParameters_)
{
  const size_t d = LMA.unknownParameters.Nsize();

  xParametersNames.resize(d);
  xParameters95Names.resize(d);
  N95 = d;
}

PopTea::~PopTea(void){}


void PopTea::thermalSetup(const double lmin_, const double lmax_,
                                const size_t LendMin)
{
  expSetup.laser.L_end = expSetup.laser.thermalSetup(lmin_, lmax_,
                                      TBCsystem.coating.depth,
                                      TBCsystem.coating.kthermal.offset,
                                      TBCsystem.coating.psithermal.offset ,
                                      LendMin);

  LMA.LMA_workspace.updateArraySize(expSetup.laser.L_end,
                                    LMA.unknownParameters.Nsize());
}

double PopTea::bEval(void) const
{
  return expSetup.laser.radius / TBCsystem.coating.depth;
}

}
