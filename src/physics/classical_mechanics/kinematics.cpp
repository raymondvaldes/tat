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
#include <vector>
#include <boost/assert.hpp>

#include "physics/classical_mechanics/kinematics.h"
#include "algorithm/algorithm.h"

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
angularFrequency_to_frequency(
  units::quantity< units::si::angular_frequency > const &  omega )
noexcept -> units::quantity< units::si::frequency >
{
  assert( omega.value() != 0 ) ;

  using units::si::radians;

  auto const frequency = omega / ( 2 * M_PI * radians ) ;

  return frequency;
}

auto
frequency_to_angularFrequency(
  units::quantity< units::si::frequency > const & frequency )
noexcept -> units::quantity< units::si::angular_frequency >
{
  using units::si::radians;
  assert( frequency.value() != 0 );
  
  auto const omega = 2. * M_PI * radians * frequency ;
  
  return omega;
}


auto
angularFrequencies_from_frequencies
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies
)
noexcept -> std::vector < units::quantity< units::si::angular_frequency > >
{
  using std::vector;
  using std::begin;
  using units::quantity;
  using units::si::angular_frequency;
  using algorithm::transform;
  
  auto const count = frequencies.size();
  auto angularFrequencies = vector< quantity< angular_frequency > >{ count };
  
  transform( frequencies, begin( angularFrequencies )  ,
  []( auto const frequency ) noexcept
  {
    auto const angularFrequency = frequency_to_angularFrequency( frequency ) ;
    return angularFrequency;
  } );

  return angularFrequencies;
}

auto
frequencies_from_angularFrequencies
(
  std::vector< units::quantity< units::si::angular_frequency > > const & angularFrequencies
)
noexcept -> std::vector < units::quantity< units::si::frequency > >
{
  using std::vector;
  using std::begin;
  using units::quantity;
  using units::si::frequency;
  using algorithm::transform;
  
  auto const count = angularFrequencies.size();
  auto frequencies = vector< quantity< frequency > >{ count };
  
  transform( angularFrequencies, begin( frequencies )  ,
  []( auto const angularFrequency ) noexcept
  {
    auto const freq = angularFrequency_to_frequency( angularFrequency ) ;
    return freq;
  } );

  return frequencies;
}



} // namespace classical_mechanics

} // namespace physics
