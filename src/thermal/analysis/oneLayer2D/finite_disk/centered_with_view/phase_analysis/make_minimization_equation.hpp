//
//  minimization_equation.hpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef minimization_equation_hpp_102315
#define minimization_equation_hpp_102315

#include <functional>
#include "theoretical_modeling.hpp"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{


auto minimization_equation
(
  std::function< Theoretical_modeling( const double *  ) >
  const & model_predictions
)
noexcept -> std::function< void( const double *, double * ) >;
  

} } } } } }

#endif /* minimization_equation_hpp */
