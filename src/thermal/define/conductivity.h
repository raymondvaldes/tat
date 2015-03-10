//
//  conductivity.h
//  tat
//
//  Created by Raymond Valdes_New on 3/10/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__conductivity__
#define __tat__conductivity__

#include "units.h"

namespace thermal{

namespace define {

auto conductivity
(
  units::quantity< units::si::volumetric_heat_capacity > const & rhoCp,
  units::quantity< units::si::thermal_diffusivity> const & alpha
)
noexcept -> units::quantity< units::si::thermal_conductivity >;

} // namespace define
  
} // namespace
#endif /* defined(__tat__conductivity__) */
