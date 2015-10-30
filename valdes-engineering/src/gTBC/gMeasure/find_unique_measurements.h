//
//  find_unique_measurements.h
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__find_unique_measurements__
#define __tat__find_unique_measurements__

#include <vector>

#include "gTBC/gMeasure/scopeFile.h"
#include "gTBC/gMeasure/Unique_scope_measurement.h"

namespace gTBC {

namespace gMeasure {

auto find_unique_measurements
(
  std::vector< ScopeFile > const & scope_files
)
noexcept -> std::vector< Unique_scope_measurement >;

} // namespace gMeasure
  
} // namespace gTBC

#endif /* defined(__tat__find_unique_measurements__) */
