//
//  planks_law.h
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_emission_planks_law__
#define __tat_thermal_emission_planks_law__

#include "units.h"

namespace thermal {
namespace emission {
namespace monochromatic_blackbody_emissive_power {

auto planks_law
(
  units::quantity< units::si::temperature > const absolute_temperature,
  units::quantity< units::si::wavelength > const emissive_wavelength
)
noexcept -> units::quantity< units::si::heat_flux_over_length >;


} // namespace monochromatic_blackbody_emissive_power
} // namespace emission
} // namespace thermal

#endif /* defined(__tat__planks_law__) */
