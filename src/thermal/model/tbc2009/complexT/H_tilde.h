//
//  H_tilde.h
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_complexT_H_tilde__
#define __tat_thermal_model_tbc2009_complexT_H_tilde__

#include "units.h"
#include <complex>
#include "thermal/model/tbc2009/dimensionless/HeatingProperties.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{

auto H_tilde
(
  units::quantity< units::si::dimensionless > const nu,
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless, std::complex<double> > const F,
  units::quantity< units::si::dimensionless, std::complex<double> > const nu_hat,
  units::quantity< units::si::dimensionless, std::complex<double> > const nu_tilde,
 
  dimensionless::HeatingProperties const hp,
  units::quantity< units::si::dimensionless > const gamma,
  units::quantity< units::si::dimensionless > const l 
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >;

} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined() */
