//
//  h.h
//  tat
//
//  Created by Raymond Valdes on 4/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_oneLayer2D_complex_h__
#define __tat_thermal_model_oneLayer2D_complex_h__

#include "units.h"
#include <complex>

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

auto h
(
  units::quantity< units::si::dimensionless, double > const nu,
  units::quantity< units::si::dimensionless, double > const z,
  units::quantity< units::si::dimensionless, double > const l,
  units::quantity< units::si::dimensionless, double > const b
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >;

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* defined(__tat__h__) */
