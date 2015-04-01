//
//  temperature.h
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__temperature__
#define __tat__temperature__

#include "units.h"
#include <complex>
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{

auto temperature
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r, 
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::dimensionless > const l 
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >;

} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined(__tat__temperature__) */
