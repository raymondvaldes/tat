//
//  extension.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_extension_h
#define tat_extension_h

#include <boost/units/systems/si/energy.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/base.hpp>

#include "units/physical_dimensions.h"
#include "units/si/si.h"
#include "units/unit.h"

namespace units {
namespace si {

using boost::units::unit;
typedef boost::units::si::system siSystem;





typedef unit< thermal_emission_dimension , siSystem > thermal_emission ;
BOOST_UNITS_STATIC_CONSTANT( spectral_power_per_area , thermal_emission ) ;




  

}}

#endif
