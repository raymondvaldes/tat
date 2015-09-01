/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include <cmath>

#include "algorithm/algorithm.h"
#include "thermal/define/lthermal.h"
#include "physics/classical_mechanics/kinematics.h"

namespace thermal{
namespace define{

  using std::vector;
    using namespace units;
  using algorithm::transform;
  using std::begin;

auto
lthermal(
  const double L_coat,
  const double k_c,
  const double psi_c,
  const double omega )
noexcept -> double
{
  const double diff = k_c / psi_c ;
  return lthermal_omeg( diff, omega, L_coat );
}

auto
lthermal_freq(
  const double diffusivity,
  const double frequency,
  const double L )
noexcept -> double
{
  const double omega = 2 * M_PI * frequency ;
  return lthermal_omeg( diffusivity, omega, L ) ;
}

auto
lthermal_omeg(
  const double diffusivity,
  const double angular_omega,
  const double L )
noexcept -> double
{
  using std::sqrt;
  return sqrt( diffusivity / angular_omega ) / L ;
}

auto
thermal_penetration_dimensional(
  units::quantity<units::si::thermal_diffusivity> const alpha,
  units::quantity<units::si::angular_frequency> const omega
)
noexcept -> units::quantity< units::si::length >
{
  assert( alpha.value() > 0 ) ;
  assert( omega.value() > 0 ) ;

  auto const thermalPenetration = sqrt( ( alpha  / omega ) * radians )  ;
  
  return thermalPenetration ;
}

auto
thermal_penetration(
  units::quantity<units::si::thermal_diffusivity> const alpha,
  units::quantity<units::si::angular_frequency> const omega,
  units::quantity<units::si::length> const L )
noexcept -> units::quantity< units::si::dimensionless >
{
  assert( alpha.value() > 0 ) ;
  assert( omega.value() > 0 ) ;
  assert( L.value() > 0 ) ;

  auto const thermalPenetration = sqrt( ( alpha  / omega ) * radians ) / L  ;
  
  return thermalPenetration ;
}

auto
thermal_penetration(
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::frequency > const & frequency,
  units::quantity< units::si::length > const & L )
noexcept -> units::quantity< units::si::dimensionless >
{
  assert( alpha.value() > 0 );
  assert( frequency.value() > 0 );
  assert( L.value() > 0 ) ;

  using physics::classical_mechanics::frequency_to_angularFrequency ;
  
  auto const omega = frequency_to_angularFrequency( frequency ) ;
  
  return thermal_penetration( alpha, omega, L );
}

auto
thermalPenetrations_from_frequencies
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::thermal_diffusivity > const alpha,
  units::quantity< units::si::length > const L
)
noexcept -> std::vector< units::quantity< units::si::dimensionless > >
{
  assert( !frequencies.empty() );
  assert( alpha.value() > 0  );
  assert( L > 0 * meters );
  
  auto const count = frequencies.size();
  auto lthermals = vector< quantity< dimensionless > >( count ) ;
  
  transform( frequencies, begin( lthermals ) , [ &alpha, &L ]
  ( auto const freq ) noexcept
  {
    auto const lthermal = thermal_penetration( alpha, freq , L ) ;
    return lthermal;
  } );
  
  return lthermals;
}

auto
thermalPenetrations_from_angularFrequencies
(
  std::vector< units::quantity< units::si::angular_frequency > > const & angularFrequencies,
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::length > const & L
)
noexcept -> std::vector< units::quantity< units::si::dimensionless > >
{
  using std::vector;
  using algorithm::transform;
  using std::begin;

  auto const count = angularFrequencies.size();
  auto lthermals = vector< quantity< dimensionless > >{ count } ;
  
  transform( angularFrequencies, begin( lthermals ) ,
  [ &alpha, &L ]( auto const & angularFrequency ) noexcept
  {
    auto const lthermal =
      thermal_penetration( alpha, angularFrequency , L ) ;
    return lthermal;
  } );
  
  return lthermals;
}


auto
angularFrequencies_from_thermalPenetrations
(
  std::vector< units::quantity< units::si::dimensionless > > const & lthermals,
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::length > const & L
)
noexcept -> std::vector< units::quantity< units::si::angular_frequency > >
{
  using std::vector;
  using algorithm::transform;
  using std::begin;

  auto const count = lthermals.size();
  auto angularFrequencies = vector< quantity< angular_frequency > >{ count } ;
  
  transform( lthermals, begin( angularFrequencies ) ,
  [ &alpha, &L ]( auto const & lthermal ) noexcept
  {
    auto const angularFrequency =
      angularFrequency_from_thermalPenetration( lthermal , alpha, L ) ;
    return angularFrequency;
  } );
  
  return angularFrequencies;
}


auto
frequencies_from_thermalPenetrations(
  std::vector< units::quantity< units::si::dimensionless > > const & lthermals,
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::length > const & L )
noexcept -> std::vector< units::quantity< units::si::frequency > >
{
  using physics::classical_mechanics::frequencies_from_angularFrequencies;
  
  auto const omegas =
  angularFrequencies_from_thermalPenetrations( lthermals, alpha, L ) ;
  
  auto const frequencies = frequencies_from_angularFrequencies( omegas ) ;
  
  return frequencies;
}

auto
angularFrequency_from_thermalPenetration(
  units::quantity< units::si::dimensionless > const & lthermal,
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::length > const & L )
noexcept -> units::quantity< units::si::angular_frequency >
{
  
  auto const omega = alpha / pow< 2 >(  lthermal * L ) ;
  return omega * radians;
}

auto
frequency_from_thermalPenetration(
  units::quantity< units::si::dimensionless > const & lthermal,
  units::quantity< units::si::thermal_diffusivity > const & alpha,
  units::quantity< units::si::length > const & L )
noexcept -> units::quantity< units::si::frequency >
{
  using physics::classical_mechanics::angularFrequency_to_frequency;
  
  auto const omega =
    angularFrequency_from_thermalPenetration( lthermal, alpha, L ) ;
  
  auto const frequency = angularFrequency_to_frequency( omega ) ;
  
  return frequency;
}


} // namespace define

} // namespace thermal
