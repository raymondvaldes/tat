//
//  check_validity_of_parameters.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "check_validity_of_parameters.hpp"
#include "thermal/model/oneLayer2D/is_valid_parameters.hpp"

namespace thermal{
namespace analysis{
namespace oneLayer2D{

auto check_validity_of_parameters(
  model::oneLayer2D::Parameters const & parameters,
  model::oneLayer2D::Valid_parameters const & valid_parameters,
  Fit_selection const fit_selection
) -> void
{
  auto pass = false;
  
  switch( Fit_selection::phases ) {
  
    case Fit_selection::phases:
    {
      pass = is_valid_parameters( parameters, valid_parameters.phase_model );
      break;
    }
    case Fit_selection::amplitudes:
    {
      pass = is_valid_parameters( parameters, valid_parameters.amplitude_model );
      break;
    }
  }
  
  if( !pass ) {
    throw thermal::model::oneLayer2D::Parameter_list_is_invalid();
  }
}

}}}


