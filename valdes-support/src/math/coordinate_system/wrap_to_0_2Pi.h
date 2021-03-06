//
//  wrap_to_0_2Pi.h
//  tat
//
//  Created by Raymond Valdes_New on 3/17/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_wrap_to_math_coordinateSystem_0_2Pi_h
#define tat_wrap_to_math_coordinateSystem_0_2Pi_h

#include <iostream>
#include <cmath>
#include "units.h"

namespace math {
namespace coordinate_system {

inline
auto wrap_to_0_2Pi( units::quantity< units::si::plane_angle > const angle )
{
  using std::isfinite;
  assert( isfinite( angle.value() )  ) ;
  using namespace units;
  
  auto static const twoPi = quantity<plane_angle>( 2 * M_PI * radians );
  
  auto x = fmod( angle, twoPi );
  if( x.value() < 0 ) {
    x += twoPi;
  }

  assert( x.value() <= 2 * M_PI );
  assert( x.value() >= 0 );
  
  return x ;
}
  
} // namespace coordinate_system
} // namespace math

#endif
