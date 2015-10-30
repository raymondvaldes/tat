//
//  extension.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_extension_h
#define tat_extension_h

#include <boost/units/operators.hpp>
#include <boost/units/systems/si/energy.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/systems/si.hpp>

#include "units/scale.h"
#include "units/systems/si/base.h"
#include "units/operators.h"
#include "units/physical_dimensions.h"
#include "units/si/si.h"
#include "units/si/predefined.h"

namespace units {

inline namespace si {

typedef multiply_typeof_helper< power , area >::type power_area;

typedef divide_typeof_helper< power , area >::type power_over_area;

typedef divide_typeof_helper<power,solid_angle>::type power_over_solid_angle;

typedef multiply_typeof_helper<power_over_solid_angle, temperature> thermal_emission;


typedef divide_typeof_helper< length , time >::type length_over_time;

typedef divide_typeof_helper< length, temperature >::type length_over_temperature;

typedef multiply_typeof_helper< length, temperature>::type length_temperature;

typedef divide_typeof_helper< dimensionless, temperature>::type one_over_temperature;

typedef divide_typeof_helper< pressure, time >::type pressure_over_time;

typedef divide_typeof_helper< power_over_area, length >::type heat_flux_over_length;

///custom dimensions
typedef divide_typeof_helper< length , dimensionless >::type wavelength;



typedef
multiply_typeof_helper< thermal_conductivity,
                        volumetric_heat_capacity>::type thermal_effusivity_pow2;


typedef root_typeof_helper<
  thermal_effusivity_pow2,
  static_rational<2> >::type thermal_effusivity;



} // namespace si

} // namespace units

#endif
