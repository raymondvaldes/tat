//
//  b.cpp
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "b.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

auto b
(
  units::quantity< units::si::length > const beam_radius,
  units::quantity< units::si::length > const L
) noexcept -> units::quantity< units::si::dimensionless >
{
  return beam_radius / L;
}

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal

