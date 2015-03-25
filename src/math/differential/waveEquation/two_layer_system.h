//
//  two_layer_system.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_two_layer_system_h
#define tat_two_layer_system_h

#include <cmath>
#include "math/functions/trigonometric/csc.h"
#include "math/functions/trigonometric/sec.h"

#include "units.h"

namespace math {

namespace differential {

namespace waveEquation {

template< typename T, typename Y >
auto surface_solution
(
  Y const k,
  T const a,
  T const b
) noexcept -> Y
{
  using std::sinh;
  using std::cosh;
  using units::sinh;
  using units::cosh;
  
  auto const kx = k * x;
  
  auto
  s  = a * cosh( k - kx ) + b * sinh( k - kx ) ;
  s /= b * k * cosh( k ) + a * k * sinh( k );
  
  return s;
}
  
template< typename T, typename Y >
auto first_layer_solution
(
  Y const k,
  T const a,
  T const b
) noexcept -> Y
{
  using std::sinh;
  using std::cosh;
  using units::sinh;
  using units::cosh;
  
  auto
  s  = a * cosh( k ) + b * sinh( k ) ;
  s /= b * k * cosh( k ) + a * k * sinh( k );
  
  return s;
}

template< typename T, typename Y >
auto second_layer_solution
(
  T const x,
  Y const Kappa,
  T const a,
  T const b
) noexcept -> Y
{
  using std::sinh;
  using std::cosh;
  using std::exp;
  
  using units::sinh;
  using units::cosh;
  using units::exp;
  
  auto const kx = k * x;
  
  auto
  s  = a * exp( ( k - kx ) / a ) ;
  s /= k * ( b * cosh( k ) + a * sinh( k ) ) ;
  
  return s;
}
  
template< typename T, typename Y >
auto two_layer_system
(
  T const x,
  Y const k,
  T const a,
  T const b
) noexcept -> Y
  // transient heat condution with periodic formulation (complex combination)
  // eq:     s1''(x) - (k^2) s1(x) == 0
  // eq: a * s2''(x) - (k^2) s2(x) == 0

  // BC:  s1'(0) == -1              //ex. periodic heat flux cos(wt)
  // BC:  s1( 1 ) = s2 ( 1 )        //ex. temperature continuity
  // BC:  s2'( 1 ) == b * s2'( 1 )  //ex. heat flux continuity
  // BC:  s2( Inf )  == 0           //ex. temperature goes to 0
{
  auto s_x = T();

  if( x == 0){
    s_x = surface_solution( k, a, b ) ;
  }
  else if( 0 < x <= 1 )  {
    s_x = first_layer_solution( x, k, a, b );
  }
  else if( x > 1 )  {
    s_x = second_layer_solution( x, k, a, b );
  }
  
  return s_x;
}
  
} // namespace waveEquation
  
} // namespace differential

} // namespace math

#endif
