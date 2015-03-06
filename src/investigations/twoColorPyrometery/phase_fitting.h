//
//  phase_fitting.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__phase_fitting__
#define __tat__phase_fitting__

#include "tools/interface/filesystem.hpp"

namespace investigations {

namespace twoColorPyrometery {

auto phase_fitting( filesystem::directory const & dir ) -> void ;
  
} // namespace twoColorPyrometery
  
} // namespace investigations

#endif /* defined(__tat__phase_fitting__) */
