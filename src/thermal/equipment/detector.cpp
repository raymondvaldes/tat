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
#include <boost/assert.hpp>
#include "thermal/equipment/detector.h"

namespace thermal{
namespace equipment{

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
  
}}