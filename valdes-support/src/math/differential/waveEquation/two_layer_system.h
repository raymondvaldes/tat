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
#include <complex>
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
  using std::tanh;
  using units::tanh;
  
  auto const numerator    = a + b * tanh( k ) ;
  auto const denominator  = b * k + a * k * tanh( k ) ;
  auto const s  = numerator / denominator;
  
  return s;
}
  
template< typename T, typename Y >
auto first_layer_solution
(
  T const x,
  Y const k,
  T const a,
  T const b
) noexcept -> Y
{
  using std::sinh;
  using std::cosh;
  using std::tanh;
  using units::sinh;
  using units::cosh;
  using units::tanh;
  auto const kx = k * x;

  auto
  s  =    cosh( kx )  * ( a + b * tanh( k ) );
  s  /=  ( k * b + k * a * tanh( k ) );
  
  s -= sinh( kx ) / k ;
  
  return s;
}

template< typename T, typename Y >
auto second_layer_solution
(
  T const x,
  Y const k,
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
  
  auto const
  s   = a * exp( ( k - kx ) / a )  
      / k * ( b * cosh( k ) + a * sinh( k ) ) ;
  
  return s;
}
  
template< typename D, typename C >
auto two_layer_system_without_resistance
(
  D const x,
  C const k,
  D const a,
  D const b
) noexcept -> C
  // transient heat condution with periodic formulation (complex combination)
  // eq:     s1''(x) - (k^2) s1(x) == 0
  // eq: a * s2''(x) - (k^2) s2(x) == 0

  // BC:  s1'(0) == -1              //ex. periodic heat flux cos(wt)
  // BC:  s1( 1 ) = s2 ( 1 )        //ex. temperature continuity
  // BC:  s2'( 1 ) == b * s2'( 1 )  //ex. heat flux continuity
  // BC:  s2( Inf )  == 0           //ex. temperature goes to 0
{
  auto s_x = C();
  
  using namespace units;
  using std::abs;
  
  auto const at_surface = abs( x - 0 ) < 1e-6;
  auto const in_first_layer = 0 < x <= 1;
  auto const in_second_layer = x > 1;
  
  if( at_surface ){
    s_x = surface_solution( k, a, b ) ;
  }
  else if( in_first_layer )  {
    s_x = first_layer_solution( x, k, a, b );
  }
  else if( in_second_layer )  {
    s_x = second_layer_solution( x, k, a, b );
  }
  
  return s_x;
}
  
template< typename T, typename Y >
auto surface_solution_with_resistance
(
  Y const k,
  T const a,
  T const b,
  T const R
) noexcept -> Y
{
  using std::sinh;
  using std::cosh;
  using units::sinh;
  using units::cosh;
  using units::coth;
  //auto const coth = []( auto const e ) noexcept { return cosh(e)/sinh(e); } ;

  auto const bRk = b * R * k;
  
  auto const numerator    = b + ( a + bRk ) * coth( k ) ;
  auto const denominator  = k * ( a + bRk + b * coth(k) ) ;
  auto const s  = numerator / denominator;
  
  return s;
}
  
template< typename T, typename Y >
auto first_layer_solution_with_resistance
(
  T const x,
  Y const k,
  T const a,
  T const b,
  T const R
) noexcept -> Y
{
  using std::sinh;
  using std::cosh;
  using units::sinh;
  using units::cosh;
  using units::coth;
  //auto const coth = []( auto const e ) noexcept { return cosh(e)/sinh(e); } ;

  auto const kx = k * x;
  auto const bRk = b * R * k;

  auto
  s  =    cosh( kx )  * ( b + ( a + bRk ) * coth( k ) );
  s  /=   a + bRk + b * coth(k) ;
  
  s -= sinh( kx ) ;
  
  s /= k ;
  
  return s;
}

template< typename T, typename Y >
auto second_layer_solution_with_resistance
(
  T const x,
  Y const k,
  T const a,
  T const b,
  T const R
) noexcept -> Y
{
  using std::sinh;
  using std::cosh;
  using std::exp;
  
  using units::sinh;
  using units::cosh;
  using units::exp;
  auto const kx = k * x;
  
  auto const
  s   = a * exp( ( k - kx ) / a )  
      / ( b * k * cosh( k ) + k * ( a + b * R * k) * sinh( k ) ) ;
  
  return s;
}
  
  
template< typename D, typename C >
auto two_layer_system_with_resistance
(
  D const x,
  C const k,
  D const a,
  D const b,
  D const R
) noexcept -> C
  // transient heat condution with periodic formulation (complex combination)
  // eq:     s1''(x) - (k^2) s1(x) == 0
  // eq: a * s2''(x) - (k^2) s2(x) == 0

  // BC:  s1'(0) == -1              //ex. periodic heat flux cos(wt)
  // BC:  s1( 1 ) = s2 ( 1 )        //ex. temperature continuity
  // BC:  s2'( 1 ) == b * s2'( 1 )  //ex. heat flux continuity
  // BC:  s2( Inf )  == 0           //ex. temperature goes to 0
{
  auto s_x = C();
  
  using namespace units;
  using std::abs;
  
  auto const at_surface = abs( x - 0 ) < 1e-6;
  auto const in_first_layer = 0 < x <= 1;
  auto const in_second_layer = x > 1;
  
  if( at_surface ){
    s_x = surface_solution_with_resistance( k, a, b, R ) ;
  }
  else if( in_first_layer )  {
    s_x = first_layer_solution_with_resistance( x, k, a, b, R );
  }
  else if( in_second_layer )  {
    s_x = second_layer_solution_with_resistance( x, k, a, b, R );
  }
  
  return s_x;
}

template< typename D, typename C >
auto two_layer_system
(
  D const x,
  C const k,
  D const a,
  D const b,
  D const R
) noexcept -> C
{
  auto s_x = C();
  
  using namespace units;
  using std::abs;
  
  auto const negligible_contact_resistance = abs(R - 0) < 1e-6;
  
  if( negligible_contact_resistance ){
    s_x = two_layer_system_without_resistance( x, k, a, b ) ;
  }
  else {
    s_x = two_layer_system_with_resistance( x, k, a, b, R );
  }
  
  return s_x;

}
  
} // namespace waveEquation
  
} // namespace differential

} // namespace math

#endif
