//
//  uncertainty_analysis.cpp
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include "math/bisection.hpp"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/uncertainty_analysis.h"

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all/diffusivity_from_phases.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_detectorRadius/diffusivity_from_phases.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_diffusivity/diffusivity_from_phases.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_laser/diffusivity_from_phases.h"

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace phase_analysis{

using namespace units;

auto uncertainty_analysis(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const slab_initial,
  units::quantity< units::si::length> const beam_radius,
  units::quantity< units::si::length > const detector_view_radius,
  units::quantity< units::si::temperature> const steady_state_temperature,
  units::quantity< units::si::wavelength> const detector_wavelength
) noexcept -> void
{
  assert( beam_radius > 0 * meters);
  assert( detector_view_radius > 0 * meters);
  assert( steady_state_temperature > 280.*kelvin );
  assert( detector_wavelength > 0 * meters );
  assert( frequencies.size() == observations.size() );
  assert( !frequencies.empty() );
  
  auto const best_fit = fit_all::diffusivity_from_phases( frequencies, observations,
  slab_initial, beam_radius, detector_view_radius, steady_state_temperature,
  detector_wavelength );

  //uncertainty in diffusivity
  /// uncertainty in diffusivity
  {
    auto const gFunc =[&best_fit, &steady_state_temperature, &detector_wavelength]
    ( double const x ) noexcept -> double
    {
      // updated best-fit slab with perturbed parameter
      auto updated_slab = best_fit.bulk_slab;
      auto const updated_thermal_diffusivity =
      quantity<thermal_diffusivity>( x * square_millimeters / second );
      updated_slab.set_diffusivity_update_rhoCp_hold_k(updated_thermal_diffusivity);
      
      // update observations to use the original model best-fit
      auto const observations = best_fit.model_phases;
      auto const frequencies = best_fit.frequencies;
      auto const beam_radius = best_fit.beam_radius;
      auto const detector_view_radius = best_fit.view_radius;
      
      auto const alternative_best_fit =
      fit_all_but_diffusivity::diffusivity_from_phases( frequencies, observations,
        updated_slab, beam_radius, detector_view_radius, steady_state_temperature,
        detector_wavelength );
      
      auto const error = alternative_best_fit.phase_goodness_of_fit ;
      return error;
    };


    auto const diffusivity_best_fit = best_fit.bulk_slab.get_diffusivity();
    auto const lowerbound = diffusivity_best_fit / 1.5;
    auto const upperbound = diffusivity_best_fit/ .15;
    
  

  }


}

} // namespace phase_analysis
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal
