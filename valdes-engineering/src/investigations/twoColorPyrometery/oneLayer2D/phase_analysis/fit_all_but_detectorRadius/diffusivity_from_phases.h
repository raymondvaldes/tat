//
//  diffusivity_from_phases.h
//  tat
//
//  Created by Raymond Valdes on 5/7/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__diffusivity_from_phases_1312_
#define __tat__diffusivity_from_phases_1312_

#include "tools/interface/filesystem.hpp"

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace phase_analysis{
namespace fit_all_but_detectorRadius{

auto diffusivity_from_phases( filesystem::directory const & dir ) -> void ;

} // namespace
} // namespace
} // namespace
} // namespace
} // namespace

#endif /* defined(__tat__diffusivity_from_phases__) */
