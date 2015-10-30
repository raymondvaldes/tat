//
//  calibrate_wavelength.cpp
//  tat
//
//  Created by Raymond Valdes on 5/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/pyrometry/twoColor/calibrate_wavelength.h"

namespace thermal{
namespace pyrometry{
namespace twoColor{

auto
calibrate_wavelength( units::quantity<units::si::wavelength> const & raw,
                      units::quantity<units::si::wavelength> const & offset )
noexcept-> units::quantity<units::si::wavelength>
{
  return raw + offset;
}

} // namespace twoColor
} // namespace pyrometry
} // namespace thermal
