//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit.hpp"
#include "fitting_algorithm.hpp"
#include "update_system_properties_generator.hpp"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

auto fit
(
  equipment::laser::Modulation_frequencies const & frequencies,
  emission::Phases const & exp_phases,
  model::slab::Slab const & slab_initial,
  model::Optics const & optics_initial,
  model::oneLayer2D::finite_disk::Parameters const & parameters
)
noexcept -> estimate_parameters::phase_analysis::Best_fit
{
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

