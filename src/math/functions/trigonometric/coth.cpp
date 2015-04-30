//
//  coth.cpp
//  tat
//
//  Created by Raymond Valdes on 4/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cmath>
#include <complex>
#include <cassert>

#include "math/functions/trigonometric/coth.h"

using std::cosh;
using std::sinh;
using std::isinf;

namespace math{
namespace functions {
namespace trigonometric{

/// coth of theta in double
auto coth( double const a ) noexcept -> double
{
  auto const coshv = cosh( a );
  auto const sinhv = sinh( a );
  auto ratio = coshv / sinhv;

  if( isinf(coshv) && isinf(sinhv) ) ratio = 1.0;
  
  assert( isfinite( ratio ) );
  
  return ratio;
}

auto coth( std::complex<double> const a ) noexcept -> std::complex<double>
{
  auto const coshv = cosh( a );
  auto const sinhv = sinh( a );
  auto ratio = coshv / sinhv;

  if( !isnormal(ratio.real()) || !isnormal(ratio.imag()) ) {
    ratio = 1.0;
  }
  
  assert( isfinite( ratio.real() ) );
  assert( isfinite( ratio.imag() ) );

  return ratio;
}

} // namespace trigonometric
} // namespace functions
} // namespace math
