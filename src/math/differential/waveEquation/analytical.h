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
#include "units.h"

namespace math {

namespace differential {

namespace waveEquation {

template< typename T, typename Y >
auto analytical_solution_00( T const x, Y const Kappa )
noexcept -> Y
{
  // eq:  s''(x) + (K^2) s(x) == 0
  // BC:  s(0) == 0
  // BC:  s(1) == 1

  using std::sin;
  auto const s_x = sin( Kappa * x ) / sin( Kappa ) ;
  return s_x;
}
  
template< typename T, typename Y >
auto analytical_solution_10(
  T const x,
  Y const Kappa,
  T const A,
  T const L_b )
noexcept -> Y
{
  // eq:  s''(x) + (K^2) s(x) == 0
  // BC:  s'(0) == A
  // BC:  s(L_b)  == 0

  using std::cosh;
  using std::sinh;
  using std::tanh;
  using units::sinh;
  using units::tanh;
  using units::cosh;
  
  auto const kx = Kappa * x;
  auto const kL = Kappa * L_b;


  auto const s_x = ( A / Kappa ) * ( sinh( kx ) - tanh( kL ) * cosh( kx ) ) ;
  
  return s_x;
}
  
} // namespace waveEquation
  
} // namespace differential

} // namespace math

#endif /* defined(__tat__analytical__) */
