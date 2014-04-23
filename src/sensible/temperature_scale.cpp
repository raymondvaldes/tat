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

#include "sensible/temperature_scale.h"

namespace sensible{
  

temperatureScale::
temperatureScale( const double tolerance_, const double referance_,
                  const double base_, const double rear_ ):
tolerance(tolerance_), referance(referance_), base(base_), rear(rear_)
{}

temperatureScale::~temperatureScale( void ) { }

struct temperatureScale temperatureScale::
loadConfigfromXML( const boost::property_tree::ptree pt )
{
    //initialize parameter estimation settings
  const double tolerance    = pt.get<double>( "tolerance" );
  const double referance    = pt.get<double>( "referance" );
  const double base         = pt.get<double>( "base" );
  const double rear         = pt.get<double>( "rear" );
  
  struct temperatureScale TemperatureScale(tolerance, referance, base, rear);
  return TemperatureScale;
}


}
