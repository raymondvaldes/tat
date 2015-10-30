//
//  model_vs_experiment.cpp
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "model_vs_experiment.hpp"
#include "amplitude/model_vs_experiment_amplitudes.hpp"
#include "phase/model_vs_experiment_phases.hpp"
#include <gsl.h>

namespace thermal{
namespace plot{

auto model_vs_experiment
(
  equipment::laser::Modulation_frequencies const & frequencies,
  thermal::model::complex::Temperatures const & model,
  thermal::model::complex::Temperatures  const & experimental,
  thermal::model::complex::Fit_selection const fit_selection
) noexcept -> void
{
  Expects( frequencies.size() == model.size() );
  Expects( frequencies.size() == experimental.size());
  Expects( !frequencies.empty() );

  switch( fit_selection )
  {
    case model::complex::Fit_selection::phases:
    {
      auto const m = model.phases();
      auto const e = experimental.phases();

      plot::phase::model_vs_experiment_phases( frequencies, m, e );
      break;
    }
    case model::complex::Fit_selection::amplitudes:
    {
      auto const m = model.amplitudes();
      auto const e = experimental.amplitudes();

      plot::amplitudes::model_vs_experiment_amplitudes( frequencies, m, e );
      break;
    }
  }

}

} // namespace plot
} // namespace thermal

