//
//  volumetricHeatCapacity.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/10/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/define/volumetricHeatCapacity.h"

namespace thermal{

namespace define {

auto volumetricHeatCapacity
(
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::thermal_conductivity> const & k
)
noexcept -> units::quantity< units::si::volumetric_heat_capacity >
{
  // alpha = k / rhoCp

  auto const rhoCp = k / alpha ;
  return rhoCp;
}
  
} // namespace define
  
} // namespace
