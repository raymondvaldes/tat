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
    const std::vector< units::quantity< units::si::wavelength  > >& wavelengthsIn,
    const std::vector< units::quantity< units::si::electric_potential > > &detectorSignalsIn,
    const units::quantity< units::si::temperature > &source_temperatureIn
    ) noexcept
  : wavelengths(wavelengthsIn), detectorSignals(detectorSignalsIn),
    source_temperature(source_temperatureIn)
  {
    assert_equal( wavelengthsIn.size(), detectorSignalsIn.size() );
    assert_gt_zero( source_temperature.value() ) ;
    
    
    
  }
  
  auto
  gCoefficient::at( units::quantity< units::si::wavelength > first,
      units::quantity< units::si::wavelength > second )
  noexcept
  -> units::quantity< units::si::dimensionless >
  {
    return 0;
  }
  
  auto
  gCoefficient::sourceTemperature( void )
  noexcept
  -> units::quantity< units::si::temperature>
  {
    return source_temperature;
  }

} // namespace twoColor

} // namespace pyrometry

} // namespace thermal
