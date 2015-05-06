//
//  circle.h
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_math_calculus_weighted_mean_value_circle__
#define __tat_math_calculus_weighted_mean_value_circle__

#include <utility>
#include <functional>

namespace math{
namespace calculus{
namespace weighted_mean_value{

auto circle_complex
(
  std::function<std::pair<double, double >(double)> const & f,
  std::function< double(double) > const & weighting_function,
  double const R,
  double const dr_i_step = 0.01
)
noexcept -> std::pair<double, double>;

} // namespace weighted_mean_value
} // namespace calculus
} // namespace math

#endif /* defined(__tat__circle__) */
