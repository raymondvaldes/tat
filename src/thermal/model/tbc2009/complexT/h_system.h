//
//  h_system.h
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_complex_h_system__
#define __tat_thermal_model_tbc2009_complex_h_system__

#include "units.h"
#include <functional>
#include <complex>
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{

auto h_system
(
  units::quantity< units::si::dimensionless, double > const z,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::dimensionless > const l 
) noexcept -> std::function<
  units::quantity< units::si::dimensionless, std::complex<double> >
  ( units::quantity< units::si::dimensionless, double > const,
    units::quantity< units::si::dimensionless, double > const)>;

} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined(__tat__h_system__) */
