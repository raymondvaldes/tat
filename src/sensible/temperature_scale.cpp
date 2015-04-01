/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "sensible/temperature_scale.h"

namespace sensible{
  

temperatureScale::
temperatureScale( const double tolerance_, const double referance_,
                  const double base_, const double rear_ ) noexcept:
tolerance(tolerance_), referance(referance_), base(base_), rear(rear_)
{}

temperatureScale::~temperatureScale( void ) noexcept { }

temperatureScale temperatureScale::
loadConfigfromXML( const boost::property_tree::ptree pt ) noexcept
{
    //initialize parameter estimation settings
  const double tolerance    = pt.get<double>( "tolerance" );
  const double referance    = pt.get<double>( "referance" );
  const double base         = pt.get<double>( "base" );
  const double rear         = pt.get<double>( "rear" );
  
  temperatureScale TemperatureScale(tolerance, referance, base, rear);
  return TemperatureScale;
}


}
