//
//  least_square_fit_results.hpp
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef least_square_fit_results_hpp_102815
#define least_square_fit_results_hpp_102815

#include "parameters.h"
#include "termination_code.h"

namespace math{
namespace estimation{
namespace least_square{

class Result
{

private:
  Parameters best_fit_parameters;
  Termination_code termination_code;

public:
  Result(
    Parameters const best_fit_parameters,
    Termination_code const termination_code );

  auto model_parameters() const -> Parameters;
  auto info_termination_code() const -> Termination_code;
  
};

} // namespace estimation
} // namespace math
}
#endif /* least_square_fit_results_hpp */
