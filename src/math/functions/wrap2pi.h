//
//  wrap2pi.h
//  tat
//
//  Created by Raymond Valdes on 1/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__wrap2pi__
#define __tat__wrap2pi__

#include "units.h"

namespace math {

namespace functions {

units::quantity< units::si::plane_angle >
wrap2pi( const units::quantity< units::si::plane_angle > &input ) noexcept;

  
} // namespace functions
  
} // namespace math

#endif /* defined(__tat__wrap2pi__) */
