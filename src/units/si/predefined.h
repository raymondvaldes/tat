//
//  length.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__length__
#define __tat__length__

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/length.hpp>

namespace units {
namespace si {

typedef boost::units::si::length length;
typedef boost::units::si::mass_density mass_density;
typedef boost::units::si::mass mass;

typedef boost::units::si::temperature temperature;
typedef boost::units::si::power power;
typedef boost::units::si::solid_angle solid_angle;
typedef boost::units::si::electric_potential electric_potential;
typedef boost::units::si::dimensionless dimensionless ;
typedef boost::units::si::velocity velocity;
typedef boost::units::si::area area;
typedef boost::units::si::time time;
typedef boost::units::si::frequency frequency;

using boost::units::si::meters;
using boost::units::si::meter;

using boost::units::si::second;

using boost::units::si::watts;
using boost::units::si::watt;

using boost::units::si::volts;

using boost::units::si::kelvin;


}}

#endif /* defined(__tat__length__) */
