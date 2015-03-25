//
//  surface_phase.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/two_layer/complex/surface_phase.h"

#include <cmath>
#include "thermal/model/two_layer/complex/surface_temperature.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace complex {

using namespace units;

auto surface_phase
(
  units::quantity< units::si::frequency > const f,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha_1,
  units::quantity< units::si::thermal_diffusivity > const alpha_2,
  units::quantity< units::si::thermal_conductivity > const k_1,
  units::quantity< units::si::thermal_conductivity > const k_2
)
noexcept -> units::quantity< units::si::plane_angle >
{
  auto const temp =
  complex::surface_temperature( f, L, alpha_1, alpha_2, k_1, k_2 );
  
  auto const phase = -arg( temp ) - M_PI_2 * radians ;
  return phase;
}

} // namespace complex
} // namespace twoLayer
} // namespace model
} // namespace thermal
