/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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
thermalPenetrations_from_frequencies
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::length > const & L
)
noexcept -> std::vector< units::quantity< units::si::dimensionless > >;

auto
thermalPenetrations_from_angularFrequencies
(
  std::vector< units::quantity< units::si::angular_frequency > > const & angularFrequencies,
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::length > const & L
)
noexcept -> std::vector< units::quantity< units::si::dimensionless > >;
  
auto
frequencies_from_thermalPenetrations(
  std::vector< units::quantity< units::si::dimensionless > > const & lthermals,
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::length > const & L )
noexcept -> std::vector< units::quantity< units::si::frequency > >;
  
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
