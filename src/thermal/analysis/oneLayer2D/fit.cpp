//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit.hpp"
#include <gsl.h>
#include "thermal/model/oneLayer2D/model_selection.h"

#include "thermal/model/oneLayer2D/select_emission_model.hpp"
#include "select_minimization_function.hpp"
#include "update_system_properties_generator.hpp"
#include "fitting_algorithm.hpp"

namespace thermal{
namespace analysis{
namespace oneLayer2D{

auto fit(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures,
  Fit_selection const fit_selection,
  model::oneLayer2D::generator::Disk const & initial_disk,
  model::oneLayer2D::Parameters const & parameters  
) -> Best_fit
{
  Expects( !frequencies.empty() && !temperatures.empty() );
  Expects( frequencies.size() == temperatures.size() );
  Expects( !parameters.empty() );

  auto const frequency_sweep = initial_disk.get_emission_sweep();

  auto const minimization_equation =
  select_minimization_function( fit_selection );
  
  // parameter estimation algorithm
  auto const system = update_system_properties_generator(
    initial_disk.get_slab(), initial_disk.get_optics() , parameters );
  
  auto const result =
  fitting_algorithm( frequencies, temperatures,
                      system, frequency_sweep,
                      minimization_equation  );
  return result;
}



}}}

