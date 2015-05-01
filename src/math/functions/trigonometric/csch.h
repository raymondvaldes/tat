//
//  csch.h
//  tat
//
//  Created by Raymond Valdes on 4/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_math_functions_trigonometric_csch__
#define __tat_math_functions_trigonometric_csch__

#include <complex>

namespace math{
namespace functions {
namespace trigonometric{

auto csch( double const a ) noexcept -> double;

auto csch( std::complex<double> const a ) noexcept -> std::complex<double>;


} // namespace trigonometric
} // namespace functions
} // namespace math
#endif /* defined(__tat__csch__) */
