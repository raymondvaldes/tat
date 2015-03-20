//
//  wave_signals.h
//  tat
//
//  Created by Raymond Valdes_New on 3/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__wave_signals__
#define __tat__wave_signals__

// c++ headers
#include <utility>

// project headers
#include "thermal/equipment/detector/measurements.h"

namespace investigations {

namespace twoColorPyrometery {

namespace plot {

auto wave_signals
(
  std::pair<
  thermal::equipment::detector::Measurements,
  thermal::equipment::detector::Measurements > const & wave_signals
) noexcept -> void;


  
} // namespace plot
  
} // namespace twocolorPyrometery
  
} // namespace investigations

#endif /* defined(__tat__wave_signals__) */
