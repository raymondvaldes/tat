//
//  temperature.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__temperature__
#define __tat__temperature__

#include "units.h"

namespace thermal {

namespace model {

namespace dimensionless {

auto temperature
(
  units::quantity< units::si::temperature > const T,
  units::quantity< units::si::temperature > const offset,
  units::quantity< units::si::temperature > const reference
)
noexcept -> units::quantity< units::si::dimensionless >;
  
} // namespace dimensionless
  
} // namespace model

} // namespace thermal
#endif /* defined(__tat__temperature__) */
