//
//  fitting_algorithm.cpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fitting_algorithm.hpp"
#include "make_minimization_equation.hpp"
#include "thermal/analysis/oneLayer2D/theoretical_modeling.hpp"
#include "thermal/analysis/oneLayer2D/phase_analysis/make_minimization_equation.hpp"
#include "math/estimation/lmdiff.hpp"
#include "thermal/model/complex/temperatures.h"
#include <gsl.h>
#include "thermal/model/oneLayer2D/model_selection.h"
#include "thermal/model/oneLayer2D/generator/disk.hpp"
#include "thermal/model/oneLayer2D/finite_disk/emission/centered_detector_with_view/frequency_sweep.hpp"

namespace thermal {
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

using math::estimation::lmdif;
using math::estimation::settings;
using std::get;
using thermal::analysis::oneLayer2D::phase_analysis::minimization_equation;
using thermal::model::oneLayer2D::Detector_model;
using thermal::model::oneLayer2D::Conduction_model;
using thermal::model::oneLayer2D::generator::Disk;
using thermal::model::oneLayer2D::finite_disk::disk::emission::centered_detector_with_view::frequency_sweep;


auto const detector_model = Detector_model::center_with_view;
auto const conduction_model = Conduction_model::finite_disk;

auto fitting_algorithm
(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures,
  std::vector<double> & model_parameters,
  std::function<
  std::tuple<
    model::slab::Slab,
    model::Optics >
  ( const double * x)> const & system_updater
)
noexcept -> Best_fit
{
  Expects( !temperatures.empty() );

  auto const predictions_generator =
  theoretical_modeling( frequencies, temperatures, system_updater, frequency_sweep );

  auto const min_equation = minimization_equation( predictions_generator );
  
  auto lmdif_settings = settings{};
  lmdif_settings.factor = 50.0 ;   // initial step size
  lmdif_settings.xtol = .00001;   // tolerance between x-iterates
  lmdif_settings.epsfcn = 1e-4; // tolerance of phase function

  auto const size = frequencies.size();
  lmdif(  min_equation, size, model_parameters, lmdif_settings ) ;

  ////// prepare output
  auto const x = model_parameters.data();
  auto const final_results = predictions_generator( x );

  auto const t = system_updater( x );
  auto const slab_fit = get< 0 >(t);
  auto const optics_fit = get< 1 >(t);
  
  auto const best_fit_disk =
  Disk( conduction_model, detector_model, slab_fit, optics_fit );
  
  auto const result = Best_fit( best_fit_disk, final_results );
  
  return result;
}

} } } } } }


