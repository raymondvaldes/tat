//
//  diffusivity_from_phases.h
//  tat
//
//  Created by Raymond Valdes on 4/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_analysis_oneLayer2D_offset_detector_estimate_parameters_diffusivity_from_phases__
#define __tat_thermal_analysis_oneLayer2D_offset_detector_estimate_parameters_diffusivity_from_phases__

#include "units.h"
#include "thermal/model/slab/slab.h"

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace offset_detector{
namespace estimate_parameters{

struct Best_fit{
  // system properties
  units::quantity< units::si::length > view_radius;
  units::quantity< units::si::length > beam_radius;
  
  // modeled elements (reconstructed from non-dimensional parameters)
  thermal::model::slab::Slab bulk_slab;
  
  // modulation frequency/thermal penetration
  std::vector< units::quantity< units::si::frequency > > frequencies;
  std::vector< units::quantity< units::si::dimensionless > > ls;

  // model predictions
  std::vector< units::quantity< units::si::plane_angle > > model_phases;

  explicit Best_fit
  (
    thermal::model::slab::Slab const slab_,
    units::quantity< units::si::dimensionless > const view_radius_nd,
    units::quantity< units::si::dimensionless> const b,
    std::vector< units::quantity<units::si::frequency> > const frequencies_,
    std::vector< units::quantity< units::si::plane_angle > > const model_phases_
  ) noexcept ;

};

auto diffusivity_from_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const slab_initial,
  units::quantity< units::si::length> const beam_radius,
  units::quantity< units::si::length > const detector_view_radius,
  units::quantity< units::si::length > const detector_offset_i 
) noexcept -> Best_fit;

} // namespace estimate_parameters
} // namespace offset_detector
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal

#endif /* defined(__tat__diffusivity_from_phases__) */
