/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__kinematics__
#define __tat__kinematics__

#include <vector>
#include "units.h"

namespace physics{

namespace classical_mechanics{

double period_to_angularFrequency( const double period ) noexcept;

double angularFrequency_to_period( const double angularFrequency ) noexcept;

auto
frequency_to_angularFrequency(
  units::quantity< units::si::frequency > const &  frequency )
noexcept -> units::quantity< units::si::angular_frequency >;

auto
angularFrequency_to_frequency(
  units::quantity< units::si::angular_frequency > const &  frequency )
noexcept -> units::quantity< units::si::frequency >;

auto
angularFrequencies_from_frequencies
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies
)
noexcept -> std::vector < units::quantity< units::si::angular_frequency > >;

auto
frequencies_from_angularFrequencies
(
  std::vector< units::quantity< units::si::angular_frequency > > const & angularFrequencies
)
noexcept -> std::vector < units::quantity< units::si::frequency > >;

auto
get_period_from_frequency ( units::quantity< units::si::frequency > const freq )
noexcept -> units::quantity< units::si::time >;

auto
get_period_from_angularFrequency
(
  units::quantity< units::si::angular_frequency > const  omega
)
noexcept -> units::quantity< units::si::time >;

auto
get_delta_time_from_phase
(
  units::quantity< units::si::plane_angle > const phase,
  units::quantity< units::si::frequency > const f
)
noexcept -> units::quantity< units::si::time >;

auto
get_delta_time_from_phase
(
  units::quantity< units::si::plane_angle > const phase,
  units::quantity< units::si::angular_frequency > const omega
)
noexcept -> units::quantity< units::si::time >;

} // namespace classical_mechanics

} // physics


#endif /* defined(__tat__kinematics__) */
