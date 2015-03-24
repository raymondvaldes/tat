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
  // BC:  s'(1) == 0 (adiabatic)

  using std::cos;
  using math::functions::trigonometric::csc;
  using std::sqrt;

  using units::cos;
  using units::csc;
  
  auto const s_x = - cos( Kappa - Kappa * x  )  * csc( Kappa )  / Kappa;

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
  // BC:  s(1)  == 0 ( constant surface temperature )

  using std::sin;
  using math::functions::trigonometric::sec;
  using std::sqrt;
  
  using units::sin;
  using units::sec;
  using units::sqrt;
  
  auto const s_x = sec( Kappa ) * sin( Kappa  - Kappa * x ) / Kappa ;
  return s_x;
}
  
template< typename T, typename Y >
auto analytical_solution_11(
  T const x,
  Y const Kappa,
  T const T0,
  T const phi
)
noexcept -> Y
{
  // eq:  s''(x) + (K^2) s(x) == 0
  // BC:  s'(0) == -1
  // BC:  s(1)  == T0 * Exp[-phi] ( unknown surface temperature )

  using std::sin;
  using math::functions::trigonometric::sec;
  using std::sqrt;
  using std::exp;
  
  using units::exp;
  using units::sin;
  using units::sec;
  using units::sqrt;
  
  auto const Kappa_x = Kappa * x;
  
  auto
  s_x = exp( -phi ) * T0 * cos( Kappa_x ) + ( sin( Kappa  - Kappa_x ) / Kappa ) ;
  s_x *= sec( Kappa );

  
  return s_x;
}
  
} // namespace waveEquation
  
} // namespace differential

} // namespace math

#endif /* defined(__tat__analytical__) */
