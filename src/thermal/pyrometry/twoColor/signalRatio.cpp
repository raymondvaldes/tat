//
//  signalRatio.cpp
//  tat
//
//  Created by Raymond Valdes on 1/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <cassert>
#include "signalRatio.h"

#include "units.h"

namespace thermal{

namespace pyrometer{

namespace twoColor{

auto signalRatio(
  units::quantity<units::si::electric_potential> signal1,
  units::quantity<units::si::electric_potential> signal2
) noexcept -> units::quantity< units::si::dimensionless >
{
  assert( signal1.value() > 0 );
  assert( signal2.value() > 0 );
  
  return signal1 / signal2 ;
}

  
}
  
}

}
