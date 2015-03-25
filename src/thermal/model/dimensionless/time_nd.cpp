//
//  time.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/dimensionless/time_nd.h"

namespace thermal {

namespace model {

namespace dimensionless {

auto time
(
  units::quantity< units::si::time > const t,
  units::quantity< units::si::time > const reference
)
noexcept -> units::quantity< units::si::dimensionless >
{
  return t / reference;
}
  
} // namespace dimensionless
  
} // namespace model

} // namespace thermal
