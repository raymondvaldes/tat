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

#include "sensible/radiativeSysProp.h"

namespace sensible{
  
  
  


radiativeSysProp::
radiativeSysProp( const double R0_, const double R1_, const double Emit1_) noexcept
: R0(R0_), R1(R1_), Emit1(Emit1_){}

radiativeSysProp::
~radiativeSysProp(void) noexcept{}

class radiativeSysProp
radiativeSysProp::loadConfig( const boost::property_tree::ptree pt ) noexcept
{
  const double R0_ = pt.get<double>("R0");
  const double R1_ = pt.get<double>("R1");
  const double Emit1_ = pt.get<double>("Emit1");
  
  radiativeSysProp Obj( R0_, R1_, Emit1_);
  
  return Obj;
}
  
  
}
