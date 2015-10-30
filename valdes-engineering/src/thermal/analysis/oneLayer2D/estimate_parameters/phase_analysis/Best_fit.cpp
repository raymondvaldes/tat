//
//  Best_fit.cpp
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <cassert>
#include <iostream>

#include "plot/gnuplot.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/Best_fit.h"
#include "statistics/uncertainty_analysis/goodness_of_fit/goodness_of_fit.h"
#include "thermal/define/lthermal.h"
#include "units.h"


using thermal::define::thermalPenetrations_from_frequencies;

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace phase_analysis{


Best_fit::Best_fit
(
  thermal::model::oneLayer2D::Conduction_model const conduction_model,
  thermal::model::oneLayer2D::Detector_model const detector_model,
  thermal::model::slab::Slab const slab,
  thermal::model::Optics const optics,
  double const phase_goodness_of_fit
) noexcept :
  engine( conduction_model, detector_model, slab, optics ),
  slab( slab ),
  optics( optics ),
  phase_goodness_of_fit( phase_goodness_of_fit)
{}

auto Best_fit::evaluate
(
  equipment::laser::Modulation_frequencies const & modulation_frequencies
)
const -> thermal::model::complex::Temperatures
{
  return engine.evaluate( modulation_frequencies );
}

auto Best_fit::phase_goodness_of_fit_function() const -> double
{
//  auto const predictions = model_predictions.phases();
//  auto const gf = goodness_of_fit( calibrated_observations , predictions );

  auto const gf = 42;
  return gf;
}


//auto caliberate_experimental_temperatures(
//  equipment::laser::Modulation_frequencies const & frequencies,
//  model::complex::Temperatures const & temperatures
//  ) noexcept -> model::complex::Temperatures ;
//

} // namespace phase_analysis
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal
