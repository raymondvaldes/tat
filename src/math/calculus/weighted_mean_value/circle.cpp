//
//  circle.cpp
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "math/calculus/weighted_mean_value/circle.h"

#include "math/numIntegration/integrate.h"
#include <cmath>
#include <vector>

namespace math{
namespace calculus{
namespace weighted_mean_value{

auto circle_complex
(
  std::function<std::pair<double, double >(double)> const & f,
  std::function< double(double) > const & weighting_function,
  double const R,
  double const dr_i_step
)
noexcept -> std::pair<double, double>
{
  using math::numIntegration::integrate;
  using std::pow;
  using std::vector;
  using std::make_pair;
  
  // find the mean value of a function from a to b.
  // mean_value = 2/(R^2) * Int[ ( f * r ) dr, 0, R ]

  auto const func = [&f, &weighting_function]
  (
    vector< double > const & y,
    vector< double > & dr,
    double const r
  ) noexcept -> void
  {
    auto const f_eval = f(r);
    auto const w = weighting_function(r);
    
    dr[0] = f_eval.first * w * r;
    dr[1] = f_eval.second * w * r;
    dr[2] = w * r;
  };

  auto f_0= vector< double > ( { 0, 0, 0 } );
  auto const r0 = double(0) ;
  auto const r1 = R ;

  integrate( func, f_0, r0 , r1, dr_i_step );

  auto const weighted_area = f_0[2];
  
  auto const mean_first  =  ( f_0[0] ) / weighted_area ;
  auto const mean_second =  ( f_0[1] ) / weighted_area ;
  
  auto const mean = make_pair( mean_first, mean_second ) ;
  return mean;

}

} // namespace weighted_mean_value
} // namespace calculus
} // namespace math
