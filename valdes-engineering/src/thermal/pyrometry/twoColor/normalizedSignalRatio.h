//
//  normalizedSignalRatio.h
//  tat
//
//  Created by Raymond Valdes on 1/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_normalizedSignalRatio_h
#define tat_normalizedSignalRatio_h

#include "units.h"

namespace thermal{

namespace pyrometer{

namespace twoColor{

auto normalizedSignalRatio(
  units::quantity<units::si::dimensionless> const & SignalRatio,
  units::quantity<units::si::wavelength> const & first,
  units::quantity<units::si::wavelength> const & second
  ) noexcept -> units::quantity< units::si::one_over_temperature >;
  
}
  
}

}


#endif
