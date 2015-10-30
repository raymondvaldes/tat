//
//  hat.cpp
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "hat.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{
namespace nu{

using namespace std::literals;
using namespace units;
using std::complex;

auto hat
(
  units::quantity< units::si::dimensionless > const nu,
  units::quantity< units::si::dimensionless > const a_sub,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::dimensionless > const b
) noexcept -> units::quantity< units::si::dimensionless , std::complex<double>>
{
  auto const i_non = quantity<dimensionless, complex<double > >( 0. + 1i );

  return sqrt( i_non + pow<2>( nu * a_sub * l / b ) )  ;
}

} // namespace nu
} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal
