//
//  fitting_algorithm.cpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fitting_algorithm.hpp"
#include "theoretical_modeling.hpp"
#include "make_minimization_equation.hpp"

#include "math/estimation/lmdiff.hpp"
#include "statistics/uncertainty_analysis/goodness_of_fit/goodness_of_fit.h"


namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

using statistics::uncertainty_analysis::goodness_of_fit;
using math::estimation::lmdif;
using math::estimation::settings;
using std::get;
using estimate_parameters::phase_analysis::Best_fit;

auto fitting_algorithm
(
  equipment::laser::Modulation_frequencies const & frequencies,
  emission::Phases const & exp_phases,
  std::vector<double> & model_parameters,
  std::function<
  std::tuple<
    model::slab::Slab,
    model::Optics >
  ( const double * x)> const & model_evaluate
)
noexcept -> estimate_parameters::phase_analysis::Best_fit
{
  auto const model_predictions_generator =
  theoretical_modeling( frequencies, exp_phases, model_evaluate );

  auto const min_equation = minimization_equation( model_predictions_generator );
  
  auto lmdif_settings = settings{};
  lmdif_settings.factor = 50.0 ;   // initial step size
  lmdif_settings.xtol = .00001;   // tolerance between x-iterates
  lmdif_settings.epsfcn = 1e-4; // tolerance of phase function

  auto const size = frequencies.size();
  lmdif(  min_equation, size, model_parameters, lmdif_settings ) ;

  ////// prepare output
  auto const x = model_parameters.data();
  auto const t = model_evaluate( x );

  auto const slab_fit = get< 0 >(t);
  auto const optics_fit = get< 1 >(t);

  auto const theoretical_modeling = model_predictions_generator( x );
  auto const phase_predictions = theoretical_modeling.model_predictions.phases();
  auto const calibrated_observations = theoretical_modeling.calibrated_observations;
  auto const phase_goodness_of_fit = goodness_of_fit( calibrated_observations , phase_predictions );

  auto const result = Best_fit(
    slab_fit, optics_fit, phase_goodness_of_fit );
  
  return result;
}

} } } } } }


