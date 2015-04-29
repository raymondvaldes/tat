//
//  b.cpp
//  tat
//
//  Created by Raymond Valdes on 4/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/dimensionless/b.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
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
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
