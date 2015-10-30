//
//  angles_of_intersection.cpp
//  tat
//
//  Created by Raymond Valdes on 4/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <iostream>
#include "math/geometry/intersect/two_circles/angles_of_intersection.h"
#include "math/geometry/intersect/two_circles/if_intersect.h"
#include "math/geometry/intersect/two_circles/points_of_intersection.h"
#include <cassert>

namespace math{
namespace geometry{
namespace intersect{
namespace two_circles{

using namespace units;
using std::pair;
using std::make_pair;
using std::abs;



auto angles_of_intersection
(
  units::quantity< units::si::length > r,
  units::quantity< units::si::length > offset,
  units::quantity< units::si::length > radius
)  -> std::pair< units::quantity< units::si::plane_angle>,
                units::quantity< units::si::plane_angle> >
{
  assert( r >= 0 * meter );
  assert( offset > 0 * meter );
  assert( radius > 0 * meter );

  auto const a = offset;
  auto const b = radius;

  assert( if_intersect(r, a, b ) );
  auto angles = pair< quantity< plane_angle >, quantity< plane_angle > >();
  
  auto const is_inside_circle = r <= ( b - a);
  
  if( !is_inside_circle )
  {
    auto const ratio =
    sqrt( ( b + a - r ) * ( b - a + r ) * ( -b + a + r ) * ( b + a + r )  )
    /  (  -pow<2>(b) + pow<2>(a) +  pow<2>(r) );
    
    auto const phi = abs( atan( ratio ) );
    angles = make_pair( -phi, phi );
  
    auto const intersection_points = points_of_intersection(r, offset, radius );
    auto const x_is_neg = intersection_points.first.x < 0 * meters ;
    
    if( x_is_neg )
    {
      // this correction is necessary to get the right bounds on the angle
      angles = make_pair(
        - M_PI * radians - angles.first ,
          M_PI * radians - angles.second
      );
      
    }
  }
  else if( is_inside_circle )
  {
    angles = make_pair( -M_PI * radians, M_PI * radians );
  }
  
  assert( angles.first <= 0 * radians );
  assert( angles.second >= 0 * radians );
  
  return angles;
}

} // namespace two_circles
} // namespace intersect
} // namespace geometry
} // namespace math
