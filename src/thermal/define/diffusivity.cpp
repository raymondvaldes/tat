/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "thermal/define/diffusivity.h"
#include <cassert>

namespace thermal{

namespace define{

double diffusivity( const double k, const double rhoCp ) noexcept
{
  return k / rhoCp ;
}

auto diffusivity
(
  units::quantity< units::si::thermal_conductivity> const k,
  units::quantity< units::si::volumetric_heat_capacity > const rhoCp
)
noexcept -> units::quantity< units::si::thermal_diffusivity >
{
  assert( k.value() > 0 );
  assert( rhoCp.value() > 0 );
  
  auto const alpha = k / rhoCp;
  return alpha;
}

    
} // namesapce define

} // namespace thermal
