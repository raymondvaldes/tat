//
//  temperature.cpp
//  tat
//
//  Created by Raymond Valdes on 4/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/complex/temperature.h"
#include "math/transform/inverseHankel.h"
#include "thermal/model/oneLayer2D/complex/h.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex {

using math::transform::inverseHankel_complex;
using math::transform::iHankelSettings;

auto temperature
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r,
  units::quantity< units::si::dimensionless > const b,
  units::quantity< units::si::dimensionless > const l
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  auto const
  h_system = [ b, l ]( auto const nu_ , auto const z_ ) noexcept {
      return h( nu_, z_, b, l );
  };

  auto const T = inverseHankel_complex( h_system , z, r ) ;
  
  return T;

}

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
