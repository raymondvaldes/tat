/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "thermal/equipment/setup.h"
#include "tools/interface/xml.h"

namespace thermal{

namespace equipment{

setup::setup( Laser laser_, detector::Detector detector_) noexcept
: laser(laser_), detector(detector_)
{
  q_surface = 0;
}

setup setup::loadConfigfromXML( const boost::property_tree::ptree pt ) noexcept
{
    //initialize laser
  using tools::interface::getItem;
  auto const power      = getItem<double>( pt, "Laser.power" ) ;
  auto const radius     = getItem<double>( pt, "Laser.radius" ) ;
  auto const offset     = getItem<double>( pt, "Laser.offset" ) ;
  auto const amplitude  = getItem<double>( pt, "Laser.amplitude" ) ;
  const Laser CO2Laser( power, radius, offset, amplitude );
  
    //initialize detector
  auto const detector_rad = getItem<double>( pt, "Detector.radius" );
  auto const detector_lam = getItem<double>( pt, "Detector.lambda" );
  const detector::Detector Emissiondetector( detector_lam, detector_rad );
  
    //initialize experimental setup object
  const setup expSetup( CO2Laser, Emissiondetector );
  
  return expSetup;
}
    
} // namespace equipment

} // namespace thermal
