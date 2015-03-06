//
//  2colorPyrometery.cpp
//  tat
//
//  Created by Raymond Valdes on 12/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include <cassert>

#include "investigations/twoColorPyrometery/calculateCalibrationCoefficients.h"
#include "investigations/twoColorPyrometery/temperature_prediction.h"

namespace investigations{

namespace twoColorPyrometery{

auto run( filesystem::directory const & dir ) noexcept -> void
{
  calculateCalibrationCoefficients( dir ) ;
  
  temperature_prediction( dir ) ;
}

} //namespace twoColorPyrometry

} //namespace investigations
