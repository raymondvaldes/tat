//
//  if_intersect.h
//  tat
//
//  Created by Raymond Valdes on 4/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_math_geometry_intersect_two_circles_if_intersect__
#define __tat_math_geometry_intersect_two_circles_if_intersect__

#include "units.h"
#include <utility>

namespace math{
namespace geometry{
namespace intersect{
namespace two_circles{

auto if_intersect
(
  units::quantity< units::si::length > r,
  units::quantity< units::si::length > offset,
  units::quantity< units::si::length > radius
) -> bool;

} // namespace two_circles
} // namespace intersect
} // namespace geometry
} // namespace math

#endif /* defined() */
