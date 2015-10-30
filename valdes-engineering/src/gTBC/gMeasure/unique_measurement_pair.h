//
//  unique_measurement_pair.h
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__unique_measurement_pair__
#define __tat__unique_measurement_pair__

#include "gTBC/gMeasure/Unique_scope_measurement.h"
#include "units.h"

namespace gTBC {

namespace gMeasure {

auto unique_measurement_pairs
(
  std::vector< Unique_scope_measurement > const & unique_measurements,
  std::vector< units::quantity< units::si::frequency >>
)
noexcept -> std::vector< std::pair< Unique_scope_measurement,
                                    Unique_scope_measurement > >;
  
  
} // namespace gMeasure

} // namespace gTBC

#endif /* defined(__tat__unique_measurement_pair__) */
