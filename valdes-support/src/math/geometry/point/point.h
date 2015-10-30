//
//  point.h
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_math_geometry_point__
#define __tat_math_geometry_point__

#include "units.h"

namespace math{
namespace geometry{

struct Point{

  units::quantity< units::si::length > x;
  units::quantity< units::si::length > y;
  
  explicit Point
  (
    units::quantity< units::si::length > const x_,
    units::quantity< units::si::length > const y_
  ) noexcept;
  
};

} // namespace geometry
} // namespace math

#endif /* defined(__tat__point__) */
