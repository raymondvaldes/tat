//
//  average_surface_phases_amplitudes.h
//  tat
//
//  Created by Raymond Valdes on 4/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2D_offset_detector_average_surface_phases_amplitudes__
#define __tat_thermal_model_oneLayer2D_offset_detector_average_surface_phases_amplitudes__


#include <complex>
#include <vector>

#include "units.h"
#include "math/complex/properties.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace offset_detector{

auto average_surface_phases_amplitudes
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  std::vector< units::quantity< units::si::frequency> > const & frequencies,
  units::quantity< units::si::length> const L,
  units::quantity< units::si::thermal_diffusivity> const alpha,
  units::quantity< units::si::dimensionless> const detector_offset
) noexcept -> std::vector< math::complex::properties< units::si::temperature >>;

} // namespace offset_detector
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__average_surface_phases_amplitudes__) */
