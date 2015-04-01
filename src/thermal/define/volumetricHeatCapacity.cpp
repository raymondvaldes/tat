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
  assert( alpha.value() > 0 );
  assert( k.value() > 0 );
  // alpha = k / rhoCp

  auto const rhoCp = k / alpha ;
  return rhoCp;
}

auto volumetricHeatCapacity
(
  units::quantity< units::si::thermal_effusivity > const e,
  units::quantity< units::si::thermal_conductivity> const k
)
noexcept -> units::quantity< units::si::volumetric_heat_capacity >
{
  assert( e.value() > 0 );
  assert( k.value() > 0 );
  // e = sqrt( k * rhoCp )
  
  auto const rhoCp = pow<2>( e ) / k;
  return rhoCp;
}

  
} // namespace define
} // namespace
