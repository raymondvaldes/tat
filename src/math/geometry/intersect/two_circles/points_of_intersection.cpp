//
//  points_of_intersection.cpp
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "points_of_intersection.h"
#include "math/geometry/intersect/two_circles/if_intersect.h"
#include <cassert>

namespace math{
namespace geometry{
namespace intersect{
namespace two_circles{

using namespace units;
using std::pair;
using std::make_pair;
using std::abs;
using std::isfinite;

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
) noexcept -> std::pair< Point, Point >
{
  assert( r > 0 * meter );
  assert( offset > 0 * meter );
  assert( radius > 0 * meter );

  auto const a = offset;
  auto const b = radius;

  assert( if_intersect( r, a, b ) );
  
  auto const x_1 = ( pow<2>(a) - pow<2>(b) + pow<2>(r) ) / ( 2._nd * a ) ;
  auto const y_1 =
  - ( sqrt( - ( a - b - r ) * ( a + b - r ) * ( a - b + r ) * ( a + b + r ) ) )
  / ( 2._nd * a ) ;
  
  assert( isfinite(x_1) );
  assert( isfinite(y_1) );
 
  auto const x_2 = x_1;
  auto const y_2 = - y_1 ;

  auto const point_1 = Point( x_1, y_1 );
  auto const point_2 = Point( x_2, y_2 );
  
  
  return make_pair( point_1, point_2 );
}

} // namespace two_circles
} // namespace intersect
} // namespace geometry
} // namespace math
