//
//  circle_complex.h
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_math_calculus_mean_value_circle_complex_h
#define tat_math_calculus_mean_value_circle_complex_h

#include <utility>
#include <functional>

namespace math{
namespace calculus{
namespace mean_value{

auto circle_complex
(
  std::function<std::pair<double, double >(double)> const & f,
  double const R,
  double const dr_i_step = 0.01
)
noexcept -> std::pair<double, double>;

} // namespace mean_value
} // namespace calculus
} // namespace math

#endif
