#ifndef POPTEA_HPP
#define POPTEA_HPP

enum XParaNames
{
    gammaEff,
    asub,
    E1,
    R1,
    lambda,
    R0
};

namespace thermalAnalysisMethod
{
  class PopTea
  {
  public:
    std::vector<enum XParaNames> xParametersNames;    //MUST BE REMOVED
    std::vector<enum XParaNames> xParameters95Names;  //MUST BE REMOVED
    size_t N95;                                       //MUST BE REMOVED

    class expEquipment::setup expSetup;
    class physicalModel::TBCsystem TBCsystem;
    class thermal::ThermalModelSelection thermalModel;
    class parameterEstimation::LMA LMA;
    class filesystem::directory DataDirectory;

    explicit PopTea( class expEquipment::setup expSetup_,
                     class physicalModel::TBCsystem TBCsystem_,
                     class thermal::ThermalModelSelection thermalModel_,
                     class parameterEstimation::settings Settings_,
                     class parameterEstimation::unknownList unknownParameters_,
                     class filesystem::directory DataDirectory_
                     );
    static thermalAnalysisMethod::PopTea
      loadConfig( const std::string &filename, class filesystem::directory DataDirectory_);

    ~PopTea( void );


  void thermalSetup( const double lmin_, const double lmax_, //MUST BE REMOVED
                     const size_t LendMin);                  //MUST BE REMOVED
  double bEval(void) const;                                 //MUST BE REMOVED
  };
}

#endif // POPTEA_HPP
