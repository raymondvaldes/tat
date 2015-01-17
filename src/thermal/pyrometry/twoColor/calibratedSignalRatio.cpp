//
//  calibratedSignalRatio.cpp
//  tat
//
//  Created by Raymond Valdes on 1/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/pyrometry/twoColor/calibratedSignalRatio.h"

namespace thermal{

namespace pyrometer{

namespace twoColor{

auto calibratedSignalRatio(
  units::quantity<units::si::dimensionless> signalRatio, 
  units::quantity<units::si::dimensionless> gCoeff
  ) noexcept -> units::quantity<units::si::dimensionless>
{
  assert( signalRatio.value() > 0 );
  assert( gCoeff.value() > 0 );
  
  return gCoeff * signalRatio;
}



}

}

}
