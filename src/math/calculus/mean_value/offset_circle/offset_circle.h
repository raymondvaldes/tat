//
//  offset_circle.h
//  tat
//
//  Created by Raymond Valdes on 4/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_math_calculus_offset_circle_h
#define tat_math_calculus_offset_circle_h

#include "units.h"
#include <functional>

namespace math{
namespace calculus{
namespace mean_value{

auto offset_circle
(
  std::function< double( units::quantity< units::si::length > )> const & f,
  units::quantity< units::si::length > const offset,
  units::quantity< units::si::length > const radius
)
noexcept -> double;

  // find the mean value of a function from a to b.
  // mean_value =
  // 1/(A) * Int[ Int[ ( f * r ), dphi, phi_1, phi_2 ] , dr, r1, r2 ]

  // A = pi * b^2

} // namespace mean_value
} // namespace calculus
} // namespace math

#endif
