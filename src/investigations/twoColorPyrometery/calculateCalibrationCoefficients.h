//
//  calculateCalibrationCoefficients.h
//  tat
//
//  Created by Raymond Valdes_New on 2/17/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__calculateCalibrationCoefficients__
#define __tat__calculateCalibrationCoefficients__

#include "units.h"
#include "tools/interface/filesystem.hpp"

namespace investigations {

namespace twoColorPyrometery {

auto calculateCalibrationCoefficients( filesystem::directory const & dir )
-> units::quantity< units::si::dimensionless > ;
  
} // namespace twoColorPyrometery
  
} // namespace investigations

#endif /* defined(__tat__calculateCalibrationCoefficients__) */
