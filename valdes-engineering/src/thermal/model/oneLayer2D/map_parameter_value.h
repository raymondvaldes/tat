//
//  map_parameter_quantity.h
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef map_parameter_quantity_h_1016f43253123
#define map_parameter_quantity_h_1016f43253123

#include "parameter_list.hpp"
#include <map>
#include "thermal/model/optics/optics.h"
#include "thermal/model/slab/slab.h"

#include <gsl.h>

namespace thermal{
namespace model{
namespace oneLayer2D{

auto map_parameter_value
(
  Parameter const parameter,
  slab::Slab const & slab,
  Optics const & optics
)
noexcept -> double;

}}}

#endif /* map_parameter_quantity_h */
