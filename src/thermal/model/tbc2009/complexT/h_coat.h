//
//  h_coat.h
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_complexT_h_coat__
#define __tat_thermal_model_tbc2009_complexT_h_coat__

#include "units.h"
#include <complex>
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{

auto h_coat
(
  units::quantity< units::si::dimensionless > const nu,
  units::quantity< units::si::dimensionless > const z,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >;

} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined(__tat__h_coat__) */
