//
//  transient_surface_amplitudes.h
//  tat
//
//  Created by Raymond Valdes_New on 3/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__transient_surface_amplitudes__
#define __tat__transient_surface_amplitudes__

#include <vector>

#include "units.h"

namespace investigations {

namespace twoColorPyrometery {

namespace plot {

auto transient_surface_amplitudes(
  std::vector< units::quantity< units::si::frequency > > const & x,
  std::vector< units::quantity< units::si::temperature > > const & y
) noexcept -> void;
  
} // namespace plot

} // namespace twoColorPyrometery
  
} // namespace investigations

#endif /* defined(__tat__transient_surface_amplitudes__) */
