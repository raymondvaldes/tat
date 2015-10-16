//
//  normalizedSignalRatio.cpp
//  tat
//
//  Created by Raymond Valdes on 1/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/pyrometry/twoColor/normalizedSignalRatio.h"
#include "units/si/constants/thermal.h"  

using units::si::constants::C2_wien;

namespace thermal{

namespace pyrometer{

namespace twoColor{

auto normalizedSignalRatio(
  units::quantity<units::si::dimensionless> const & SignalRatio,
  units::quantity<units::si::wavelength> const & first,
  units::quantity<units::si::wavelength> const & second
  )
noexcept -> units::quantity< units::si::one_over_temperature >
{
  assert( SignalRatio > 0 );
  assert( first.value() > 0 );
  assert( second.value() > 0 );
  assert( first < second ) ;
  
  auto const
  result =
    ( log( SignalRatio ) - 5 * log( first / second ) )
    / ( C2_wien / first - C2_wien / second ) ;

  return result;
}
  
}
  
}

}
