//
//  circle.h
//  tat
//
//  Created by Raymond Valdes on 4/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_math_calculus_circle_circle_h
#define tat_math_calculus_circle_circle_h

#include "math/numIntegration/integrate.h"
#include <cmath>
#include <vector>

namespace math{
namespace calculus{
namespace mean_value{

template< typename Func >
auto circle
(
  Func const & f,
  double const R,
  double const dr_i_step = R / 100.
)
noexcept -> double
{
  using math::numIntegration::integrate;
  using std::pow;
  using std::vector
  
  // find the mean value of a function from a to b.
  // mean_value = 2/(R^2) * Int[ ( f * r ) dr, 0, R ]

  auto const func = [&f]
  (
    vector< double > const & y,
    vector< double > & dr,
    double const r
  ) noexcept -> void
  {
    dr[0] = f( r ) * r;
  };

  auto const f_r0 = vector< double > ( { 0 } );

  auto const integratation_result = integrate( func, f_r0, 0 , R, dr_i_step );
  auto const mean =  ( 2. * integratation_result ) / ( pow( R,2 ) ) ;

  return mean;
}

} // namespace mean_value
} // namespace calculus
} // namespace math

#endif
