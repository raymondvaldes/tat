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

using namespace units;

auto volumetricHeatCapacity
(
  units::quantity< units::si::thermal_diffusivity > const alpha,
  units::quantity< units::si::thermal_conductivity> const k
)
noexcept -> units::quantity< units::si::volumetric_heat_capacity >
{
  // alpha = k / rhoCp

  auto const rhoCp = k / alpha ;
  return rhoCp;
}

auto volumetricHeatCapacity
(
  units::quantity< units::si::thermal_effusivity > const e,
  units::quantity< units::si::thermal_conductivity> const k
)
noexcept -> units::quantity< units::si::volumetric_heat_capacity >
{
  // e = sqrt( k * rhoCp )
  
  auto const rhoCp = pow<2>( e ) / k;
  return rhoCp;
}

  
} // namespace define
} // namespace
