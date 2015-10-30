//
//  periodic_cosine.h
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_equipment_detector_simulate_measurements_periodic_cosine__
#define __tat_thermal_equipment_detector_simulate_measurements_periodic_cosine__

#include "thermal/equipment/detector/measurements.h"
#include "math/functions/cosine.h"
#include "units.h"

namespace thermal {
namespace equipment {
namespace detector{
namespace simulate_measurements{

auto periodic_cosine(
  math::functions::PeriodicProperties< units::si::electric_potential > const & properties,
  units::quantity< units::si::wavelength > const detector_wavelength,
  size_t points
) noexcept -> Measurements;
  
} // namespace  simulate_measurements
} // namespace  detector
} // namespace  equipment
} // namespace  thermal

#endif /* defined(__tat__periodic_cosine__) */
