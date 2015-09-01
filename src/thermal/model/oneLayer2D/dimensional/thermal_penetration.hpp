//
//  thermal_penetration.hpp
//  tat
//
//  Created by Raymond Valdes on 8/29/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef thermal_penetration_cpp_23432
#define thermal_penetration_cpp_23432


#include "units.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace dimensional{

auto thermal_penetration
(
  units::quantity< units::si::frequency > const f,
  units::quantity< units::si::thermal_diffusivity> const alpha
) noexcept -> units::quantity< units::si::length >;

} // namespace dimensionless
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* thermal_penetration_cpp */
