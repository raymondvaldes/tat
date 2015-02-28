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
  units::quantity<units::si::electric_potential> const & first,
  units::quantity<units::si::electric_potential> const & second
) noexcept -> units::quantity< units::si::dimensionless >
{
  assert( first.value() > 0 ) ;
  assert( second.value() > 0 ) ;
  
  return second / first ;
}

  
}
  
}

}
