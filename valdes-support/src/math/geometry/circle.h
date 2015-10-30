//
//  circle.h
//  tat
//
//  Created by Raymond Valdes on 4/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_circle_h
#define tat_circle_h

#include <cmath>
#include "units.h"

namespace math{
namespace geometry{
namespace area{

auto circle_from_radius( units::quantity< units::si::length > const radius )
noexcept -> units::quantity< units::si::area > ;

auto circle_from_diameter( units::quantity< units::si::length > const diameter )
noexcept -> units::quantity< units::si::area > ;

template< typename type >
auto circle_from_radius( type const radius ) noexcept
{
  auto const area = M_PI * pow( radius, 2 );
  return area;
}

template< typename type >
auto circle_from_diameter( type const diameter ) noexcept
{
  auto const radius = diameter / 2 ;
  auto const area = circle_from_radius( radius );
  return area;
}

} // namespace area
} // namespace geometry
} // namespace math

#endif
