/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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
#include <cmath>
#include <boost/assert.hpp>
#include "thermal/equipment/laser.h"

namespace thermal{
namespace equipment{

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
  
  
}}
