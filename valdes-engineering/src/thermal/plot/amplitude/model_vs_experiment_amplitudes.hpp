//
//  model_vs_experiment_amplitudes.hpp
//  tat
//
//  Created by Raymond Valdes on 10/27/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef model_vs_experiment_amplitudes_hpp_10271534f34f
#define model_vs_experiment_amplitudes_hpp_10271534f34f

#include "plot/gnuplot-iostream.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/model/complex/amplitude.h"

namespace thermal{
namespace plot{
namespace amplitudes{

auto model_vs_experiment_amplitudes
(
  equipment::laser::Modulation_frequencies const & frequencies,
  thermal::model::complex::Amplitudes const & model,
  thermal::model::complex::Amplitudes const & experiment
) noexcept -> void;

} // namespace ammplitudes
} // namespace plot
} // namespace thermal

#endif /* model_vs_experiment_amplitudes_hpp */
