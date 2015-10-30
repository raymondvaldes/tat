//
//  print_quantities.hpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef print_quantities_hpp
#define print_quantities_hpp

#include <string>
#include "print_quantity.hpp"
#include "parameter_list.hpp"

namespace thermal{
namespace model{
namespace oneLayer2D{

auto print_quantities(
  Parameters const parameters,
  slab::Slab const & slab,
  Optics const & optics
  ) noexcept -> std::string;

} // namespace
} // namespace
} // namespace

#endif /* print_quantities_hpp */
