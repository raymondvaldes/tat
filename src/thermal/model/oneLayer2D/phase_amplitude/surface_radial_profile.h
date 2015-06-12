//
//  surface_radial_profile.h
//  tat
//
//  Created by Raymond Valdes on 5/1/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2D_phase_amplitude_surface_radial_profile__
#define __tat_thermal_model_oneLayer2D_phase_amplitude_surface_radial_profile__

#include <vector>

#include "units.h"
#include "math/complex/properties.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{
namespace temperature{

auto surface_radial_profile(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::temperature > const deltaT,
  std::vector< units::quantity< units::si::dimensionless > > const & radial_positions,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha,
  units::quantity< units::si::frequency > const f
) noexcept -> std::vector< math::complex::properties< units::si::temperature >>;

} // namespace temperature
} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__surface_radial_profile__) */
