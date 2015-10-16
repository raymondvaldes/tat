//
//  model_vs_experiment_phases.hpp
//  tat
//
//  Created by Raymond Valdes on 10/15/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef model_vs_experiment_phases_hpp_101515
#define model_vs_experiment_phases_hpp_101515

#include "plot/gnuplot-iostream.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/model/complex/phase.h"


namespace thermal{
namespace plot{
namespace phase{

auto model_vs_experiment_phases
(
  equipment::laser::Modulation_frequencies const & frequencies,
  thermal::model::complex::Phases const & model_phases,
  thermal::model::complex::Phases const & experiment_phases
) noexcept -> void;

} // namespace phase
} // namespace plot
} // namespace thermal

#endif /* model_vs_experiment_phases_hpp */
