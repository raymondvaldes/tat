//
//  map_parameter_name.hpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef map_parameter_name_hpp
#define map_parameter_name_hpp

#include "parameter_list.hpp"
#include "thermal/model/optics/optics.h"
#include "thermal/model/slab/slab.h"
#include <string>

namespace thermal{
namespace model{
namespace oneLayer2D{

auto map_parameter_name
(
  Parameter const parameter,
  slab::Slab const & slab,
  Optics const & optics
)
noexcept -> std::string;

}}}
#endif /* map_parameter_name_hpp */
