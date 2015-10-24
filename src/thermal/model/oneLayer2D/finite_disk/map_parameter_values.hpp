//
//  scale_parameters.hpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef scale_parameters_hpp_102315
#define scale_parameters_hpp_102315

#include "parameter_list.hpp"
#include <map>
#include "disk.hpp"
#include "optics.hpp"

namespace thermal { 
namespace model {
namespace oneLayer2D { 
namespace finite_disk {

using Map_parameter_values = std::map< Parameter, double >;

auto map_parameter_values
(
  Parameters const & parameters,
  Disk const & disk,
  Optics const & optics
)
noexcept -> Map_parameter_values;


} } } }


#endif /* scale_parameters_hpp */
