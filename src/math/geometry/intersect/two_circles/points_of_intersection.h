//
//  points_of_intersection.h
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_math_geometry_intersect_two_circles_points_of_intersection__
#define __tat_math_geometry_intersect_two_circles_points_of_intersection__

#include "units.h"
#include <utility>
#include "math/geometry/point/point.h"

namespace math{
namespace geometry{
namespace intersect{
namespace two_circles{

/*
Given a circle at an origin: (x^2 + y^2 == r^2)
and  a circle that is  offset in the positive (x) direction:
( ( x - a )^2 + y^2 == b^2 )

What are the points of intersection with respect to the origin?

What are the angle of intersection with respect to the origin?
*/

auto points_of_intersection
(
  units::quantity< units::si::length > r,
  units::quantity< units::si::length > offset,
  units::quantity< units::si::length > radius
) noexcept -> std::pair< Point, Point > ;

} // namespace two_circles
} // namespace intersect
} // namespace geometry
} // namespace math

#endif /* defined(__tat__points_of_intersection__) */
