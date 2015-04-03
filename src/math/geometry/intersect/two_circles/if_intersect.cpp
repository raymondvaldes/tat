//
//  if_intersect.cpp
//  tat
//
//  Created by Raymond Valdes on 4/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "if_intersect.h"

#include <cmath>
#include <cassert>

namespace math{
namespace geometry{
namespace intersect{
namespace two_circles{

using namespace units;

auto if_intersect
(
  units::quantity< units::si::length > r,
  units::quantity< units::si::length > offset,
  units::quantity< units::si::length > radius
) -> bool
{
  auto const a = offset;
  auto const b = radius;

  assert( r > 0 * meter );
  assert( a > 0 * meter );
  assert( b > 0 * meter );

  return ( ( r <= a + b )  && ( r >= a - b ) );
}

} // namespace two_circles
} // namespace intersect
} // namespace geometry
} // namespace math
