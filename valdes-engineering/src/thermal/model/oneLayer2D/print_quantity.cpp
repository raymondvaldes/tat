//
//  print_quantity.cpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "print_quantity.hpp"
#include "map_parameter_string.hpp"
#include "map_parameter_name.hpp"

namespace thermal{
namespace model{
namespace oneLayer2D{

auto print_quantity(
  Parameter const parameter,
  slab::Slab const & slab,
  Optics const & optics
) noexcept -> std::string
{
  auto o = std::string();

  auto const name =
  [&](){ return map_parameter_name( parameter , slab, optics ); };

  auto const value_with_units =
  [&](){ return map_parameter_string( parameter , slab, optics ); };

  o = name() + std::string(": ") + value_with_units();

  return o;
}

}}}

