//
//  make_minimization_equation.hpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef make_minimization_equation_hpp_13hiunf3iu4n83
#define make_minimization_equation_hpp_13hiunf3iu4n83

#include <functional>
#include "thermal/analysis/oneLayer2D/theoretical_results.hpp"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace phase_analysis{

auto minimization_equation
(
  std::function< Theoretical_results( const double *  ) >
  const & model_predictions
)
noexcept -> std::function< void( const double *, double * ) >;
  

} } } }

#endif /* make_minimization_equation_hpp */
