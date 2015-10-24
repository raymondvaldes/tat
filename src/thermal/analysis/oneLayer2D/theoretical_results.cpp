//
//  theoretical_modeling.cpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "theoretical_modeling.hpp"
#include "algorithm/vector/add.h"
#include "statistics/uncertainty_analysis/goodness_of_fit/goodness_of_fit.h"

namespace thermal{
namespace analysis{
namespace oneLayer2D {

using std::get;
using algorithm::vector::add;

using statistics::uncertainty_analysis::goodness_of_fit;

Theoretical_results::Theoretical_results(
  emission::Phases const & observations_,
  model::complex::Temperatures const & model_predictions_,
  emission::Phases const & experimental_bias_
)
: observations( observations_ ),
  model_predictions( model_predictions_ ),
  experimental_bias( experimental_bias_ ),
  calibrated_observations( add( observations, experimental_bias ) )
  //calibrated_observations(observations )  //enable this to ignore RC filter
{};


auto Theoretical_results::phase_goodness_of_fit() const noexcept -> double
{
  auto const predictions = model_predictions.phases();
  auto const gf = goodness_of_fit( calibrated_observations , predictions );

  return gf;
}


} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal
