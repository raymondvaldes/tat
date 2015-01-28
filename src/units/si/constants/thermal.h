//
//  thermal.h
//  tat
//
//  Created by Raymond Valdes on 10/3/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_thermal_h
#define tat_thermal_h

#include <boost/units/systems/detail/constants.hpp>
#include "units/si/predefined.h"
#include "units/si/extension.h"
#include "units/si/prefixes.h"
#include "units/quantity.h"

namespace units {
namespace si {
namespace constants {

BOOST_UNITS_PHYSICAL_CONSTANT(  C1_wien ,
                                quantity<power_over_area>,
                                3.7418 * 10e8 * watts/  meter  /  meter ,
                                0.0 * watts / meter / meter ) ;
  
BOOST_UNITS_PHYSICAL_CONSTANT(  C2_wien ,
                                quantity<length_temperature>,
                                0.01439 *  meters  * kelvin,
                                0.0 * meters * kelvin ) ;

BOOST_UNITS_PHYSICAL_CONSTANT(  PI_radians ,
                                quantity<plane_angle>,
                                M_PI *  radians,
                                0.0 * radians ) ;

}}}


#endif
