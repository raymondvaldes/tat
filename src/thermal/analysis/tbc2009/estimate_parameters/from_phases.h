//
//  estimate_properties.h
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_analysis_tbc2009_estimate_properties__
#define __tat_thermal_analysis_tbc2009_estimate_properties__

#include <vector>
#include "thermal/model/slab/slab.h"
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"
#include "units.h"

namespace thermal {
namespace analysis {
namespace tbc2009 {
namespace estimate_parameters{

struct Best_fit{
  // nondimentional system properties
  units::quantity< units::si::length > view_radius;
  dimensionless::HeatingProperties hp;
  dimensionless::ThermalProperties tp;
  
  // modeled elements (reconstructed from non-dimensional parameters)
  thermal::model::slab::Slab coating_slab;  
  
  // modulation frequency/thermal penetration
  std::vector< units::quantity< units::si::frequency > > frequencies;
  std::vector< units::quantity< units::si::dimensionless > > ls;

  // model predictions
  std::vector< units::quantity< units::si::plane_angle > > model_phases;

  explicit Best_fit
  (
    units::quantity< units::si::length > const L_coat_,
    units::quantity< units::si::dimensionless > const view_radius_,
    thermal::model::slab::Slab const substrate_slab_,
    dimensionless::HeatingProperties const hp_,
    dimensionless::ThermalProperties const tp_,
    std::vector< units::quantity<units::si::frequency> > const  frequencies_,
    std::vector< units::quantity< units::si::plane_angle > > const model_phases_
  ) noexcept ;

};

auto estimate_parameters_from_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const & slab_initial,
  thermal::model::slab::Slab const & slab_substrate
) noexcept -> fitting_result;



////
//
//average_surface_phases_amplitudes
//(
//  units::quantity< units::si::dimensionless > const view_radius,
//  std::vector< units::quantity< units::si::frequency > > const frequencies,
//  units::quantity< units::si::dimensionless > const Lambda,
//  units::quantity< units::si::dimensionless > const R0,
//  units::quantity< units::si::dimensionless > const R1,
//  units::quantity< units::si::dimensionless > const b,
//  dimensionless::ThermalProperties const tp,
//  units::quantity< units::si::length > const L,
//  units::quantity< units::si::thermal_diffusivity > const alpha_substrate
//)



} // namespace estimate_parameters
} // namespace tbc2009
} // namespace analysis
} // namespace thermal

#endif /* defined(__tat__estimate_properties__) */
