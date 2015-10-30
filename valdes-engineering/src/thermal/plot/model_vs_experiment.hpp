//
//  model_vs_experiment.hpp
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef model_vs_experiment_hpp_102815
#define model_vs_experiment_hpp_102815

#include "thermal/model/complex/temperatures.h"
#include "thermal/model/complex/selection.h"

namespace thermal{
namespace plot{

auto model_vs_experiment
(
  equipment::laser::Modulation_frequencies const & frequencies,
  thermal::model::complex::Temperatures const & model,
  thermal::model::complex::Temperatures  const & experimental,
  thermal::model::complex::Fit_selection const selection
) noexcept -> void;

} // namespace plot
} // namespace thermal
#endif /* model_vs_experiment_hpp */
