//
//  least_square_fit.cpp
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit.hpp"
#include "fitting_algorithm.h"
#include "settings.h"
#include <gsl.h>
#include <cmath>
#include "interpret_termination_code.hpp"

namespace math{
namespace estimation{
namespace least_square{

using std::isfinite;

auto fit
(
  Minimization_function fcn,
  Points_to_fit const dataPoints,
  Parameters const & initialConditions,
  Settings const & Settings
)
-> Result
{
  Expects( !initialConditions.empty() );
  Expects( dataPoints > 0  && isfinite( dataPoints ) );

  auto fitting_parameters = initialConditions;
  auto const c = lmdif( fcn, dataPoints, fitting_parameters, Settings );
  auto const code = interpret_termination_code( c );


  switch( code ) {
    case Termination_code::improper_input:
      throw Improper_fit_input();
      break;
    
    case Termination_code::exceeds_calls_fcn_maxfev:
      throw Iterations_maxed_out();
      break;

    default:
      break;
  }

  auto const o = Result( fitting_parameters, code );

  return o;
}

} // namespace estimation
} // namespace math
}

