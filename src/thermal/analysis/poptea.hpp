/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef poptea_HPP
#define poptea_HPP

#include <vector>
#include <boost/property_tree/ptree.hpp>

#include "thermal/analysis/pie.hpp"
#include "thermal/analysis/methods.hpp"
#include "units.h"

namespace thermal {
namespace analysis{

class Poptea: public baseData
{
private:
  bool loadedExperimental = false;
  bool runbestfit = false;
  methods analysis;
  

  class ExperimentalData{
    public:
      class uniqueMeasurement{
        public:
          const units::quantity<units::frequency_dimension> heatingFrequency;
          const units::quantity<units::length_dimension> heatingWavelength;
          const units::quantity<units::length_dimension> detectorWavelength;
        
          const units::quantity<units::dimensionless_type> modulatorAmplitude;
          const units::quantity<units::dimensionless_type> laserWidth;
          const units::quantity<units::dimensionless_type> referenceAmplitude;
          const units::quantity<units::dimensionless_type> referenceArgument;

          const units::quantity<units::dimensionless_type> signalArgument;
          const units::quantity<units::dimensionless_type> signal2NoiseRatio;
          const units::quantity<units::dimensionless_type> runningSignal2NoiseRatio;
          const units::quantity<units::amount_dimension> signalsAveraged;
          const units::quantity<units::electric_potential_dimension> signalAmplitude;
          const units::quantity<units::electric_potential_dimension> signalUncertainty;
        
          const units::quantity<units::amount_dimension> signalSamples;
          const units::quantity<units::time_dimension> signalMeasurementTime;
          const units::quantity<units::electric_potential_dimension> signalGround;
      };
    
      explicit ExperimentalData(void);
    
    private:
  };


public:
  /// constructors and object creators
  explicit Poptea(
      const Kernal &coreSystem_ ,
      const ThermalData &thermaldata_,
      const math::estimation::unknownList &unknownParameters_,
      const methods analysis_in ) noexcept;

  static Poptea loadConfig( const Kernal &coreSystem_,
                            const boost::property_tree::ptree &pt ) noexcept;
  static Poptea loadConfigfromFile( const filesystem::directory &dir ) noexcept;
  ~Poptea( void ) noexcept;

  /// Member operations that update on multiple members
  void updateExperimentalData( const std::vector<double> &omegas,
                               const std::vector<double> &input ) noexcept;
  void updateModelData( const std::vector<double> &omegas ,
                        const std::vector<double> &input    ) noexcept;
  auto loadTBDfile( const filesystem::directory &dir,
                    const std::string& inputFileName )
    -> std::vector< units::quantity<units::si::electric_potential >> ;
  
  

  /// Operations that give results
  double bestFit( void ) noexcept;
  thermal::analysis::PIE::PIEAnalysisOutput PIE( void ) noexcept;
  ThermalSweepOptimizer::OptimizerOutput optimization( void ) noexcept;
  std::string thermalSweepMap(void ) noexcept;
  std::vector<double> thermalSweep( void ) const noexcept;
  void taylor_uncertainty( void ) noexcept;

  /// Reload kernels
  void reloadAnalysis( const methods &analysis_in ) noexcept;
  void reloadThermalModel( const thermal::define::construct &in_ ) noexcept;

  /// Printers
  std::string ppThermalData( void ) noexcept;
  std::string ppUnknownParameters( void ) noexcept;
} ;

Poptea loadWorkingDirectoryPoptea( const filesystem::directory &dir,
                                   const Kernal &popteaCore ) noexcept;
}}
#endif // poptea_HPP
