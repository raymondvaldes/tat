//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 10/19/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit_a_s_re_RC.hpp"
#include <gsl.h>

#include "fitting_algorithm.hpp"
#include "thermal/model/oneLayer2D/finite_disk/parameter_list.hpp"
#include "update_system_properties_generator.hpp"
#include "update_disk_optics.hpp"

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
  
  // parameter estimation algorithm
  auto const model =
  update_system_properties_generator( slab_initial, optics_initial, parameters);
  
  auto m_parameters = model.first;
  auto m_evaluate = model.second;
  
  auto const result =
  fitting_algorithm( frequencies, exp_phases, m_parameters , m_evaluate  );

 return result;
}

} } } } } }
