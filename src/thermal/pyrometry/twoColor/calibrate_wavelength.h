//
//  calibrate_wavelength.h
//  tat
//
//  Created by Raymond Valdes on 5/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_pyrometry_twoColor_calibrate_wavelength__
#define __tat_thermal_pyrometry_twoColor_calibrate_wavelength__

#include "units.h"

namespace thermal{
namespace pyrometry{
namespace twoColor{

auto
calibrate_wavelength( units::quantity<units::si::wavelength> const & raw,
                      units::quantity<units::si::wavelength> const & offset )
noexcept-> units::quantity<units::si::wavelength>;

} // namespace twoColor
} // namespace pyrometry
} // namespace thermal


#endif /* defined(__tat__calibrate_wavelength__) */
