//
//  tilde.h
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_complexT_nu_tilde__
#define __tat_thermal_model_tbc2009_complexT_nu_tilde__

#include <complex>
#include "units.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{
namespace nu{

auto tilde
(
  units::quantity< units::si::dimensionless > const nu,
  units::quantity< units::si::dimensionless > const c_coat,
  units::quantity< units::si::dimensionless > const thermal_penetration,
  units::quantity< units::si::dimensionless > const beam_radius
) noexcept -> units::quantity< units::si::dimensionless , std::complex<double>>;

} // namespace nu
} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined(__tat__tilde__) */
