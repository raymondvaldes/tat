//
//  calibratedSignalRatio.h
//  tat
//
//  Created by Raymond Valdes on 1/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__calibratedSignalRatio__
#define __tat__calibratedSignalRatio__

#include "units.h"

namespace thermal{

namespace pyrometer{

namespace twoColor{

auto calibratedSignalRatio(
  units::quantity<units::si::dimensionless> signalRatio,
  units::quantity<units::si::dimensionless> gCoeff
  ) noexcept -> units::quantity<units::si::dimensionless> ;

}

}

}

#endif /* defined(__tat__calibratedSignalRatio__) */
