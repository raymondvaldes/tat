//
//  analytical.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__analytical__
#define __tat__analytical__

#include <cmath>
#include "math/functions/trigonometric/csc.h"
#include "math/functions/trigonometric/sec.h"

#include "units.h"

namespace math {

namespace differential {

namespace waveEquation {

template< typename T, typename Y >
auto analytical_solution_00( T const x, Y const Kappa )
noexcept -> Y
{
  //
  // eq:  s''(x) + (K^2) s(x) == 0
  // BC:  s'(0) == -1
  // BC:  s'(1) == 0

  using std::cos;
  using math::functions::trigonometric::csc;
  using std::sqrt;

  using units::cos;
  using units::csc;
  using units::sqrt;
  
  auto const sqrt_k = sqrt( Kappa );
  auto const s_x = -( cos( sqrt_k * ( x - 1 ) ) * csc( sqrt_k ) ) / sqrt_k;

  return s_x;
}
  
template< typename T, typename Y >
auto analytical_solution_10(
  T const x,
  Y const Kappa
)
  
noexcept -> Y
{
  // eq:  s''(x) + (K^2) s(x) == 0
  // BC:  s'(0) == -1
  // BC:  s(1)  == 0

  using std::sin;
  using math::functions::trigonometric::sec;
  using std::sqrt;
  
  using units::sin;
  using units::sec;
  using units::sqrt;
  
  auto const sqrt_k = sqrt( Kappa );
  auto const s_x = (-sec( sqrt_k ) * sin( sqrt_k * ( x - 1 ) ) ) / sqrt_k ;
  
  return s_x;
}
  
} // namespace waveEquation
  
} // namespace differential

} // namespace math

#endif /* defined(__tat__analytical__) */
