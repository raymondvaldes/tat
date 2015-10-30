/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef tat_thermal_model_volumetricHeatCapacity_h
#define tat_thermal_model_volumetricHeatCapacity_h

#include "units.h"

namespace thermal{

namespace define {

auto volumetricHeatCapacity
(
  units::quantity< units::si::thermal_diffusivity > const alpha,
  units::quantity< units::si::thermal_conductivity> const k
)
noexcept -> units::quantity< units::si::volumetric_heat_capacity >;

auto volumetricHeatCapacity
(
  units::quantity< units::si::thermal_effusivity > const e,
  units::quantity< units::si::thermal_conductivity> const k
)
noexcept -> units::quantity< units::si::volumetric_heat_capacity >;

} // namespace define
  
} // namespace

#endif
