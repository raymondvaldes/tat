#ifndef POPTEA_HPP
#define POPTEA_HPP

namespace thermalAnalysisMethod
{
  class PopTea
  {
  public:
    enum XParaNames *xParameters95Names;  //MUST BE REMOVEd
    enum XParaNames *xParametersNames;    // MUST BE REMOVED
    size_t N95;                           //MUST BE REMOVED
    size_t L_end;                         //MUST BE REMOVED
    size_t N;

    class expEquipment::setup expSetup;
    class physicalModel::TBCsystem TBCsystem;
    class ThermalModelSelection thermalModel;

//    struct parameterEstimation::settings Settings;
    class parameterEstimation::unknownList unknownParameters;
    class parameterEstimation::LMA_workingArrays LMA_workspace;

    class parameterEstimation::LMA LMA;

    PopTea(class expEquipment::setup expSetup_,
           class physicalModel::TBCsystem TBCsystem_,
           class ThermalModelSelection thermalModel_,
           class parameterEstimation::settings Settings_,
           class parameterEstimation::unknownList unknownParameters_);
    ~PopTea(void);


  void thermalSetup(const double lmin_, const double lmax_,
                    const size_t LendMin); //MUST BE REMOVED
  double bEval(void); //MUST BE REMOVED
  };
}

#endif // POPTEA_HPP
