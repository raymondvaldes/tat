//
//  remove_grnd_if_not_in_scope_files.h
//  tat
//
//  Created by Raymond Valdes on 3/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__remove_grnd_if_not_in_scope_files__
#define __tat__remove_grnd_if_not_in_scope_files__

#include <vector>
#include "gTBC/gMeasure/import_sweep_meta_data.h"
#include "units.h"

namespace gTBC {

namespace gMeasure {

auto remove_grnd_if_not_in_scope_files
(
  std::vector < frequency_detector_ground > const signal_grnds_,
  std::vector< units::quantity< units::si::frequency > > frequencies
)
noexcept -> std::vector < frequency_detector_ground >;
  
} // namespace gMeasure
  
} // namespace gTBC

#endif /* defined(__tat__remove_grnd_if_not_in_scope_files__) */
