/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <boost/assert.hpp>
#include "thermal/equipment/detector/detector.h"

namespace thermal{

namespace equipment{

namespace detector{

Detector::Detector(const double wavelength_, const double radius_) noexcept
:wavelength(wavelength_), radius(radius_)
{
  BOOST_ASSERT_MSG( ( wavelength > 0 )     &&
                    ( radius > 0 ),
                   "check detector inputs\n\n" );
}

double Detector::getPeakWavelength(void) const noexcept {

  return wavelength;
}

double Detector::getSpotSizeRadius(void) const noexcept {
  return radius;
}

Detector::~Detector(void) noexcept {}
  
} // namespace detector
  
} // namespace equipment

} // namespace thermal
