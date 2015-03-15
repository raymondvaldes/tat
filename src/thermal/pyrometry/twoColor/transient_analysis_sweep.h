//
//  transient_analysis_sweep.h
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__transient_analysis_sweep__
#define __tat__transient_analysis_sweep__

#include <vector>
#include <utility>

#include "thermal/pyrometry/twoColor/transient_analysis.h"
#include "thermal/equipment/detector/measurements.h"
#include "gTBC/gMeasure/import_twoColor_scope_files.h"
#include "units.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {

struct transient_analysis_sweep_results
{
  std::vector< transient_analysis_results > transient_results;

  transient_analysis_sweep_results(
    std::vector< transient_analysis_results > const & transient_results_
  );
  
  auto phases_omega(void) const -> 
  std::pair<
    std::vector< units::quantity< units::si::angular_frequency>>,
    std::vector< units::quantity< units::si::plane_angle      >> >;
};


auto transient_analysis_sweep
(
  std::vector< units::quantity< units::si::frequency> > const &
  laser_modulation_freq,
 
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

  
} // namespace twoColor
  
} // namespace pyrometry
  
} // namespace thermal

#endif /* defined(__tat__transient_analysis_sweep__) */
