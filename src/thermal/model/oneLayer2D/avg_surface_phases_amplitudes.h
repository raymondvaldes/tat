//
//  avg_surface_phases_amplitudes.h
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2D_avg_surface_phases_amplitudes__
#define __tat_thermal_model_oneLayer2D_avg_surface_phases_amplitudes__

#include <complex>
#include <vector>

#include "units.h"
#include "math/complex/properties.h"

namespace thermal {
namespace model {
namespace oneLayer2D {

auto
avg_surface_phases_amplitudes
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::temperature > const deltaT,
  units::quantity< units::si::dimensionless> const view_radius,
  std::vector< units::quantity< units::si::frequency> > const & frequencies,
  units::quantity< units::si::length> const L,
  units::quantity< units::si::thermal_diffusivity> const alpha
) noexcept -> std::vector< math::complex::properties< units::si::temperature >>;


} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__avg_surface_phases_amplitudes__) */
