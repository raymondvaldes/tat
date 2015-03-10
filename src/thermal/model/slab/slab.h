//
//  slab.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__slab__
#define __tat__slab__

#include <cassert>
#include <complex>
#include "math/differential/waveEquation/analytical.h"
#include "units.h"

namespace thermal {

namespace model {

namespace slab {


struct Slab
{
  units::quantity< units::si::length > characteristic_length;
  units::quantity< units::si::thermal_diffusivity > alpha;
  units::quantity< units::si::thermal_conductivity > k;

  Slab(
    units::quantity< units::si::length > const & characteristic_length_in,
    units::quantity< units::si::thermal_diffusivity > const & alpha_in,
    units::quantity< units::si::thermal_conductivity > const & k_in
  ) :characteristic_length(characteristic_length_in), alpha(alpha_in), k(k_in)
  {};
  
};


auto
real_transient_temperature
(
  units::quantity< units::si::length > x ,
  units::quantity< units::si::time > t ,
  units::quantity< units::si::angular_frequency > w ,
  units::quantity< units::si::heat_flux > I_t ,
  Slab const & slab
)
noexcept -> units::quantity< units::si::temperature >;


auto
exponentialModulator_nondimensional
(
  units::quantity<units::si::dimensionless > const & omega_non,
  units::quantity<units::si::dimensionless > const & time_non
)
-> units::quantity< units::si::dimensionless, std::complex< double > >;

auto
surface_temperature_amplitude
(
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::heat_flux > I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::temperature >;

auto
surface_temperature_phase
(
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::heat_flux > I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::plane_angle >;


auto
complex_surface_temperature
(
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::heat_flux > I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::temperature, std::complex<double > >;

auto
exponentialModulator_nondimensional
(
  units::quantity<units::si::dimensionless > const & omega_non,
  units::quantity<units::si::dimensionless > const & time_non
)
-> units::quantity< units::si::dimensionless, std::complex< double > >;

auto
temperature_phase
(
  units::quantity< units::si::length> x ,
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::heat_flux > I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::plane_angle >;

auto
temperature_amplitude
(
  units::quantity< units::si::length> x ,
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::heat_flux > I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::temperature >;

auto nondimensional_omega
(
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > L,
  units::quantity< units::si::thermal_diffusivity > alpha
)
noexcept -> units::quantity< units::si::dimensionless>;

auto nondimensional_time
(
  units::quantity< units::si::time > time,
  units::quantity< units::si::length > L,
  units::quantity< units::si::thermal_diffusivity > alpha
)
noexcept -> units::quantity< units::si::dimensionless>;

auto
complex_temperature
(
  units::quantity< units::si::length> x ,
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::heat_flux > I_t,
  Slab const & slab
)
noexcept -> units::quantity< units::si::temperature, std::complex<double > >;

auto neumann_and_direchlet_BC(
  units::quantity< units::si::length> x ,
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > characteristic_length,
  units::quantity< units::si::thermal_diffusivity > alpha
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >;

  
} // namespace slab
  
} // namespace model
  
} // namespace thermal

#endif /* defined(__tat__slab__) */
