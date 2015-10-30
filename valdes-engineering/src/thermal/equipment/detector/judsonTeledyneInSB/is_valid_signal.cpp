//
//  is_valid_signal.c
//  tat
//
//  Created by Raymond Valdes on 10/4/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "is_valid_signal.hpp"

namespace thermal{
namespace equipment{
namespace detector{
namespace judsonTeledyneInSB{

using namespace units;
using std::isnormal;
using units::isnormal; 

auto is_valid_signal( Signal const signal ) noexcept -> bool
{
  auto const is_outside_range = signal < 0 * volts || signal > 15 * volts;
  auto const is_inside_range = !is_outside_range;

  auto const is_valid = is_inside_range && isnormal( signal );

  return is_valid;
}

auto is_invalid_signal( Signal const signal ) noexcept -> bool
{
  auto const is_invalid = !is_valid_signal( signal );
  return is_invalid;
}


} // namespace judsonTeledyneInSb
} // namespace detector
} // namespace equipment
} // namespace thermal
