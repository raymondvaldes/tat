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
  model::tbc2009::dimensionless::HeatingProperties hp;
  model::tbc2009::dimensionless::ThermalProperties tp;
  
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
    model::tbc2009::dimensionless::HeatingProperties const & hp_,
    model::tbc2009::dimensionless::ThermalProperties const & tp_,
    std::vector< units::quantity<units::si::frequency> > const frequencies_,
    std::vector< units::quantity< units::si::plane_angle > > const model_phases_
  ) noexcept ;

};

auto from_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const slab_initial,
  thermal::model::slab::Slab const slab_substrate,

  model::tbc2009::dimensionless::HeatingProperties const & hp_initial,
  units::quantity< units::si::length > const detector_view_radius
) noexcept -> Best_fit;


auto from_phases
(
  std::pair<
  std::vector< units::quantity< units::si::frequency > > ,
  std::vector< units::quantity< units::si::plane_angle > > > const & o,
  thermal::model::slab::Slab const & slab_initial,
  thermal::model::slab::Slab const & slab_substrate,

  model::tbc2009::dimensionless::HeatingProperties const & hp_initial,
  units::quantity< units::si::length > const & detector_view_radius
) noexcept -> Best_fit;

} // namespace estimate_parameters
} // namespace tbc2009
} // namespace analysis
} // namespace thermal

#endif /* defined(__tat__estimate_properties__) */
