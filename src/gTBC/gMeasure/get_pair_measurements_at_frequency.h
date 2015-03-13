//
//  get_pair_measurements_at_frequency.h
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__get_pair_measurements_at_frequency__
#define __tat__get_pair_measurements_at_frequency__

#include <utility>
#include "units.h"
#include "gTBC/gMeasure/Unique_scope_measurement.h"


namespace gTBC {
  
namespace gMeasure {

auto get_pair_measurements_at_frequency
(
  std::vector< Unique_scope_measurement > const & unique_measurements,
  units::quantity<units::si::frequency> const & frequency
)
noexcept -> std::pair<  Unique_scope_measurement, Unique_scope_measurement > ;


  
} // gMeasure
  
} // gTBC

#endif /* defined(__tat__get_pair_measurements_at_frequency__) */
