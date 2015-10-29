//
//  termination_code.h
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef termination_code_h_102815
#define termination_code_h_102815

namespace math{
namespace estimation{
namespace least_square{

enum class Termination_code
{
  improper_input,
  
  sum_square_reduction_satisfies_ftol,
  relative_error_satisfies_xtol,
  sum_square_ftol_and_relative_error_xtol,
  fvec_and_jacobian_satisfies_gtol,
  exceeds_calls_fcn_maxfev,

  ftol_is_too_small,
  xtol_is_too_small,
  gtol_is_too_small
};

}}}

#endif /* termination_code_h */
