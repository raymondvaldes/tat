//
//  check_validity_of_parameters.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "check_validity_of_parameters.hpp"
#include "thermal/model/oneLayer2D/is_valid_parameters.hpp"
#include <gsl.h>

namespace thermal{
namespace analysis{
namespace oneLayer2D{

auto check_validity_of_parameters(
  model::oneLayer2D::Parameters const & parameters,
  model::oneLayer2D::Valid_parameters const & valid_parameters,
  Fit_selection const fit_selection
) -> void
{
  if( valid_parameters.empty() ) {
    throw thermal::model::oneLayer2D::Parameter_list_empty();
  }
  
  auto pass = false;
  
  switch( fit_selection ) {
  
    case Fit_selection::phases:
    {
      auto const v = valid_parameters.phase_model;
      pass = is_valid_parameters( parameters, v );
      break;
    }
    case Fit_selection::amplitudes:
    {
      auto const v = valid_parameters.phase_model;
      pass = is_valid_parameters( parameters, v );
      break;
    }
  }
  
  if( !pass ) {
    throw thermal::model::oneLayer2D::Parameter_list_is_invalid();
  }
}

}}}


