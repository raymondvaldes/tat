//
//  least_square_fit_results.cpp
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "result.hpp"

namespace math{
namespace estimation{
namespace least_square{


Result::Result
(
  Parameters const best_fit_parameters,
  Termination_code const termination_code
):
best_fit_parameters( best_fit_parameters ),
termination_code( termination_code ) {};

auto
Result::model_parameters() const -> Parameters
{
  return best_fit_parameters;
}

auto
Result::info_termination_code() const -> Termination_code
{
  return termination_code;
}


} // namespace estimation
} // namespace math
}
