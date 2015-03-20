//
//  steady_surface_temperature.h
//  tat
//
//  Created by Raymond Valdes_New on 3/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__steady_surface_temperature__
#define __tat__steady_surface_temperature__

#include <vector>

#include "units.h"

namespace investigations {

namespace twoColorPyrometery {

namespace plot {

auto steady_surface_temperature(
  std::vector< units::quantity< units::si::frequency > > const & x,
  std::vector< units::quantity< units::si::temperature > > const & y
) noexcept -> void;
  
} // namespace plot

} // namespace twoColorPyrometery
  
} // namespace investigations

#endif /* defined(__tat__steady_surface_temperature__) */
