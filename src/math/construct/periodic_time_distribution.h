//
//  periodic_time_distribution.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__periodic_time_distribution__
#define __tat__periodic_time_distribution__

#include <vector>
#include <cstddef>
#include "units.h"

namespace math {

namespace construct {

auto
periodic_time_distribution
(
  units::quantity< units::si::frequency > const & frequency,
  size_t const cycles,
  size_t const count
)
noexcept -> std::vector< units::quantity< units::si::time > >;
  
} // namespace construct
  
} // namespace math

#endif /* defined(__tat__periodic_time_distribution__) */
