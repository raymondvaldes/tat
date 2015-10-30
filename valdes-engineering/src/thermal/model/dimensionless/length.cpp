//
//  length.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/dimensionless/length.h"

namespace thermal {

namespace model {

namespace dimensionless {

auto length
(
  units::quantity< units::si::length > const x,
  units::quantity< units::si::length > const reference
)
noexcept -> units::quantity< units::si::dimensionless >
{
  return x / reference;
}

} // namespace dimensionless
  
} // namespace model

} // namespace thermal
