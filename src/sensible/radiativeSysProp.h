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

#ifndef __tat__radiativeSysProp__sensible
#define __tat__radiativeSysProp__sensible

#include <iostream>
#include <boost/property_tree/ptree.hpp>

namespace sensible{
  
class radiativeSysProp
{
private:
  
  
public:
  double R0;
  double R1;
  double Emit1;
  explicit radiativeSysProp( const double R0_, const double R1_,
                            const double Emit1_);
  static radiativeSysProp
  loadConfig( const boost::property_tree::ptree pt );
  ~radiativeSysProp(void);
};

}

#endif /* defined(__tat__radiativeSysProp__sensible) */
