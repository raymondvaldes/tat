/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include <cassert>
#include "thermal/define/conductivity.h"

namespace thermal{
namespace define {

using namespace units;

auto conductivity
(
  units::quantity< units::si::volumetric_heat_capacity > const rhoCp,
  units::quantity< units::si::thermal_diffusivity> const alpha
)
noexcept -> units::quantity< units::si::thermal_conductivity >
{
  assert( rhoCp.value() > 0 );
  assert( alpha.value() > 0 );

  // alpha = k / rhoCp

  auto const k = alpha * rhoCp ;
  return k;
}

auto conductivity
(
  units::quantity< units::si::volumetric_heat_capacity > const rhoCp,
  units::quantity< units::si::thermal_effusivity> const e
)
noexcept -> units::quantity< units::si::thermal_conductivity >
{
  assert( rhoCp.value() > 0 );
  assert( e.value() > 0 );
  // e = sqrt( k * rhoCp )

  auto const k = pow<2>( e ) / rhoCp ;
  return k;
}
  
auto conductivity
(
  units::quantity< units::si::thermal_effusivity > const e,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> units::quantity< units::si::thermal_conductivity >
{
  assert( e.value() > 0 );
  assert( alpha.value() > 0 );

  return e * sqrt( alpha );
}
  
} // namespace define
} // namespace
