//
//  signalRatio.h
//  tat
//
//  Created by Raymond Valdes on 1/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__signalRatio__
#define __tat__signalRatio__

#include "units/units.h"

namespace thermal{

namespace pyrometer{

namespace twoColor{

auto signalRatio(
  units::quantity<units::si::electric_potential> signal1,
  units::quantity<units::si::electric_potential> signal2
) noexcept -> units::quantity< units::si::dimensionless >;
  
}
  
}

}

#endif /* defined(__tat__signalRatio__) */
