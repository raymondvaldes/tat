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

auto
surface_temperature_amplitude
(
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > L_c,
  units::quantity< units::si::thermal_diffusivity > alpha,
  units::quantity< units::si::heat_flux > I_t,
  units::quantity< units::si::thermal_conductivity > k
)
noexcept -> units::quantity< units::si::temperature >;

auto
surface_temperature_phase
(
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > L_c,
  units::quantity< units::si::thermal_diffusivity > alpha,
  units::quantity< units::si::heat_flux > I_t,
  units::quantity< units::si::thermal_conductivity > k
)
noexcept -> units::quantity< units::si::plane_angle >;


auto
complex_surface_temperature
(
  units::quantity< units::si::angular_frequency > w,
  units::quantity< units::si::length > characteristic_length,
  units::quantity< units::si::thermal_diffusivity > alpha,
  units::quantity< units::si::heat_flux > I_t,
  units::quantity< units::si::thermal_conductivity > k
)
noexcept -> units::quantity< units::si::temperature, std::complex<double > >;


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
noexcept -> units::quantity< units::si::plane_angle >;

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
noexcept -> units::quantity< units::si::temperature >;

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
