//
//  transient_analysis_sweep.h
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__transient_analysis_sweep_2346244572434562_
#define __tat__transient_analysis_sweep_2346244572434562_

#include <vector>
#include <utility>

#include "thermal/pyrometry/twoColor/periodic/transient_analysis.h"
#include "thermal/equipment/detector/measurements.h"
#include "gTBC/gMeasure/import_twoColor_scope_files.h"
#include "thermal/pyrometry/twoColor/periodic/transient_analysis_sweep_results.h"
#include "units.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

auto transient_analysis_sweep
(
  std::vector<
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > > laser_modulations,
 
  std::vector< std::pair<
    thermal::equipment::detector::Measurements,
    thermal::equipment::detector::Measurements > > const & sweep,
 
  units::quantity< units::si::dimensionless > const & gCoeff
)
noexcept -> transient_analysis_sweep_results;

auto transient_analysis_sweep
(
  gTBC::gMeasure::processed_scope_data const & gCoeff
)
noexcept -> transient_analysis_sweep_results;

} // namespace periodic  
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal

#endif /* defined(__tat__transient_analysis_sweep__) */
