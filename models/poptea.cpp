#include "../Header.h"

namespace thermalAnalysisMethod
{

PopTea::PopTea(class expEquipment::setup expSetup_,
               class physicalModel::TBCsystem TBCsystem_,
               class ThermalModelSelection thermalModel_,
               class parameterEstimation::settings Settings_,
               class parameterEstimation::unknownList unknownParameters_)
  : expSetup(expSetup_),
    TBCsystem(TBCsystem_),
    thermalModel(thermalModel_),
    Settings(Settings_),
    unknownParameters(unknownParameters_),
    LMA(Settings_, unknownParameters_)
{
  const size_t d = unknownParameters.Nsize();
  xParametersNames   = new enum XParaNames[d];
  xParameters95Names = new enum XParaNames[d];
  N95 = d;
}

PopTea::~PopTea(void)
{
  delete [] xParametersNames;
  delete [] xParameters95Names;
}


void PopTea::thermalSetup(const double lmin_, const double lmax_,
                                const size_t LendMin)
{
  L_end = expSetup.laser.thermalSetup(lmin_, lmax_,
                                      TBCsystem.coating.depth,
                                      TBCsystem.coating.kthermal.offset,
                                      TBCsystem.coating.psithermal.offset ,
                                      LendMin);
  LMA_workspace.updateArraySize(L_end, unknownParameters.Nsize());
}

double PopTea::bEval(void)
{
  return expSetup.laser.radius / TBCsystem.coating.depth;
}

}
