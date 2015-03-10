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

#include "thermal/define/diffusivity.h"

namespace thermal{

namespace define{

double diffusivity( const double k, const double rhoCp ) noexcept
{
  return k / rhoCp ;
}

auto diffusivity
(
  units::quantity< units::si::volumetric_heat_capacity > const & rhoCp,
  units::quantity< units::si::thermal_conductivity> const & k
)
noexcept -> units::quantity< units::si::thermal_diffusivity >
{
  auto const alpha = k / rhoCp;
  return alpha;
}

    
} // namesapce define

} // namespace thermal
