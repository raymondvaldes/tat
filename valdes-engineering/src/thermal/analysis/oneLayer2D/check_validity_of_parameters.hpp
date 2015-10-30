//
//  check_validity_of_parameters.hpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef check_validity_of_parameters_hpp_34f234rc
#define check_validity_of_parameters_hpp_34f234rc

#include "parameter_list.hpp"
#include "fit_selection.h"

namespace thermal{
namespace analysis{
namespace oneLayer2D{

auto check_validity_of_parameters(
  model::oneLayer2D::Parameters const & parameters,
  model::oneLayer2D::Valid_parameters const & valid_parameters,
  Fit_selection const fit_selection
 ) -> void;

}}}


#endif /* check_validity_of_parameters_hpp */
