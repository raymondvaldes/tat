//
//  is_valid.cpp
//  tat
//
//  Created by Raymond Valdes on 10/5/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "coefficient_is_valid.hpp"
#include <cmath>

namespace thermal {
namespace pyrometry{
namespace twoColor{
namespace calibration{

using std::isnormal;
using units::isnormal;

auto coefficient_is_valid( Coefficient const g ) noexcept -> bool
{
  auto const is_normal_value = isnormal( g );
  auto const is_in_range = g > 0;

  auto const is_valid = is_normal_value && is_in_range;
  
  return is_valid;
}

} // namespace calibration_coefficient
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal

