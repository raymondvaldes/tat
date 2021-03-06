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
#include "check_validity_of_parameters.hpp"
#include "check_validity_of_observations.hpp"

namespace thermal{
namespace analysis{
namespace oneLayer2D{

auto fit(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures,
  Fit_selection const to_fit,
  model::oneLayer2D::generator::Disk const & disk,
  model::oneLayer2D::Parameters const & parameters  
) -> Best_fit
{
  // can throw if incorrect size or values
  check_validity_of_observations( frequencies, temperatures );

  // can throw if invalid parameters (for model)
  check_validity_of_parameters( parameters, disk.valid_parameters(), to_fit );
  
  // can throw if invalid model (not model implemented)
  auto const frequency_sweep = disk.get_emission_sweep();
  
  
  auto const minimization_equation = select_minimization_function( to_fit );
  auto const system = update_system_properties_generator(
    disk.get_slab(), disk.get_optics() , parameters );
  
  // can throw if incorrect setup or max iterations met (either is a failed fit)
  auto const result =
  fitting_algorithm( frequencies, temperatures,
                      system, frequency_sweep,
                      minimization_equation  );
  return result;
}

}}}
