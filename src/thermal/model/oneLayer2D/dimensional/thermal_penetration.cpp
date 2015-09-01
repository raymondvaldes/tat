//
//  thermal_penetration.cpp
//  tat
//
//  Created by Raymond Valdes on 8/29/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "thermal_penetration.hpp"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace dimensional{

using namespace units;

auto thermal_penetration
(
  units::quantity< units::si::frequency > const f,
  units::quantity< units::si::thermal_diffusivity> const alpha
) noexcept -> units::quantity< units::si::length >
{
  return 9999 * meters;

}

} // namespace dimensionless
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
