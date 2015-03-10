//
//  conductivity.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/10/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/define/conductivity.h"

namespace thermal{

namespace define {

auto conductivity
(
  units::quantity< units::si::volumetric_heat_capacity > const & rhoCp,
  units::quantity< units::si::thermal_diffusivity> const & alpha
)
noexcept -> units::quantity< units::si::thermal_conductivity >
{
  // alpha = k / rhoCp

  auto const k = alpha * rhoCp ;
  return k;
}
  
} // namespace define
  
} // namespace
