//
//  adjust_phase.h
//  tat
//
//  Created by Raymond Valdes on 9/2/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef adjust_phase_h
#define adjust_phase_h

#include <cassert>
#include <cmath>

#include "algorithm/algorithm.h"
#include "math/complex/properties.h"
#include "units.h"

namespace math{
namespace complex{

template< typename T>
auto adjust_phase
(
  properties<T> const & complex_quantity,
  units::quantity< units::si::plane_angle> const phase_offset
)
{
  using std::isfinite;
  assert( isfinite( phase_offset.value() ) );
  
  auto const phase = complex_quantity.phase;
  auto const amplitude = complex_quantity.amplitude;
  
  auto const phase_adjusted = phase - phase_offset;
  auto const adjusted_complex_value = properties<T>( phase_adjusted,amplitude );

  return adjusted_complex_value;
}

} // namespace complex
} // namespace math

#endif /* adjust_phase_h */
