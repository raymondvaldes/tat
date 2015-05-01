//
//  csch.cpp
//  tat
//
//  Created by Raymond Valdes on 4/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>
#include <complex>
#include <cassert>

#include "math/functions/trigonometric/csch.h"

using std::complex;

namespace math{
namespace functions {
namespace trigonometric{

auto csch( double const a ) noexcept -> double
{
  assert( a > 0 );
  
  auto const sinhv = sinh( a );
  auto ratio = 1.0 / sinhv;
  
  assert( isfinite( ratio ) );
  
  return ratio;
}

auto csch( std::complex<double> const a ) noexcept -> std::complex<double>
{
  assert( a.real() > 0 || a.imag() > 0 ) ;

  auto const sinhv = sinh( a );
  auto ratio =  complex<double>(1.0, 0.0) / sinhv;
  
  assert( isfinite( ratio.real() ) );
  assert( isfinite( ratio.imag() ) );

  return ratio;
}

} // namespace trigonometric
} // namespace functions
} // namespace math
