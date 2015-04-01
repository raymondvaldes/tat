/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__setup__
#define __tat__setup__

#include <iostream>
#include <boost/property_tree/ptree.hpp>

#include "thermal/equipment/laser.h"
#include "thermal/equipment/detector/detector.h"

namespace thermal{

namespace equipment{
  
class setup
{
public:
  Laser laser;
  detector::Detector detector;
  double q_surface;
  
  explicit setup( Laser laser_,  detector::Detector detector_) noexcept;
  static setup loadConfigfromXML( const boost::property_tree::ptree pt ) noexcept;
};

} // namespace equipment

} // namespace thermal
  
#endif /* defined(__tat__setup__) */
