/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
-------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/
#include <boost/assert.hpp>

#include "models/expEquipment.hpp"
#include "thermal/simulations/Numerical_Setup.h"
#include "math/utility.hpp"

namespace equipment{

Detector::Detector(const double wavelength_, const double radius_)
    :wavelength(wavelength_), radius(radius_)
{
  BOOST_ASSERT_MSG( ( wavelength > 0 )     &&
                    ( radius > 0 ),
                    "check detector inputs\n\n" );
}

Detector::~Detector(void){}

Laser::Laser(const double a, const double b, const double c, const double d):
             offset(c), amplitude(d), Qlaser(a), radius(b)
{
  BOOST_ASSERT_MSG( ( offset > 0 && offset < 1 )     &&
                    ( amplitude > 0 )                &&
                    ( ( amplitude + offset ) <= 1 )  &&
                    ( amplitude <= offset )          &&
                    ( Qlaser > 0 )                   &&
                    ( radius > 0 ),
                    "check laser inputs\n\n" );
  update();
}

void Laser::update(void)
{
    Is = IntensitySteady();
    It = IntensityTransient();
}

void Laser::updateRadius(const double r)
{
  BOOST_ASSERT_MSG( ( r > 0 ), "check laser radius inputs\n\n" );
  radius = r;
  update();
}

void Laser::updatePower(const double Qpower)
{
  BOOST_ASSERT_MSG(Qpower >= 0, "power can't be negaitve \n\n");
  Qlaser = Qpower;
  update();
}

double Laser::area(void) const
{
    return M_PI_2 * radius * radius;
}

double Laser::IntensityTotal(void) const
{
    return Qlaser / area();
}

double Laser::IntensitySteady(void) const
{
    return IntensityTotal() * offset;
}

double Laser::IntensityTransient(void) const
{
    return IntensitySteady() * amplitude;
}

Laser::~Laser(){}

setup::setup(struct Laser laser_, struct Detector detector_)
    : laser(laser_), detector(detector_)
{
  q_surface = 0;
}

class setup setup::loadConfigfromXML( const boost::property_tree::ptree pt )
{
    //initialize laser
    const double power      = pt.get< double >( "Laser.power" );
    const double radius     = pt.get< double >( "Laser.radius" );
    const double offset     = pt.get< double >( "Laser.offset" );
    const double amplitude  = pt.get< double >( "Laser.amplitude" );
    const class Laser CO2Laser( power, radius, offset, amplitude );

    //initialize detector
    const double detector_rad = pt.get< double >( "Detector.radius" );
    const double detector_lam = pt.get< double >( "Detector.lambda" );
    const class Detector Emissiondetector( detector_lam, detector_rad );

    //initialize experimental setup object
    const class setup expSetup( CO2Laser, Emissiondetector );

    return expSetup;
}


}
