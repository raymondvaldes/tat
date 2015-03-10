//
//  slab.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <complex>

#include "thermal/model/slab/slab.h"
#include "thermal/define/lthermal.h"
#include "physics/classical_mechanics/kinematics.h"

namespace thermal {

namespace model {

namespace slab {

auto
surface_temperature_amplitudes
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> std::vector < units::quantity< units::si::temperature > >
{
  using physics::classical_mechanics::angularFrequencies_from_frequencies;
  
  auto const omegas = angularFrequencies_from_frequencies( frequencies ) ;

  auto const amplitudes = surface_temperature_amplitudes( omegas, I_t, slab ) ;
  
  return amplitudes;
}

auto
surface_temperature_amplitudes
(
  std::vector< units::quantity< units::si::dimensionless > > const & lthermals,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> std::vector < units::quantity< units::si::temperature > >
{
  using thermal::define::angularFrequencies_from_thermalPenetrations;
  
  auto const alpha = slab.alpha;
  auto const L = slab.characteristic_length;
  
  auto const omegas =
    angularFrequencies_from_thermalPenetrations( lthermals, alpha, L ) ;

  auto const amplitudes = surface_temperature_amplitudes( omegas, I_t, slab ) ;
  
  return amplitudes;
}

auto
surface_temperature_amplitudes
(
  std::vector< units::quantity< units::si::angular_frequency > > const & omegas,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> std::vector < units::quantity< units::si::temperature > >
{
  using std::vector;
  using std::begin;
  using units::quantity;
  using units::si::temperature;
  using algorithm::transform;
  
  auto const count = omegas.size();
  auto amplitudes = vector< quantity< temperature > >{ count };
  
  transform( omegas, begin( amplitudes ) ,
  [&I_t, &slab]( auto const omega ) noexcept
  {
    auto const phase = surface_temperature_amplitude( omega , I_t, slab ) ;
    return phase;
  } );

  return amplitudes;
}

auto
surface_temperature_amplitude
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::temperature >
{
  using units::abs;
  
  auto const Tsurface = complex_surface_temperature( w, I_t, slab ) ;
  
  auto const amplitude = abs( Tsurface ) ;
  
  return amplitude ;
}


auto
surface_temperature_phases
(
  std::vector< units::quantity< units::si::dimensionless > > const & lthermals,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> std::vector < units::quantity< units::si::plane_angle > >
{
  using thermal::define::angularFrequencies_from_thermalPenetrations;
  
  auto const alpha = slab.alpha;
  auto const L = slab.characteristic_length;
  
  auto const omegas =
    angularFrequencies_from_thermalPenetrations( lthermals, alpha, L ) ;

  auto const phases = surface_temperature_phases( omegas, I_t, slab ) ;
  
  return phases;
}

auto
surface_temperature_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> std::vector < units::quantity< units::si::plane_angle > >
{
  using physics::classical_mechanics::angularFrequencies_from_frequencies;
  
  auto const omegas = angularFrequencies_from_frequencies( frequencies ) ;

  auto const phases = surface_temperature_phases( omegas, I_t, slab ) ;
  
  return phases;
}


auto
surface_temperature_phases
(
  std::vector< units::quantity< units::si::angular_frequency > > const & omegas,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> std::vector < units::quantity< units::si::plane_angle > >
{
  using std::vector;
  using std::begin;
  using units::quantity;
  using units::si::plane_angle;
  using algorithm::transform;
  
  auto const count = omegas.size();
  auto phases = vector< quantity< plane_angle > >{count};
  
  transform( omegas, begin( phases )  ,
  [&I_t, &slab]( auto const omega ) noexcept
  {
    auto const phase = surface_temperature_phase( omega , I_t, slab ) ;
    return phase;
  } );

  return phases;
}


auto
surface_temperature_phase
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::plane_angle >
{
  assert( w.value() != 0 );
  assert( I_t.value() != 0 );
  using units::arg;
  
  auto const Tsurface = complex_surface_temperature( w, I_t, slab ) ;
  
  auto const phase = arg( Tsurface ) ;
  
  return phase;
}

auto
exponentialModulator_nondimensional
(
  units::quantity<units::si::dimensionless > const omega_non,
  units::quantity<units::si::dimensionless > const time_non
)
-> units::quantity< units::si::dimensionless, std::complex< double > >
{
  assert( omega_non.value() != 0 ) ;
  assert( time_non.value() != 0 ) ;

  using std::complex;
  using units::exp;
  using units::quantity;
  using units::si::dimensionless;

  auto const i_imag = complex< double >( 0, 1 ) ;
  auto const i_non = quantity< dimensionless, complex< double > >( i_imag ) ;
  auto const negative_one = quantity< dimensionless >( -1 );

  auto const exponential = exp( negative_one * i_non * omega_non * time_non ) ;
  
  return exponential ;
}

auto
real_transient_temperature
(
  units::quantity< units::si::length > const x ,
  units::quantity< units::si::time > const t,
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept ->  units::quantity< units::si::temperature >
{
  assert( x.value() > 0 ) ;
  assert( t.value() != 0 ) ;
  assert( w.value() != 0 ) ;
  assert( I_t.value() != 0 ) ;

  using units::real;

  auto const temperature_dimensional = complex_temperature( x, w, I_t, slab );
  
  auto const L = slab.characteristic_length;
  auto const alpha = slab.alpha;
  
  auto const w_non = nondimensional_omega( w, L, alpha ) ;
  auto const t_non = nondimensional_time( t, L , alpha ) ;
  
  auto const modulator = exponentialModulator_nondimensional( w_non , t_non ) ;

  auto const real_transient = real( temperature_dimensional * modulator );
 
  return real_transient;
}

auto
complex_surface_temperature
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::temperature, std::complex<double > >
{
  assert( w.value() != 0 ) ;
  assert( I_t.value() != 0 );

  using units::quantity;
  using units::si::length;

  auto const x_surface = quantity< length >::from_value( 0 );
  
  auto const temperature_dimensional =
    complex_temperature( x_surface, w, I_t, slab );

  return temperature_dimensional;
}


auto
temperature_phase
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::plane_angle >
{
  assert( x.value() > 0 ) ;
  assert( w.value() != 0 ) ;
  assert( I_t.value() != 0 ) ;

  using units::quantity;
  using units::si::length;
  
  auto const T_cmplx = complex_temperature( x, w, I_t, slab ) ;
  
  using units::arg;
  auto const phase =arg( T_cmplx ) ;
  
  return phase;
}

auto
temperature_amplitude
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::temperature >
{
  assert( x.value() > 0 ) ;
  assert( w.value() != 0 ) ;
  assert( I_t.value() != 0 ) ;

  using units::quantity;
  using units::si::length;
  
  auto const T_cmplx = complex_temperature( x, w, I_t, slab ) ;
  
  using units::abs;
  auto const amplitude = abs( T_cmplx ) ;
  
  return amplitude;
}


auto
complex_temperature
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::temperature, std::complex<double > >
{
  assert( x.value() >= 0 ) ;
  assert( w.value() != 0 ) ;
  assert( I_t.value() > 0 ) ;

  using units::quantity;
  using units::si::temperature;

  auto const characteristic_length = slab.characteristic_length;
  auto const alpha = slab.alpha;
  auto const k = slab.k;

  auto const theta_complex =
    neumann_and_direchlet_BC( x , w , characteristic_length, alpha ) ;

  auto const deltaT = ( I_t * characteristic_length ) / k ;
  
  auto const temperature_dimensional = theta_complex * deltaT ;
  
  return temperature_dimensional;
}

auto nondimensional_time
(
  units::quantity< units::si::time > const time,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> units::quantity< units::si::dimensionless>
{
  assert( time.value() != 0 ) ;
  assert( L.value() > 0 ) ;
  assert( alpha.value() != 0 ) ;

  using units::pow;
  
  auto const t_non = ( time * alpha )  / pow< 2 >( L );
  
  return t_non;
}

auto nondimensional_omega
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> units::quantity< units::si::dimensionless>
{
  assert( w.value() != 0 ) ;
  assert( L.value() > 0 ) ;
  assert( alpha.value() != 0 ) ;

  using units::si::radians;
  using units::pow;
  
  auto const w_non = ( w * pow< 2 >( L ) / alpha ) / radians;

  return w_non;
}
 
auto neumann_and_direchlet_BC(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::length > const characteristic_length,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >
{
  // eq:  T''(x) + ( ( sqrt( i * w ) )^2 ) T(x) == 0
  // BC:  T'(0)   == - 1
  // BC:  T(1)  == 0

  assert( x.value() >= 0 ) ;
  assert( characteristic_length.value() > 0 ) ;
  assert( alpha.value() != 0 ) ;
  assert( w.value() != 0 ) ;

  using std::complex;

  using units::sqrt;
  using units::quantity;
  using units::si::dimensionless;
  using math::differential::waveEquation::analytical_solution_10;

  auto const i_imag = complex< double >( 0, 1 ) ;
  
  auto const L = characteristic_length;
    
  auto const w_non = nondimensional_omega( w, L, alpha ) ;
  auto const i_non = quantity< dimensionless, complex< double > >( i_imag ) ;
  auto const Kappa = sqrt( i_non * w_non ) ;
  
  
  auto const A_non = quantity< dimensionless >( -1 ) ;
  
  auto const x_non = x / L ;
  
  auto const L_b =  quantity< dimensionless >( 1 ) ;

  auto const s_x = analytical_solution_10( x_non, Kappa, A_non, L_b ) ;

  return s_x;
}

} // namespace slab
  
} // namespace model
  
} // namespace thermal
