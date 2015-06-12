//
//  signalRatio.h
//  tat
//
//  Created by Raymond Valdes on 1/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__signalRatio_134234314345_
#define __tat__signalRatio_134234314345_

#include "units.h"

namespace thermal{

namespace pyrometer{

namespace twoColor{

auto signalRatio(
  units::quantity<units::si::electric_potential> const & first,
  units::quantity<units::si::electric_potential> const & second
) noexcept -> units::quantity< units::si::dimensionless >;
  
}
  
}

}

#endif /* defined(__tat__signalRatio__) */
