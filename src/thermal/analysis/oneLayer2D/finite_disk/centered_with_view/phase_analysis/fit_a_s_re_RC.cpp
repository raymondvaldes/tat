//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 10/19/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit_a_s_re_RC.hpp"
#include <gsl.h>
#include "fit.hpp"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

auto fit_a_s_re_RC
(
  equipment::laser::Modulation_frequencies const & frequencies,
  emission::Phases const & exp_phases,
  model::slab::Slab const & slab_initial,
  model::Optics const & optics_initial
)
noexcept -> estimate_parameters::phase_analysis::Best_fit
{
  Expects( !frequencies.empty() );
  Expects( !exp_phases.empty() );
  Expects( frequencies.size() == exp_phases.size() );
  
  using thermal::model::oneLayer2D::finite_disk::Parameters;
  auto const parameters = Parameters({
    thermal::model::oneLayer2D::finite_disk::Parameter::thermal_diffusivity,
    thermal::model::oneLayer2D::finite_disk::Parameter::specimen_radius,
    thermal::model::oneLayer2D::finite_disk::Parameter::detector_radius,
    thermal::model::oneLayer2D::finite_disk::Parameter::rc_filter
  });
  
  auto const result =
  fit( frequencies, exp_phases, slab_initial, optics_initial, parameters);
  return result;
}

} } } } } }
