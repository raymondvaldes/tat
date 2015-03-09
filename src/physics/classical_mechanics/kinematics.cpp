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

#include <cmath>
#include <boost/assert.hpp>

#include "kinematics.h"

namespace physics{

namespace classical_mechanics{

auto
period_to_angularFrequency( const double period )
noexcept -> double
{
  const bool pass = period > 0 ;
  BOOST_ASSERT( pass ) ;

  const double angularFrequency = 2 * M_PI / period;
  return angularFrequency ;
}

auto
angularFrequency_to_period( const double angularFrequency )
noexcept -> double
{
  const bool pass = angularFrequency > 0 ;
  BOOST_ASSERT( pass ) ;

  const double period = 2 * M_PI / angularFrequency;
  return period;
}

auto
frequency_to_angularFrequency(
  units::quantity< units::si::frequency > const & frequency )
noexcept -> units::quantity< units::si::angular_frequency >
{
  using units::si::radians;
  assert( frequency.value() > 0 );
  
  return 2. * M_PI * radians * frequency;
}

} // namespace classical_mechanics

} // namespace physics
