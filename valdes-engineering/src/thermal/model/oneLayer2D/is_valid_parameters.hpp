//
//  is_valid_parameters.hpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef is_valid_parameters_hpp_13f23f234c2cf
#define is_valid_parameters_hpp_13f23f234c2cf

#include "parameter_list.hpp"

namespace thermal{
namespace model{
namespace oneLayer2D{

auto is_valid_parameters(
  Parameters const & parameters,
  Parameters const & valid_parameters
) noexcept -> bool;


} // namespace oneLayer2D
} // namespace model
} // namespace thermal


#endif /* is_valid_parameters_hpp */
