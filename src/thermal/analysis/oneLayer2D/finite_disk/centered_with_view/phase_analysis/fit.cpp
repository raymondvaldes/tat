//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit.hpp"
#include "fitting_algorithm.hpp"
#include "thermal/analysis/oneLayer2D/update_system_properties_generator.hpp"
#include <gsl.h>

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

auto fit
(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures,
  model::slab::Slab const & slab_initial,
  model::Optics const & optics_initial,
  model::oneLayer2D::finite_disk::Parameters const & parameters
)
noexcept -> Best_fit
{
  Expects( frequencies.size() == temperatures.size() );
  Expects( !parameters.empty() );
  
  // parameter estimation algorithm
  auto const model =
  update_system_properties_generator( slab_initial, optics_initial,parameters );
  
  auto m_parameters = model.first;
  auto m_evaluate = model.second;
  
  auto const result =
  fitting_algorithm( frequencies, temperatures, m_parameters , m_evaluate  );

 return result;
}

} } } } } }

