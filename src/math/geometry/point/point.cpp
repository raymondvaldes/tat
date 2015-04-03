//
//  point.cpp
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "point.h"

namespace math{
namespace geometry{

Point::Point
(
  units::quantity< units::si::length > const x_,
  units::quantity< units::si::length > const y_
) noexcept : x( x_ ), y( y_ ) {}

} // namespace geometry
} // namespace math
