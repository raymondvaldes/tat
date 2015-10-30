//
//  make_minimization_equation.cpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "make_minimization_equation.hpp"
#include "statistics/signal_processing/residuals/residual.h"
#include "algorithm/algorithm.h"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace phase_analysis{

using statistics::signal_processing::residual;

auto minimization_equation
(
  std::function< Theoretical_results( const double *  ) >
  const & model_predictions
)
noexcept -> std::function< void( const double *, double * ) >
{

  auto const objective_function = [ &model_predictions ]
  ( const double *x, double *fvec ) noexcept
  {
    auto const theoreticalModeling = model_predictions( x ) ;
    
    auto const predictions = theoreticalModeling.model_predictions.phases();
    auto const observations = theoreticalModeling.calibrated_observations;
    
    //populate fvec
    algorithm::transform( predictions, observations, fvec,
    []( auto const p, auto const o ) noexcept {
      return residual( p , o ).value();
    });
    
  };

  return objective_function;
}

} } } }
