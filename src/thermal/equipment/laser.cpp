/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <cmath>
#include <boost/assert.hpp>
#include "thermal/equipment/laser.h"

namespace thermal{
namespace equipment{

Laser::Laser(const double a, const double b, const double c, const double d) noexcept:
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

void Laser::update(void) noexcept
{
  Is = IntensitySteady();
  It = IntensityTransient();
}

void Laser::updateRadius(const double r) noexcept
{
  BOOST_ASSERT_MSG( ( r > 0 ), "check laser radius inputs\n\n" );
  radius = r;
  update();
}

void Laser::updatePower(const double Qpower) noexcept
{
  BOOST_ASSERT_MSG(Qpower >= 0, "power can't be negaitve \n\n");
  Qlaser = Qpower;
  update();
}

double Laser::area(void) const noexcept
{
  return M_PI_2 * radius * radius;
}

double Laser::IntensityTotal(void) const noexcept
{
  return Qlaser / area();
}

double Laser::IntensitySteady(void) const noexcept
{
  return IntensityTotal() * offset;
}

double Laser::IntensityTransient(void) const noexcept
{
  return IntensitySteady() * amplitude;
}

Laser::~Laser() noexcept{}
  
  
}}
