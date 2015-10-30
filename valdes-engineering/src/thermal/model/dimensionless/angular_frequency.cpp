//
//  angular_frequency.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "angular_frequency.h"

namespace thermal {

namespace model {

namespace dimensionless {

auto angular_frequency
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::angular_frequency > const reference
) -> units::quantity< units::si::dimensionless >
{
  return w / reference;
}
  
} // namespace dimensionless
  
} // namespace model

} // namespace thermal
