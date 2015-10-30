//
//  print_quantity.hpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef print_quantity_hpp
#define print_quantity_hpp

#include "parameter_list.hpp"
#include "thermal/model/optics/optics.h"
#include "thermal/model/slab/slab.h"
#include <string>

namespace thermal{
namespace model{
namespace oneLayer2D{

auto print_quantity(
  Parameter const parameter,
  slab::Slab const & slab,
  Optics const & optics
) noexcept -> std::string;

}}}

#endif /* print_quantity_hpp */
