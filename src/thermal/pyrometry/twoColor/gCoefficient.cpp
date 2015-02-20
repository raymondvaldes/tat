//
//  gCoefficient.cpp
//  tat
//
//  Created by Raymond Valdes_New on 2/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "gCoefficient.h"
#include "assertExtensions.h"
#include "math/algorithms/spline-quantity.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {

  gCoefficient::gCoefficient(
    std::vector< units::quantity< units::si::wavelength  > > const & wavelengthsIn,
    std::vector< units::quantity< units::si::electric_potential > > const & detectorSignalsIn,
    units::quantity< units::si::temperature > const & source_temperatureIn
    ) noexcept
  : wavelengths(wavelengthsIn),
    detectorSignals(detectorSignalsIn),
    source_temperature(source_temperatureIn)
  {
    assert_equal( wavelengthsIn.size(), detectorSignalsIn.size() );
  }
  
  auto
  gCoefficient::at( units::quantity< units::si::wavelength > const & first,
                    units::quantity< units::si::wavelength > const & second )
  const noexcept
  -> units::quantity< units::si::dimensionless >
  {
    assert_lt( first, second );
    
    return 0;
  }
  
  auto gCoefficient::sourceTemperature( void ) const noexcept
  -> units::quantity< units::si::temperature>
  {
    return source_temperature;
  }

} // namespace twoColor

} // namespace pyrometry

} // namespace thermal
