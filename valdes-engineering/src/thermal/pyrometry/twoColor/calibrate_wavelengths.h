//
//  calibrate_wavelengths.h
//  tat
//
//  Created by Raymond Valdes on 5/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_pyrometry_twoColor_calibrate_wavelengths__
#define __tat_thermal_pyrometry_twoColor_calibrate_wavelengths__

#include "units.h"
#include <vector>

namespace thermal{
namespace pyrometry{
namespace twoColor{

auto
calibrate_wavelengths(
  std::vector< units::quantity< units::si::wavelength > > const & raw,
  units::quantity<units::si::wavelength> const & offset )
noexcept-> std::vector< units::quantity< units::si::wavelength > >;

} // namespace twoColor
} // namespace pyrometry
} // namespace thermal

#endif /* defined(__tat__calibrate_wavelengths__) */
