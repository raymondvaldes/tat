//
//  spot_view.h
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_equipment_detector_spot_view__
#define __tat_thermal_equipment_detector_spot_view__

#include <utility>

#include "units.h"
#include "math/complex/properties.h"

namespace thermal{
namespace equipment{
namespace detector{

/* The spot-view function takes the weighted-average value of a function.  The
    weighted function is derived from the monochromatic emissive power.
*/
auto spot_view_2
(
  std::function< math::complex::properties< units::si::temperature > ( double ) > const phase_amplitude_field,
  units::quantity< units::si::temperature > const reference_temperature,
  units::quantity< units::si::wavelength> const detector_wavelength,
  units::quantity< units::si::dimensionless> const R
)
noexcept -> math::complex::properties< units::si::temperature >;

} // namespace detector
} // namespace equipment
} // namespace thermal
#endif /* defined(__tat__spot_view__) */
