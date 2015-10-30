/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat_thermal_define_conductivity__
#define __tat_thermal_define_conductivity__

#include "units.h"

namespace thermal{

namespace define {

auto conductivity
(
  units::quantity< units::si::volumetric_heat_capacity > const rhoCp,
  units::quantity< units::si::thermal_diffusivity> const alpha
)
noexcept -> units::quantity< units::si::thermal_conductivity >;

auto conductivity
(
  units::quantity< units::si::volumetric_heat_capacity > const rhoCp,
  units::quantity< units::si::thermal_effusivity> const e
)
noexcept -> units::quantity< units::si::thermal_conductivity >;

auto conductivity
(
  units::quantity< units::si::thermal_effusivity > const e,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> units::quantity< units::si::thermal_conductivity >;


} // namespace define
  
} // namespace
#endif /* defined(__tat__conductivity__) */
