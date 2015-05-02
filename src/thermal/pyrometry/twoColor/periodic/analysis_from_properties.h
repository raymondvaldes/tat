//
//  analyis_from_properties.h
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_pyrometry_twoColor_periodic_analyis_from_properties__
#define __tat_thermal_pyrometry_twoColor_periodic_analyis_from_properties__

#include "thermal/pyrometry/twoColor/periodic/results.h"
#include "units.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

auto analysis_from_properties
(
  math::functions::PeriodicProperties< units::si::electric_potential > const & properties_1,
  units::quantity<units::si::wavelength> const detector_wavelength_1,
  math::functions::PeriodicProperties< units::si::electric_potential > const & properties_2,
  units::quantity<units::si::wavelength> const detector_wavelength_2,
  units::quantity< units::si::dimensionless > const & gCoeff,
  units::quantity< units::si::frequency > const & laser_frequency
)
noexcept -> transient_analysis_results;

} // namespace periodic  
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal

#endif /* defined(__tat__analyis_from_properties__) */
