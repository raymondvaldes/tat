//
//  circle.cpp
//  tat
//
//  Created by Raymond Valdes on 4/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>
#include "circle.h"

namespace math{
namespace geometry{
namespace area{

using namespace units;

auto circle_from_radius( units::quantity< units::si::length > const radius )
noexcept -> units::quantity< units::si::area >
{
  auto const pi = quantity< dimensionless >( M_PI );
  auto const area = pi * pow<2>( radius );
  
  return area;
}

auto circle_from_diameter( units::quantity< units::si::length > const diameter )
noexcept -> units::quantity< units::si::area >
{
  auto const radius = diameter / 2._nd ;
  auto const area = circle_from_radius( radius );

  return area;
}

} // namespace area
} // namespace geometry
} // namespace math
