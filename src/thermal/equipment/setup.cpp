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

#include "thermal/equipment/setup.h"
#include "tools/interface/xml.h"

namespace thermal{
  namespace equipment{

setup::setup( Laser laser_, Detector detector_)
: laser(laser_), detector(detector_)
{
  q_surface = 0;
}

setup setup::loadConfigfromXML( const boost::property_tree::ptree pt )
{
    //initialize laser
  using tools::interface::getItem;
  const auto power      = getItem<double>( pt, "Laser.power" ) ;
  const auto radius     = getItem<double>( pt, "Laser.radius" ) ;
  const auto offset     = getItem<double>( pt, "Laser.offset" ) ;
  const auto amplitude  = getItem<double>( pt, "Laser.amplitude" ) ;
  const class Laser CO2Laser( power, radius, offset, amplitude );
  
    //initialize detector
  const auto detector_rad = getItem<double>( pt, "Detector.radius" );
  const auto detector_lam = getItem<double>( pt, "Detector.lambda" );
  const class Detector Emissiondetector( detector_lam, detector_rad );
  
    //initialize experimental setup object
  const class setup expSetup( CO2Laser, Emissiondetector );
  
  return expSetup;
}
    
  }
}
