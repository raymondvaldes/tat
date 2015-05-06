//
//  weighted_avg_surface_phases_amplitudes.h
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2d_average_weighted_avg_surface_phases_amplitudes__
#define __tat_thermal_model_oneLayer2d_average_weighted_avg_surface_phases_amplitudes__

#include <complex>
#include <vector>

#include "units.h"
#include "math/complex/properties.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace average{

auto
weighted_avg_surface_phases_amplitudes
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  std::vector< units::quantity< units::si::frequency> > const & frequencies,
  units::quantity< units::si::length> const L,
  units::quantity< units::si::thermal_diffusivity> const alpha,
  units::quantity< units::si::temperature > const steady_state_temperature,
  units::quantity< units::wavelength > const detector_wavelength
) noexcept -> std::vector< math::complex::properties< units::si::temperature >>;

} // namespace average
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__weighted_avg_surface_phases_amplitudes__) */
