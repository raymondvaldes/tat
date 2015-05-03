//
//  analysis_from_properties_sweep.h
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_pyrometery_twoColor_periodic_analysis_from_properties_sweep__
#define __tat_thermal_pyrometery_twoColor_periodic_analysis_from_properties_sweep__

#include <vector>
#include "thermal/pyrometry/twoColor/periodic/transient_analysis_sweep_results.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

auto analysis_from_properties_sweep
(
  std::vector<
  math::functions::PeriodicProperties< units::si::electric_potential >> const & properties_1,
  units::quantity<units::si::wavelength> const detector_wavelength_1,
  std::vector<
  math::functions::PeriodicProperties< units::si::electric_potential >> const & properties_2,
  units::quantity<units::si::wavelength> const detector_wavelength_2,
  units::quantity< units::si::dimensionless > const & gCoeff,
  std::vector< units::quantity< units::si::frequency > > const & laser_frequency
)
noexcept -> transient_analysis_sweep_results;

} // namespace periodic  
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal

#endif /* defined(__tat__analysis_from_properties_sweep__) */
