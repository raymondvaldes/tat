//
//  slab.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>
#include <complex>

#include "thermal/model/slab/slab.h"

namespace thermal {

namespace model {

namespace slab {





auto
surface_temperature_amplitude
(
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > L_c,
  units::quantity< units::si::thermal_diffusivity > alpha,
  units::quantity< units::si::heat_flux > I_t,
  units::quantity< units::si::thermal_conductivity > k
)
noexcept -> units::quantity< units::si::temperature >
{
  using units::abs;
  
  auto const Tsurface = complex_surface_temperature( w, L_c, alpha, I_t, k ) ;
  
  auto const amplitude = abs( Tsurface ) ;
  
  return amplitude ;
}

auto
surface_temperature_phase
(
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > L_c,
  units::quantity< units::si::thermal_diffusivity > alpha,
  units::quantity< units::si::heat_flux > I_t,
  units::quantity< units::si::thermal_conductivity > k
)
noexcept -> units::quantity< units::si::plane_angle >
{
  using units::arg;
  
  auto const Tsurface = complex_surface_temperature( w, L_c, alpha, I_t, k ) ;
  
  auto const phase = arg( Tsurface ) ;
  
  return phase;
}

auto
real_transient_temperature()
{

}

//auto
//real_total_temperature()
//{
//
//}




auto
complex_surface_temperature
(
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > characteristic_length,
  units::quantity< units::si::thermal_diffusivity > alpha,
  units::quantity< units::si::heat_flux > I_t,
  units::quantity< units::si::thermal_conductivity > k
)
noexcept -> units::quantity< units::si::temperature, std::complex<double > >
{
  using units::quantity;
  using units::si::length;

  auto const x_surface = quantity< length >::from_value( 0 );
  
  auto const temperature_dimensional =
    complex_temperature( x_surface, w, characteristic_length, alpha, I_t, k );

  return temperature_dimensional;
}


auto
temperature_phase
(
  units::quantity< units::si::length> x ,
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > L_c,
  units::quantity< units::si::thermal_diffusivity > alpha,
  units::quantity< units::si::heat_flux > I_t,
  units::quantity< units::si::thermal_conductivity > k
)
noexcept -> units::quantity< units::si::plane_angle >
{
  using units::quantity;
  using units::si::length;
  
  auto const T_cmplx = complex_temperature( x, w, L_c, alpha, I_t, k ) ;
  
  using units::arg;
  auto const phase =arg( T_cmplx ) ;
  
  return phase;
}

auto
temperature_amplitude
(
  units::quantity< units::si::length> x ,
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > L_c,
  units::quantity< units::si::thermal_diffusivity > alpha,
  units::quantity< units::si::heat_flux > I_t,
  units::quantity< units::si::thermal_conductivity > k
)
noexcept -> units::quantity< units::si::temperature >
{
  using units::quantity;
  using units::si::length;
  
  auto const T_cmplx = complex_temperature( x, w, L_c, alpha, I_t, k ) ;
  
  using units::abs;
  auto const amplitude = abs( T_cmplx ) ;
  
  return amplitude;
}


auto
complex_temperature
(
  units::quantity< units::si::length> x ,
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > characteristic_length,
  units::quantity< units::si::thermal_diffusivity > alpha,
  units::quantity< units::si::heat_flux > I_t,
  units::quantity< units::si::thermal_conductivity > k
)
noexcept -> units::quantity< units::si::temperature, std::complex<double > >
{
  using units::quantity;
  using units::si::temperature;
  using std::complex;

  auto const theta_complex =
    neumann_and_direchlet_BC( x , w , characteristic_length, alpha ) ;

  auto const deltaT = I_t * characteristic_length / k ;
  
  auto const temperature_dimensional = theta_complex * deltaT ;
  
  return temperature_dimensional;
}

auto neumann_and_direchlet_BC(
  units::quantity< units::si::length> x ,
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > characteristic_length,
  units::quantity< units::si::thermal_diffusivity > alpha
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >
{
  // eq:  T''(x) + ( ( sqrt( i * w ) )^2 ) T(x) == 0
  // BC:  T'(0)   == - 1
  // BC:  T(1)  == 0

  assert( x.value() > 0 ) ;
  assert( characteristic_length.value() > 0 ) ;
  assert( alpha.value() > 0 ) ;
  assert( w.value() != 0 ) ;

  using std::complex;

  using units::pow;
  using units::sqrt;
  using units::quantity;
  using units::si::radians;
  using units::si::dimensionless;
  using math::differential::waveEquation::analytical_solution_10;

  auto const i_imag = complex< double >( 0, 1 ) ;
  
  auto const L = characteristic_length;
    
  auto const w_non = ( w * pow< 2 >( L ) / alpha ) / radians;
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
