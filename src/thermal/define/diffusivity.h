/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__diffusivity__
#define __tat__diffusivity__

#include "units.h"

namespace thermal{

namespace define{

double diffusivity( const double k, const double rhoCp ) noexcept ;

auto diffusivity
(
  units::quantity< units::si::thermal_conductivity> const k,
  units::quantity< units::si::volumetric_heat_capacity > const rhoCp
)
noexcept -> units::quantity< units::si::thermal_diffusivity >;


} // namesapce define

} // namespace thermal

#endif /* defined(__tat__diffusivity__) */
