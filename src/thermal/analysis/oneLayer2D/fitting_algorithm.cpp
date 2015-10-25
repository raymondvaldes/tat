//
//  fitting_algorithm.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include <gsl.h>

#include "fitting_algorithm.hpp"
#include "theoretical_modeling.hpp"
#include "math/estimation/lmdiff.hpp"
#include "thermal/model/complex/temperatures.h"
#include "thermal/model/oneLayer2D/model_selection.h"
#include "thermal/model/oneLayer2D/generator/disk.hpp"

namespace thermal{
namespace analysis{
namespace oneLayer2D{

using math::estimation::lmdif;
using math::estimation::settings;
using std::get;
using thermal::model::oneLayer2D::Detector_model;
using thermal::model::oneLayer2D::Conduction_model;
using thermal::model::oneLayer2D::generator::Disk;

auto const detector_model = Detector_model::center_with_view;
auto const conduction_model = Conduction_model::finite_disk;

auto fitting_algorithm
(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures,
 
  std::pair< std::vector<double> ,
    std::function<
    std::tuple<
      model::slab::Slab,
      model::Optics  >( const double * x )  >
      > const & system,

  std::function<
    model::complex::Temperatures(
        model::slab::Slab const &,
        model::Optics const &,
        equipment::laser::Modulation_frequencies const & )
  > const & frequency_sweep,
 
  std::function<
    std::function< void( const double *, double * ) >(
      std::function< Theoretical_results( const double *  ) > const &)
  >
  const & minimization_equation
)
noexcept -> Best_fit
{
  Expects( !temperatures.empty() );
  
  auto model_parameters = system.first;
  auto const system_updater = system.second;

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


} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal
