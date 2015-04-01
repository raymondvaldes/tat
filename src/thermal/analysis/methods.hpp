/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef METHODS_HPP
#define METHODS_HPP

#include <string>
#include <vector>
#include <memory>
#include <boost/property_tree/ptree.hpp>

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/analysis/pie.hpp"
#include "thermal/analysis/thermalsweepoptimizer.hpp"
#include "thermal/analysis/gum_uncertainty.h"

namespace thermal{
namespace analysis{

class methods
{
private:
  /// working objects
  std::shared_ptr< LMA > bestfitMethod;
  std::shared_ptr< PIE > intervalEstimates;
  std::shared_ptr< ThermalSweepOptimizer > lthermalSweepOptimizer;
  std::shared_ptr< Taylor_uncertainty > taylor_uncertainty;

public:
  //constructors
  explicit methods( const math::estimation::settings &Settings_in,
      const math::estimation::unknownList &unknownParameters_in,
      const ThermalData& thermalData_in,
      const math::estimation::unknownList &thermalSweepSearch_in,
      const std::vector<thermal::model::labels> &sweepOptimizationGoal_in,
      const sensible::layer coating , const size_t iter,
      const double lmin, const double lmax ) noexcept;

  methods& operator=( const methods& that ) noexcept;

  //output methods
  double bestFit(
      const std::shared_ptr< math::estimation::unknownList > &list_in,
      const std::shared_ptr< ThermalData > &thermalData_in,
      const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) noexcept;

  PIE::PIEAnalysisOutput
  parameterIntervalEstimates(
      const std::shared_ptr< math::estimation::unknownList > &list_in,
      const std::shared_ptr< ThermalData > &thermalData_in,
      const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) noexcept;

  ThermalSweepOptimizer::OptimizerOutput
  optimization(
      const std::shared_ptr< math::estimation::unknownList > &list_in,
      const std::shared_ptr< ThermalData > &thermalData_in,
      const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in
      ) noexcept;
  
  void GUM_uncertainty(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in  ) noexcept;

  std::string contourMapping() noexcept;
};

methods
loadMethodsfromFile(const boost::property_tree::ptree &ptchild4,
                     const math::estimation::unknownList &parameterEstimation,
                     const ThermalData &thermData,
                     const sensible::layer &coating ) noexcept;


}}
#endif // METHODS_HPP
