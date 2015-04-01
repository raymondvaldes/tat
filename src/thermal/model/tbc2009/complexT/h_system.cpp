//
//  h_system.cpp
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "h_system.h"

#include "thermal/model/tbc2009/complexT/h_sub.h"
#include "thermal/model/tbc2009/complexT/h_coat.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{


auto h_system
(
  units::quantity< units::si::dimensionless, double > const z,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::dimensionless > const l
) noexcept -> std::function<
  units::quantity< units::si::dimensionless, std::complex<double> >
  ( units::quantity< units::si::dimensionless, double > const,
    units::quantity< units::si::dimensionless, double > const )>
{
  assert( z >= 0 );

  auto h =
  std::function< units::quantity< units::si::dimensionless, std::complex<double> >
  ( units::quantity< units::si::dimensionless, double > const,
    units::quantity< units::si::dimensionless, double > const)>();

  auto const in_coating = z > 0 && z <= 1;
  auto const in_substrate = z > 1 ;
  
  if( in_coating )
  {
    h = [ hp, tp, l ]( auto const nu_ , auto const z_ ) noexcept {
        return h_coat( nu_, z_, hp, tp, l );
    };
  }
  else if( in_substrate )
  {
    h = [ hp, tp, l ]( auto const nu_ , auto const z_ ) noexcept {
      return h_sub( nu_, z_, hp, tp, l );
    };
  }
  
  return h;
}

} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal
