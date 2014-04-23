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

#ifndef __tat__setup__
#define __tat__setup__

#include <iostream>
#include <boost/property_tree/ptree.hpp>

#include "thermal/equipment/laser.h"
#include "thermal/equipment/detector.h"

namespace thermal{namespace equipment{
  
class setup
{
public:
  Laser laser;
  Detector detector;
  double q_surface;
  
  explicit setup( Laser laser_,  Detector detector_);
  static class setup loadConfigfromXML( const boost::property_tree::ptree pt );
};

}}
  
#endif /* defined(__tat__setup__) */
