//
//  map_parameter_values.hpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef map_parameter_values_hpp_102515
#define map_parameter_values_hpp_102515

#include "parameter_list.hpp"
#include <map>
#include "disk.h"
#include "thermal/model/optics/optics.h"

namespace thermal{
namespace model{
namespace oneLayer2D{


using Map_parameter_values = std::map< Parameter, double >;

auto map_parameter_values
(
  Parameters const & parameters,
  Disk const & disk,
  Optics const & optics
)
noexcept -> Map_parameter_values;

}}}

#endif /* map_parameter_values_hpp */
