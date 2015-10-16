//
//  is_valid_frequency.h
//  tat
//
//  Created by Raymond Valdes on 10/14/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef is_valid_frequency_h_101415
#define is_valid_frequency_h_101415

#include "units.h"
#include <cmath>

namespace thermal{
namespace equipment{
namespace laser{

auto is_valid_frequency( double const freq ) noexcept -> bool
{
  using std::isnormal;
  using std::isgreater;

  auto const is_normal = isnormal( freq );
  auto const is_positive =freq > 0;

  return is_normal && is_positive;

}

auto is_valid_frequency( units::quantity< units::si::frequency > const  freq )
noexcept -> bool
{
  using units::isnormal;
  using units::isgreater;

  auto const f_value = freq.value();
  return is_valid_frequency( f_value );

}




} // namespace laser
} // namespace equipment
} // namespace thermal

#endif /* is_valid_frequency_h */
