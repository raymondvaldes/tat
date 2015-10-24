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
#include "thermal/analysis/oneLayer2D/phase_analysis/make_minimization_equation.hpp"
#include "math/estimation/lmdiff.hpp"
#include "thermal/model/complex/temperatures.h"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

using math::estimation::lmdif;
using math::estimation::settings;
using std::get;
using estimate_parameters::phase_analysis::Best_fit;
using thermal::analysis::oneLayer2D::phase_analysis::minimization_equation;

auto fitting_algorithm
(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures,
  std::vector<double> & model_parameters,
  std::function<
  std::tuple<
    model::slab::Slab,
    model::Optics >
  ( const double * x)> const & model_evaluate
)
noexcept -> estimate_parameters::phase_analysis::Best_fit
{
  auto const exp_phases = temperatures.phases();

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
  auto const theoretical_modeling = model_predictions_generator( x );


  auto const t = model_evaluate( x );
  auto const slab_fit = get< 0 >(t);
  auto const optics_fit = get< 1 >(t);
  
  auto const result = Best_fit(
    slab_fit, optics_fit, theoretical_modeling.phase_goodness_of_fit() );
  
  return result;
}

} } } } } }


