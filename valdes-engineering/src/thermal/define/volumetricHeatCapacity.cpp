/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include <cassert>
#include "thermal/define/volumetricHeatCapacity.h"

namespace thermal{
namespace define {

using namespace units;

auto volumetricHeatCapacity
(
  units::quantity< units::si::thermal_diffusivity > const alpha,
  units::quantity< units::si::thermal_conductivity> const k
)
noexcept -> units::quantity< units::si::volumetric_heat_capacity >
{
  assert( alpha.value() > 0 && isfinite(alpha) );
  assert( k.value() > 0  && isfinite(k));
  // alpha = k / rhoCp
  // rhoCp = k / alpha

  auto const rhoCp = k / alpha ;
  
  assert( rhoCp.value() && isfinite(rhoCp) );
  return rhoCp;
}

auto volumetricHeatCapacity
(
  units::quantity< units::si::thermal_effusivity > const e,
  units::quantity< units::si::thermal_conductivity> const k
)
noexcept -> units::quantity< units::si::volumetric_heat_capacity >
{
  assert( e.value() > 0 && isfinite(e) );
  assert( k.value() > 0 && isfinite(k) );
  // e = sqrt( k * rhoCp )
  // e^2 = k * rhoCp
  // rhoCp = e^2 / k
  
  auto const rhoCp = pow<2>( e ) / k;
  
  assert( rhoCp.value() && isfinite(rhoCp) );
  return rhoCp;
}

} // namespace define
} // namespace
