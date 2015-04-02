//
//  temperature.cpp
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "temperature.h"
#include "math/transform/inverseHankel.h"
#include "thermal/model/tbc2009/complexT/h_system.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{

using math::transform::inverseHankel;
using math::transform::iHankelSettings;

auto temperature
(
  units::quantity< units::si::dimensionless, double > const z,
  units::quantity< units::si::dimensionless, double > const r,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::dimensionless > const l 
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  assert( z.value() >= 0 );
  assert( r.value() >= 0 );
  
  auto const h = h_system( z, hp, tp, l );
  auto const T = inverseHankel( h , z, r ) ;
  
  return T;
}

} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal


