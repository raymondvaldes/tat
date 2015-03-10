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

#ifndef __tat__thermalpenetration__
#define __tat__thermalpenetration__

#include <cassert>
#include <vector>

#include "units.h"

namespace thermal{

namespace define{

auto
lthermal( const double L_coat, const double k_c, const double psi_c,
          const double omega )
noexcept -> double ;

auto
lthermal_freq( const double diff, const double freq,  const double L_c )
noexcept -> double ;

auto
lthermal_omeg( const double diff, const double omega, const double L_c )
noexcept -> double ;


auto
thermal_penetration(
  units::quantity<units::si::thermal_diffusivity> const alpha,
  units::quantity<units::si::angular_frequency> const omega,
  units::quantity<units::si::length> const L )
noexcept -> units::quantity< units::si::dimensionless >;

auto
thermal_penetration(
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::frequency > const & frequency,
  units::quantity< units::si::length > const & L )
noexcept -> units::quantity< units::si::dimensionless >;
  
auto
angularFrequency_from_thermalPenetration(
  units::quantity< units::si::dimensionless > const & lthermal,
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::length > const & L )
noexcept -> units::quantity< units::si::angular_frequency >;
  
auto
angularFrequencies_from_thermalPenetrations
(
  std::vector< units::quantity< units::si::dimensionless > > const & lthermals,
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::length > const & L 
)
noexcept -> std::vector< units::quantity< units::si::angular_frequency > >;
  
auto
frequency_from_thermalPenetration(
  units::quantity< units::si::dimensionless > const & lthermal,
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::length > const & L )
noexcept -> units::quantity< units::si::frequency >;
  
  
} // namespace define

} // namespace thermal


#endif /* defined(__tat__thermalpenetration__) */
