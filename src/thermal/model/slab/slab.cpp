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
#include "thermal/define/volumetricHeatCapacity.h"
#include "thermal/define/diffusivity.h"
#include "thermal/define/effusivity.hpp"

#include "thermal/define/conductivity.h"
#include "algorithm/algorithm.h"

namespace thermal {

namespace model {

namespace slab {



Slab::Slab(
  units::quantity< units::si::length > const characteristic_length_in,
  units::quantity< units::si::thermal_diffusivity > const alpha_in,
  units::quantity< units::si::thermal_conductivity > const k_in
)
  : characteristic_length( characteristic_length_in ),
    k( k_in ),
    rhoCp( thermal::define::volumetricHeatCapacity( alpha_in, k )  )
{
  assert( alpha_in.value() > 0 ) ;
  assert( k_in.value() > 0 ) ;
  assert( rhoCp.value() > 0 ) ;

  assert( characteristic_length_in.value() > 0 ) ;

};


Slab::Slab(
  units::quantity< units::si::length > const characteristic_length_in,
  units::quantity< units::si::thermal_diffusivity > const alpha_in,
  units::quantity< units::si::volumetric_heat_capacity > const rhoCp_in
) :Slab(
    characteristic_length_in,
    alpha_in,
    thermal::define::conductivity( rhoCp_in, alpha_in) ) {}

Slab::Slab(
  units::quantity< units::si::length > const characteristic_length_in,
  units::quantity< units::si::thermal_conductivity > const k_in,
  units::quantity< units::si::volumetric_heat_capacity > const rhoCp_in
) :Slab(
    characteristic_length_in,
    thermal::define::diffusivity( k_in , rhoCp_in ),
    k_in ) {}
  

auto Slab::get_conductivity( void ) const
-> units::quantity< units::si::thermal_conductivity >
{
  return k;
}

auto Slab::get_volumetric_heatCapacity( void ) const
-> units::quantity< units::si::volumetric_heat_capacity>
{
  return rhoCp;
}

auto Slab::get_diffusivity( void ) const
-> units::quantity< units::si::thermal_diffusivity >
{
  using thermal::define::diffusivity;
  auto const alpha_here = diffusivity( k, rhoCp );
  return alpha_here;
}

auto Slab::get_effusivity( void ) const
-> units::quantity< units::si::thermal_effusivity >
{
  using thermal::define::effusivity;
  auto const e = effusivity( k , rhoCp );
  return e;
}

auto Slab::set_conductivity
(
  units::quantity< units::si::thermal_conductivity > const & k_in
) -> void
{
  k = k_in;
}

auto Slab::set_volumetric_heatCapacity
(
  units::quantity< units::si::volumetric_heat_capacity> const & rhoCp_in
) -> void
{
  rhoCp = rhoCp_in;
}

auto Slab::set_effusivity_update_k_hold_rhoCp (
  units::quantity< units::si::thermal_effusivity > const & e
) -> void
{
  using thermal::define::conductivity;
  auto const updated_k = conductivity( rhoCp,  e ) ;
  set_conductivity( updated_k );
}

auto Slab::set_effusivity_update_rhoCp_hold_k (
units::quantity< units::si::thermal_effusivity > const & e
) -> void
{
  using thermal::define::volumetricHeatCapacity;
  auto const updated_rhoCp = volumetricHeatCapacity( e, k ) ;
  
  set_volumetric_heatCapacity( updated_rhoCp );
}

auto Slab::set_diffusivity_update_k_hold_rhoCp
(
  units::quantity< units::si::thermal_diffusivity > const & alpha_in
) -> void
{
  using thermal::define::conductivity;
  auto const updated_k = conductivity( rhoCp,  alpha_in ) ;
  set_conductivity( updated_k );
}

auto Slab::set_diffusivity_update_rhoCp_hold_k
(
  units::quantity< units::si::thermal_diffusivity > const & alpha_in
) -> void
{
  using thermal::define::volumetricHeatCapacity;
  auto const updated_rhoCp = volumetricHeatCapacity(alpha_in, k) ;
  
  set_volumetric_heatCapacity( updated_rhoCp );
}


auto
surface_temperature_amplitudes
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> std::vector < units::quantity< units::si::temperature > >
{
  using physics::classical_mechanics::angularFrequencies_from_frequencies;
  
  auto const omegas = angularFrequencies_from_frequencies( frequencies ) ;

  auto const amplitudes =
  surface_temperature_amplitudes( omegas, I_t, slab, boundary_condition, rear ) ;
  
  return amplitudes;
}

auto
surface_temperature_amplitudes
(
  std::vector< units::quantity< units::si::dimensionless > > const & lthermals,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> std::vector < units::quantity< units::si::temperature > >
{
  using thermal::define::angularFrequencies_from_thermalPenetrations;
  
  auto const alpha = slab.get_diffusivity();
  auto const L = slab.characteristic_length;
  
  auto const omegas =
  angularFrequencies_from_thermalPenetrations( lthermals, alpha, L ) ;

  auto const amplitudes =
  surface_temperature_amplitudes( omegas, I_t, slab, boundary_condition, rear ) ;
  
  return amplitudes;
}

auto
surface_temperature_amplitudes
(
  std::vector< units::quantity< units::si::angular_frequency > > const & omegas,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const BC,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
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
  [&I_t, &slab, &BC, &rear]( auto const omega ) noexcept
  {
    auto const phase =
    surface_temperature_amplitude( omega , I_t, slab, BC, rear ) ;
    return phase;
  } );

  return amplitudes;
}

auto
surface_temperature_amplitude
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> units::quantity< units::si::temperature >
{
  using units::abs;
  
  auto const Tsurface =
  complex_surface_temperature( w, I_t, slab, boundary_condition, rear ) ;
  
  auto const amplitude = abs( Tsurface ) ;
  
  return amplitude ;
}


auto
surface_temperature_phases
(
  std::vector< units::quantity< units::si::dimensionless > > const & lthermals,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> std::vector < units::quantity< units::si::plane_angle > >
{
  using thermal::define::angularFrequencies_from_thermalPenetrations;
  
  auto const alpha = slab.get_diffusivity();
  auto const L = slab.characteristic_length;
  
  auto const omegas =
    angularFrequencies_from_thermalPenetrations( lthermals, alpha, L ) ;

  auto const phases =
  surface_temperature_phases( omegas, slab, boundary_condition, rear ) ;
  
  return phases;
}

auto
surface_temperature_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> std::vector < units::quantity< units::si::plane_angle > >
{
  using physics::classical_mechanics::angularFrequencies_from_frequencies;
  
  auto const omegas = angularFrequencies_from_frequencies( frequencies ) ;

  auto const phases =
  surface_temperature_phases( omegas, slab, boundary_condition, rear ) ;
  
  return phases;
}


auto
surface_temperature_phases
(
  std::vector< units::quantity< units::si::angular_frequency > > const & omegas,
  Slab const & slab,
  enum back_boundary_condition const BC,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
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
  [ &slab, &BC, &rear ]( auto const omega ) noexcept
  {
    auto const phase = surface_temperature_phase( omega , slab, BC, rear ) ;
    return phase;
  } );

  return phases;
}


auto
surface_temperature_phase
(
  units::quantity< units::si::angular_frequency > const w,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> units::quantity< units::si::plane_angle >
{
  assert( w.value() != 0 );
  
  using units::quantity;
  using units::si::length;

  auto const x_surface = quantity< length >::from_value( 0 );

  auto const phase =
  temperature_phase( x_surface, w, slab, boundary_condition, rear ) ;
  
  return phase ;
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
  units::quantity< units::si::time > const t ,
  units::quantity< units::si::angular_frequency > const w ,
  units::quantity< units::si::heat_flux > const I_t ,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> units::quantity< units::si::temperature >
{
  assert( x.value() > 0 ) ;
  assert( t.value() != 0 ) ;
  assert( w.value() != 0 ) ;
  assert( I_t.value() != 0 ) ;

  using units::real;

  auto const temperature_dimensional =
  complex_temperature( x, w, I_t, slab, boundary_condition, rear );
  
  auto const L = slab.characteristic_length;
  auto const alpha = slab.get_diffusivity();
  
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
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> units::quantity< units::si::temperature, std::complex<double > >
{
  assert( w.value() != 0 ) ;
  assert( I_t.value() != 0 );

  using units::quantity;
  using units::si::length;

  auto const x_surface = quantity< length >::from_value( 0 );
  
  auto const temperature_dimensional =
  complex_temperature( x_surface, w, I_t, slab, boundary_condition, rear );

  return temperature_dimensional;
}


auto
temperature_phase
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::angular_frequency > const w,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> units::quantity< units::si::plane_angle >
{
  assert( x.value() >= 0 ) ;
  assert( w.value() != 0 ) ;

  using namespace units;
  
  auto const I_dummy = quantity< heat_flux >::from_value(1);
  
  auto const T_cmplx =
  complex_temperature( x, w, I_dummy, slab, boundary_condition, rear ) ;
  
  auto const phase = -arg( T_cmplx ) - M_PI_2 * radians ;
  
  return phase;
}

auto
temperature_amplitude
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> units::quantity< units::si::temperature >
{
  assert( x.value() > 0 ) ;
  assert( w.value() != 0 ) ;
  assert( I_t.value() != 0 ) ;

  using units::quantity;
  using units::si::length;
  
  auto const T_cmplx =
  complex_temperature( x, w, I_t, slab, boundary_condition, rear ) ;
  
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
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> units::quantity< units::si::temperature, std::complex<double > >
{
  assert( x.value() >= 0 ) ;
  assert( w.value() != 0 ) ;
  assert( I_t.value() > 0 ) ;

  using units::quantity;
  using units::si::temperature;

  auto const L = slab.characteristic_length;
  auto const alpha = slab.get_diffusivity();
  auto const k = slab.k;

  auto const theta_complex =
  neumann_and_direchlet_BC( x , w , L, alpha, boundary_condition, rear ) ;

  auto const deltaT = ( I_t * L ) / k ;
  
  auto const temperature_dimensional = theta_complex * deltaT ;
  
  return temperature_dimensional;
}

auto nondimensional_x
(
  units::quantity< units::si::length > const x,
  units::quantity< units::si::length > const L
) -> units::quantity< units::si::dimensionless >
{
  return x / L;
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
 
auto evaluate_based_on_bc
(
  units::quantity< units::si::dimensionless, double> const x_non ,
  units::quantity< units::si::dimensionless, std::complex< double > > const Kappa ,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear_condition
)
-> units::quantity< units::si::dimensionless, std::complex< double > >
{
  using math::differential::waveEquation::analytical_solution_10;
  using math::differential::waveEquation::analytical_solution_11;
  using math::differential::waveEquation::analytical_solution_00;
  using namespace units;
  auto s_x_value = std::complex<double>();
  

  switch ( boundary_condition )
  {
    case back_boundary_condition::adiabatic:
    {
      s_x_value = analytical_solution_00( x_non.value(), Kappa.value() );
      break;
    }
    case back_boundary_condition::T_base:
    {
      s_x_value = analytical_solution_10( x_non.value(), Kappa.value() );
      break;
    }
    case back_boundary_condition::T_unknown:
    {
      auto const phi = rear_condition.second.value() ;
      auto const T1 = rear_condition.first.value() ;
      s_x_value = analytical_solution_11( x_non.value(), Kappa.value(), T1,phi);
      break;
    }
    default:
      throw;
  }
  
  auto const s_x = quantity< dimensionless, std::complex<double>>( s_x_value );
  return s_x;
}
 
auto neumann_and_direchlet_BC(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::length > const characteristic_length,
  units::quantity< units::si::thermal_diffusivity > const alpha,
  enum back_boundary_condition const boundary_condition  ,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >
{
  // eq:  T''(x) + ( ( sqrt( i * w ) )^2 ) T(x) == 0
  // BC:  T'(0)   == - 1
  // BC:  T(L)  == 0

  assert( x.value() >= 0 ) ;
  assert( characteristic_length.value() > 0 ) ;
  assert( alpha.value() != 0 ) ;
  assert( w.value() != 0 ) ;

  using std::complex;

  using units::sqrt;
  using units::quantity;
  using units::si::dimensionless;


  auto const i_imag = complex< double >( 0, 1 ) ;
  
  auto const L = characteristic_length ;
    
  auto const w_non = nondimensional_omega( w, L, alpha ) ;
  auto const i_non = quantity< dimensionless, complex< double > >( i_imag ) ;
  auto const Kappa = sqrt( i_non * w_non ) ;
  
  auto const x_non = x / L ;
  
  auto const s_x = evaluate_based_on_bc( x_non, Kappa,  boundary_condition, rear );

  return s_x;
}



} // namespace slab
  
} // namespace model
  
} // namespace thermal
