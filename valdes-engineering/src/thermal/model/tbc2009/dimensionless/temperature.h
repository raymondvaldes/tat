//
//  temperature.h
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_dimensionless_temperature__
#define __tat_thermal_model_tbc2009_dimensionless_temperature__

#include <complex>
#include "units.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

auto temperature
(
  units::quantity< units::si::dimensionless, std::complex<double>  > const theta,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::heat_flux > const I_o,
  units::quantity< units::si::dimensionless > const R0,
  units::quantity< units::si::thermal_conductivity > const k_coat
) noexcept -> units::quantity< units::si::temperature, std::complex<double> >;

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined() */
