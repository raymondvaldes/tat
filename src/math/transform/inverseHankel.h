//
//  inverseHankel.h
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__inverseHankel__
#define __tat__inverseHankel__

#include <boost/math/special_functions/hankel.hpp>
#include <cmath>
#include <cstddef>
#include "units.h"

namespace math {

namespace transform {

struct iHankelSettings{
  
  units::quantity< units::si::dimensionless > nu_end;
  
explicit iHankelSettings
(
  units::quantity< units::si::dimensionless, double > const nu_end = 50.
) noexcept;

};

auto
inverseHankel
(
  std::function<
  units::quantity< units::si::dimensionless, std::complex<double> >
  ( units::quantity< units::si::dimensionless > const,
    units::quantity< units::si::dimensionless > const)> const & h,
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r,
  iHankelSettings const & settings = iHankelSettings{ /* default! */}
)
noexcept -> units::quantity< units::si::dimensionless, std::complex<double>>;

auto
inverseHankel_complex
(
  std::function<
  units::quantity< units::si::dimensionless, std::complex<double> >
  ( units::quantity< units::si::dimensionless > const,
    units::quantity< units::si::dimensionless > const)> const & h,
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r,
  iHankelSettings const & settings = iHankelSettings{ /* default! */}
)
noexcept -> units::quantity< units::si::dimensionless, std::complex<double>>;

} // namespace transform
  
} // namespace math

#endif /* defined(__tat__inverseHankel__) */
