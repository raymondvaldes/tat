//
//  circle_complex.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "math/calculus/mean_value/circle/circle_complex.h"

#include "math/numIntegration/integrate.h"
#include <cmath>
#include <vector>

namespace math{
namespace calculus{
namespace mean_value{

auto circle_complex
(
  std::function<std::pair<double, double >(double)> const & f,
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

  auto const func = [&f]
  (
    vector< double > const & y,
    vector< double > & dr,
    double const r
  ) noexcept -> void
  {
    dr[0] = f( r ).first * r;
    dr[1] = f( r ).second * r;
  };

  auto f_0= vector< double > ( { 0, 0 } );
  auto const r0 = double(0) ;
  auto const r1 = R ;
\
  integrate( func, f_0, r0 , r1, dr_i_step );
  
  auto const mean_first  =  ( 2. * f_0[0] ) / ( pow( R , 2 ) ) ;
  auto const mean_second =  ( 2. * f_0[1] ) / ( pow( R , 2 ) ) ;
  
  auto const mean = make_pair( mean_first, mean_second ) ;
  return mean;
}

} // namespace mean_value
} // namespace calculus
} // namespace math
