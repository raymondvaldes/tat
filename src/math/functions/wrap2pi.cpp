//
//  wrap2pi.cpp
//  tat
//
//  Created by Raymond Valdes on 1/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "math/functions/wrap2pi.h"
#include "units/si/constants/thermal.h"
#include <cmath>

namespace math {

namespace functions {

units::quantity< units::si::plane_angle >
wrap2pi( const units::quantity< units::si::plane_angle > &phase ) noexcept
{
  using units::fmod;
  auto phaseWrapped = phase;
  
  using units::si::constants::PI_radians;

  if ( phase.value() > 0 )
    phaseWrapped = fmod( phase + PI_radians, 2.0 * PI_radians ) - PI_radians;
  else
    phaseWrapped = fmod( phase - PI_radians, 2.0 * PI_radians ) + PI_radians;

  return phaseWrapped;
}
  
  
} // namespace functions
  
} // namespace math
