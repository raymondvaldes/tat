//
//  calibrate_wavelengths.cpp
//  tat
//
//  Created by Raymond Valdes on 5/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/pyrometry/twoColor/calibrate_wavelengths.h"
#include <algorithm>

#include "thermal/pyrometry/twoColor/calibrate_wavelength.h"

using std::generate;
using std::begin;
using std::end;

namespace thermal{
namespace pyrometry{
namespace twoColor{

auto
calibrate_wavelengths(
  std::vector< units::quantity< units::si::wavelength > > const & raw,
  units::quantity<units::si::wavelength> const & offset )
noexcept-> std::vector< units::quantity< units::si::wavelength > >
{
  auto wavelengths = raw;
  
  transform( begin( wavelengths ), end( wavelengths ), begin( wavelengths ),
  [&]( auto const & wavelength )
  {
    return calibrate_wavelength( wavelength, offset );
  } );

  return wavelengths;
}

} // namespace twoColor
} // namespace pyrometry
} // namespace thermal
