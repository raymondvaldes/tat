//
//  csc.h
//  tat
//
//  Created by Raymond Valdes_New on 3/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_csc_h
#define tat_csc_h

#include <cmath>
#include <complex>

namespace math{

namespace functions {

namespace trigonometric{


template< typename T >
auto csc( std::complex<T> const a ) noexcept
{
  using std::sin;
  using std::complex;
  using namespace std::literals::complex_literals;
  
  complex<T> const one = 1.0 + 0i;

  return one / sin( a );
}


template< typename T >
auto csc( T const a ) noexcept
{
  using std::sin;
  
  return 1 / sin(a);
}

}
  
} // namespace functions

} // namespace math

#endif
