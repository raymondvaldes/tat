/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include <cassert>
#include <cmath>
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
  assert( rhoCp.value() > 0  && isnormal(rhoCp) );
  assert( alpha.value() > 0 && isnormal(alpha) );

  // alpha = k / rhoCp
  // k = alpha * rhoCp

  auto const k = alpha * rhoCp ;
  
  assert( k.value() > 0 && isnormal( k ) );
  return k;
}

auto conductivity
(
  units::quantity< units::si::volumetric_heat_capacity > const rhoCp,
  units::quantity< units::si::thermal_effusivity> const e
)
noexcept -> units::quantity< units::si::thermal_conductivity >
{
  assert( rhoCp.value() > 0 && isnormal( rhoCp ) );
  assert( e.value() > 0 && isnormal( e ) ) ;
  // e = sqrt( k * rhoCp )
  // e^2 = k * rhoCp
  // k = e^2 / rhoCp

  auto const k = pow<2>( e ) / rhoCp ;

  assert( k.value() > 0 && isnormal( k ) );
  return k;
}
  
auto conductivity
(
  units::quantity< units::si::thermal_effusivity > const e,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> units::quantity< units::si::thermal_conductivity >
{
  // alpha = k / rhoCp
  // e = sqrt( k * rhoCp )
  // e = sqrt( k * (k / alpha) )
  // e = sqrt( k^2 / alpha )
  // e^2 = k^2 / alpha
  // k^2 = e^2 * alpha
  // k = sqrt( e^2 * alpha )
  // k = e * sqrt( alpha )
  
  assert( e.value() > 0 && isnormal( e )   );
  assert( alpha.value() > 0 && isnormal( alpha ) );

  auto const k = e * sqrt( alpha );
  
  assert( k.value() > 0 && isnormal( k ) );
  return k;

}
  
} // namespace define
} // namespace
