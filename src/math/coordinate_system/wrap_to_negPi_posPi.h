//
//  wrap_to_negPi_posPi.h
//  tat
//
//  Created by Raymond Valdes_New on 3/17/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_wrap_to_negPi_posPi_h
#define tat_wrap_to_negPi_posPi_h

#include <cmath>

#include "math/coordinate_system/wrap_to_0_2Pi.h"
#include "units.h"

namespace math {

namespace coordinate_system {

inline
auto wrap_to_negPi_posPi( units::quantity< units::si::plane_angle > const angle )
{
  using units::quantity;
  using units::si::plane_angle;
  using units::si::radians;
  using units::fmod;
  
  auto const Pi = quantity<plane_angle>( M_PI * radians );
  auto const twoPi = quantity<plane_angle>( 2 * M_PI * radians );

  auto const myAngle = wrap_to_0_2Pi( angle );
  
  auto x = fmod( myAngle + Pi, twoPi );
  if( x.value() < 0 ) {
    x += twoPi;
  }
  
  auto const wrapped_value = x - Pi;
  
  assert( wrapped_value.value() <= M_PI );
  assert( wrapped_value.value() >= -M_PI );
  
  return wrapped_value ;
}
  
} // namespace coordinate_system
  
} // namespace math

#endif
