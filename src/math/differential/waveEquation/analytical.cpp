//
//  analytical.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "math/differential/waveEquation/analytical.h"

namespace math {

namespace differential {

namespace waveEquation {

auto analytical_solution_00( double const x, std::complex<double> const Kappa )
noexcept -> std::complex<double>
{
  // eq:  s''(x) + (K^2) s(x) == 0
  // BC:  s(0) == 0
  // BC:  s(1) == 1

  using std::sin;
  auto const s_x = sin( Kappa * x ) / sin( Kappa ) ;
  return s_x;
}
  
auto analytical_solution_10(
  double const x,
  std::complex<double> const Kappa,
  double const A,
  double const L_b )
noexcept -> std::complex<double>
{
  // eq:  s''(x) + (K^2) s(x) == 0
  // BC:  s'(0) == A
  // BC:  s(L_b)  == 0

  using std::cosh;
  using std::sinh;
  
  auto const kx = Kappa * x;
  auto const kL = Kappa * L_b;
  
  auto const s_x = ( A / Kappa ) * ( sinh( kx ) - tanh( kL ) * cosh( kx ) ) ;
  
  return s_x;
}
  
} // namespace waveEquation
  
} // namespace differential

} // namespace math
