//
//  gCoefficient.h
//  tat
//
//  Created by Raymond Valdes_New on 2/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__gCoefficient__
#define __tat__gCoefficient__

#include <vector>

#include "units.h"


namespace thermal {

namespace pyrometry {

namespace twoColor {

class gCoefficient{

private:

  std::vector< units::quantity< units::si::wavelength  > > wavelengths;
  std::vector< units::quantity< units::si::electric_potential > > detectorSignals;
  units::quantity< units::si::temperature > source_temperature;

public:

  explicit gCoefficient(
    const std::vector< units::quantity< units::si::wavelength  > >& wavelengthsIn,
    const std::vector< units::quantity< units::si::electric_potential > > &detectorSignalsIn,
    const units::quantity< units::si::temperature > &source_temperatureIn
    ) noexcept;
  
  auto
  at( units::quantity< units::si::wavelength > first,
      units::quantity< units::si::wavelength > second )
  noexcept
  -> units::quantity< units::si::dimensionless >;
  
  
  auto
  sourceTemperature( void )
  noexcept
  -> units::quantity< units::si::temperature>;
  
};

} // namespace twoColor

} // namespace pyrometry

} // namespace thermal

#endif /* defined(__tat__gCoefficient__) */
