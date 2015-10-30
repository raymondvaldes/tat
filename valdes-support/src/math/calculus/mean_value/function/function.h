//
//  function.h
//  tat
//
//  Created by Raymond Valdes on 4/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_math_calculus_mean_value_function_h
#define tat_math_calculus_mean_value_function_h

#include "math/numIntegration/integrate.h"

namespace math{
namespace calculus{
namespace mean_value{

template< typename Func >
auto function
(
  Func const & f,
  double const a, double const b,
  double const dx_i_step = ( b - a ) / 100.
)
noexcept -> double
{
  using math::numIntegration::integrate;
  // find the mean value of a function from a to b.
  // mean_value = 1/(b-a) * Int[ f dx, a, b ]

  auto const func = []
  (
    vector< double > const & y,
    vector< double > & dx,
    double const x
  ) noexcept -> void
  {
    dx[0] = f( x );
  };

  auto const f_x0 = vector< double > ( { a } );

  auto const integratation_result = integrate( func, f_x0, a, b, dx_i_step );
  auto const mean =  integratation_result / ( b - a ) ;

  return mean;
}

} // namespace mean_value
} // namespace calculus
} // namespace math

#endif
