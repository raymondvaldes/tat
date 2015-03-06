//
//  temperature_prediction.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__temperature_prediction__
#define __tat__temperature_prediction__

#include "tools/interface/filesystem.hpp"

namespace investigations {

namespace twoColorPyrometery {

auto temperature_prediction( filesystem::directory const & dir ) -> void ;
  
} // namespace twoColorPyrometery
  
} // namespace investigations

#endif /* defined(__tat__temperature_prediction__) */
