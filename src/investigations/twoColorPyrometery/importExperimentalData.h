//
//  importExperimentalData.h
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_importExperimentalData_h
#define tat_importExperimentalData_h

#include "tools/interface/filesystem.hpp"

namespace investigations {

namespace twoColorPyrometery {

auto importExperimentalData( filesystem::directory const & dir ) -> void;

  
} // namespace twoColorPyrometery
  
} // namespace investigations

#endif
