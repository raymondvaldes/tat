//
//  tempeature_nd.h
//  tat
//
//  Created by Raymond Valdes on 5/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_324234_tempeature_nd__
#define __tat_324234_tempeature_nd__

#include "units.h"
#include <complex>
#include "math/transform/inverseHankel.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{
namespace reverseIntegration{

auto temperature_nd
(
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::dimensionless > const r_e ,
  math::transform::iHankelSettings const & settings = math::transform::iHankelSettings{ /* default! */}
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >;



}}}}}

#endif /* defined(__tat__tempeature_nd__) */
