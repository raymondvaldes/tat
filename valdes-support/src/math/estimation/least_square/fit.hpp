//
//  least_square_fit.hpp
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef least_square_fit_hpp_102815
#define least_square_fit_hpp_102815

#include <exception>

#include "result.hpp"
#include "settings.h"
#include "minimization_function.h"
#include "points_to_fit.h"
#include "parameters.h"

namespace math{
namespace estimation{
namespace least_square{

/*
  Minimization_function:

  Must provide a function that takes a double* of parameters and then populates
  a double* of fvec residuals.

  Points_to_fit: This is necessary to size the arrays correctly.

  Parameters_to_fit: Array of initial values that will be modified.
*/
class Improper_fit_input: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Improper fit input.";
  }
};

class Iterations_maxed_out: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Iterations maxed out.";
  }
};



auto fit
(
  Minimization_function fcn,
  Points_to_fit const dataPoints,
  Parameters const & initialConditions,
  Settings const &Settings
) -> Result;

}
} // namespace estimation
} // namespace math

#endif /* least_square_fit_hpp */
