//
//  coth.h
//  tat
//
//  Created by Raymond Valdes on 4/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_math_functions_trogonometric_coth_h
#define tat_math_functions_trogonometric_coth_h

#include <complex>

namespace math{
namespace functions {
namespace trigonometric{

auto coth( double const a ) noexcept -> double;

auto coth( std::complex<double> const a ) noexcept -> std::complex<double>;


} // namespace trigonometric
} // namespace functions
} // namespace math

#endif

