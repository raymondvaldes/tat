//
//  length.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include "thermal/model/dimensionless/length.h"
#include "thermal/model/two_Layer/dimensionless/length.h"

namespace thermal {
namespace model {
namespace twoLayer {
namespace dimensionless {

auto length
(
  units::quantity< units::si::length > const x,
  units::quantity< units::si::length > const L
)
noexcept -> units::quantity< units::si::dimensionless >
{
  return model::dimensionless::length( x, L ) ;
}

} // namespace dimensionless
} // namespace twoLayer
} // namespace model
} // namespace thermal
