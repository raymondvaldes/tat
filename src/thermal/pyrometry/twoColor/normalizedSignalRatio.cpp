//
//  normalizedSignalRatio.cpp
//  tat
//
//  Created by Raymond Valdes on 1/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/pyrometry/twoColor/normalizedSignalRatio.h"

using std::log;
using units::si::constants::C2_wien;

namespace thermal{

namespace pyrometer{

namespace twoColor{

auto normalizedSignalRatio(
  units::quantity<units::si::dimensionless> SignalRatio,
  units::quantity<units::si::length> wavelength1,
  units::quantity<units::si::length> wavelength2
  ) noexcept -> units::quantity< units::si::one_over_temperature >
{
  assert( SignalRatio.value() > 0 );
  assert( wavelength1.value() > 0 );
  assert( wavelength2.value() > 0 );

  const auto
  result =
    ( log( SignalRatio ) - 5 * log( wavelength2 / wavelength1 ) )
    / ( C2_wien / wavelength2 - C2_wien / wavelength1 ) ;

  return result;
}
  
}
  
}

}
