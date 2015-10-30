//
//  F_tilde.h
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_complexT_F_tilde__
#define __tat_thermal_model_tbc2009_complexT_F_tilde__

#include "units.h"
#include <complex>

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{

auto F_tilde
(
  units::quantity< units::si::dimensionless, std::complex<double> > const nu_tilde,
  units::quantity< units::si::dimensionless, std::complex<double>  > const nu_hat,
  units::quantity< units::si::dimensionless > const gamma,
  units::quantity< units::si::dimensionless > const thermal_penetration
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >;

} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined() */
