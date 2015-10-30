//
//  sec.h
//  tat
//
//  Created by Raymond Valdes_New on 3/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_sec_h_math_functions
#define tat_sec_h_math_functions

#include <cmath>
#include <complex>

namespace math{

namespace functions {

namespace trigonometric{

template< typename T >
auto sec( std::complex<T> const a ) noexcept
{
  using std::cos;
  using std::complex;
  using namespace std::literals::complex_literals;
  
  complex<T> const one = 1.0 + 0i;

  return one / cos( a );
}

template< typename T >
auto sec( T const a ) noexcept
{
  using std::cos;
  
  return 1 / cos( a );
}

} // namespace trigonometric
  
} // namespace functions

} // namespace math


#endif
