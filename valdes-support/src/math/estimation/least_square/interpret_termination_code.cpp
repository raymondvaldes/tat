//
//  interpret_termination_code.cpp
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "interpret_termination_code.hpp"


namespace math{
namespace estimation{
namespace least_square{

auto interpret_termination_code( int const code ) noexcept -> Termination_code
{
  auto t = Termination_code();
  
  
  switch( code )
  {
    case 0:
    {
      //*	  info = 0  improper input parameters.
      t = Termination_code::improper_input;
      break;
    }
    case 1:
    {
      //*	  info = 1  both actual and predicted relative reductions
      //*		    in the sum of squares are at most ftol.
      t = Termination_code::sum_square_reduction_satisfies_ftol;
      break;
    }
    case 2:
    {
      //*	  info = 2  relative error between two consecutive iterates
      //*		    is at most xtol.
      t = Termination_code::relative_error_satisfies_xtol;
      break;
    }
    case 3:
    {
      //*	  info = 3  conditions for info = 1 and info = 2 both hold.
      t = Termination_code::sum_square_ftol_and_relative_error_xtol;
      break;
    }
    case 4:
    {
      //*	  info = 4  the cosine of the angle between fvec and any
      //*		    column of the jacobian is at most gtol in
      //*		    absolute value.
      t = Termination_code::fvec_and_jacobian_satisfies_gtol;
      break;
    }
    case 5:
    {
      //*	  info = 5  number of calls to fcn has reached or
      //*		    exceeded maxfev.
      t = Termination_code::exceeds_calls_fcn_maxfev;
      break;
    }
    case 6:
    {
      //*	  info = 6  ftol is too small. no further reduction in
      //*		    the sum of squares is possible.
      t = Termination_code::ftol_is_too_small;
      break;
    }
    case 7:
    {
      //*	  info = 7  xtol is too small. no further improvement in
      //*		    the approximate solution x is possible.
      t = Termination_code::xtol_is_too_small;
      break;
    }
    case 8:
    {
      //*	  info = 8  gtol is too small. fvec is orthogonal to the
      //*		    columns of the jacobian to machine precision.
      t = Termination_code::gtol_is_too_small;
      break;
    }
  }
  
  return t;
}


}}}
