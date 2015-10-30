//
//  kappa.h
//  tat
//
//  Created by Raymond Valdes on 4/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2d_complex_kappa__
#define __tat_thermal_model_oneLayer2d_complex_kappa__

#include "units.h"
#include <complex>

#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/b.h"
#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/thermal_penetration.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

auto kappa
(
  units::quantity< units::si::dimensionless > const nu,
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >;

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__kappa__) */
