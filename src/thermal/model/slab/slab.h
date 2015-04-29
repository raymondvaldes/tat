//
//  slab.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__slab__
#define __tat__slab__

#include <vector>
#include <cassert>
#include <complex>

#include "math/differential/waveEquation/analytical.h"
#include "units.h"

namespace thermal {

namespace model {

namespace slab {


enum class back_boundary_condition{ T_base, adiabatic, T_unknown };

struct Slab
{
private:

public:
  units::quantity< units::si::length > characteristic_length;
  units::quantity< units::si::thermal_conductivity > k;
  units::quantity< units::si::volumetric_heat_capacity> rhoCp;

  Slab(
    units::quantity< units::si::length > const characteristic_length_in,
    units::quantity< units::si::thermal_diffusivity > const alpha_in,
    units::quantity< units::si::thermal_conductivity > const k_in
  );
  
  Slab(
    units::quantity< units::si::length > const characteristic_length_in,
    units::quantity< units::si::thermal_diffusivity > const alpha_in,
    units::quantity< units::si::volumetric_heat_capacity > const rhoCp_in
  );
  
  Slab(
    units::quantity< units::si::length > const characteristic_length_in,
    units::quantity< units::si::thermal_conductivity > const k_in,
    units::quantity< units::si::volumetric_heat_capacity > const rhoCp_in
  );
  
  // getters
  auto get_conductivity( void ) const
  -> units::quantity< units::si::thermal_conductivity > ;
  
  auto get_volumetric_heatCapacity( void ) const
  -> units::quantity< units::si::volumetric_heat_capacity>;
  
  auto get_diffusivity(void ) const
  -> units::quantity< units::si::thermal_diffusivity >;
  
  auto get_effusivity( void ) const
  -> units::quantity< units::si::thermal_effusivity >;


  // setters
  auto set_effusivity_update_k_hold_rhoCp (
    units::quantity< units::si::thermal_effusivity > const & e
  ) -> void;
  
  auto set_effusivity_update_rhoCp_hold_k (
  units::quantity< units::si::thermal_effusivity > const & e
  ) -> void;

  
  auto set_diffusivity_update_k_hold_rhoCp (
    units::quantity< units::si::thermal_diffusivity > const & alpha_in
  ) -> void;
  
  auto set_diffusivity_update_rhoCp_hold_k (
  units::quantity< units::si::thermal_diffusivity > const & alpha_in
  ) -> void;
  
  auto set_conductivity(
    units::quantity< units::si::thermal_conductivity > const & k_in
  ) -> void;
  
  auto set_volumetric_heatCapacity(
    units::quantity< units::si::volumetric_heat_capacity> const & rhoCp_in
  ) -> void;
};

auto
surface_temperature_phases
(
  std::vector< units::quantity< units::si::dimensionless > > const & lthermals,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear=
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> std::vector < units::quantity< units::si::plane_angle > >;

auto
surface_temperature_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> std::vector < units::quantity< units::si::plane_angle > >;

auto
surface_temperature_amplitudes
(
  std::vector< units::quantity< units::si::dimensionless > > const & lthermals,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> std::vector < units::quantity< units::si::temperature > >;

auto
surface_temperature_amplitudes
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> std::vector < units::quantity< units::si::temperature > >;

auto
surface_temperature_amplitudes
(
  std::vector< units::quantity< units::si::angular_frequency > > const & omegas,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> std::vector < units::quantity< units::si::temperature > >;

auto
surface_temperature_phases
(
  std::vector< units::quantity< units::si::angular_frequency > > const & omegas,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> std::vector < units::quantity< units::si::plane_angle > >;

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
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> units::quantity< units::si::temperature >;

auto
exponentialModulator_nondimensional
(
  units::quantity<units::si::dimensionless > const omega_non,
  units::quantity<units::si::dimensionless > const time_non
)
-> units::quantity< units::si::dimensionless, std::complex< double > >;

auto
surface_temperature_amplitude
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> units::quantity< units::si::temperature >;

auto
surface_temperature_phase
(
  units::quantity< units::si::angular_frequency > const w,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> units::quantity< units::si::plane_angle >;


auto
complex_surface_temperature
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> units::quantity< units::si::temperature, std::complex<double > >;

auto
exponentialModulator_nondimensional
(
  units::quantity<units::si::dimensionless > const omega_non,
  units::quantity<units::si::dimensionless > const time_non
)
-> units::quantity< units::si::dimensionless, std::complex< double > >;

auto
temperature_phase
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::angular_frequency > const w,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> units::quantity< units::si::plane_angle >;

auto
temperature_amplitude
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> units::quantity< units::si::temperature >;

auto nondimensional_omega
(
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> units::quantity< units::si::dimensionless>;

auto nondimensional_time
(
  units::quantity< units::si::time > const time,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> units::quantity< units::si::dimensionless>;

auto
complex_temperature
(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::heat_flux > const I_t,
  Slab const & slab,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> units::quantity< units::si::temperature, std::complex<double > >;

auto evaluate_based_on_bc
(
  units::quantity< units::si::dimensionless, double> const x_non ,
  units::quantity< units::si::dimensionless, std::complex< double > > const Kappa ,
  enum back_boundary_condition const boundary_condition,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear_condition =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
-> units::quantity< units::si::dimensionless, std::complex< double > >;

auto neumann_and_direchlet_BC(
  units::quantity< units::si::length> const x ,
  units::quantity< units::si::angular_frequency > const w,
  units::quantity< units::si::length > const characteristic_length,
  units::quantity< units::si::thermal_diffusivity > const alpha,
  enum back_boundary_condition const boundary_condition  ,
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> > const & rear_condition =
  std::pair< units::quantity< units::si::dimensionless >,
            units::quantity<units::si::plane_angle> >()
)
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >;

auto nondimensional_x
(
  units::quantity< units::si::length > const x,
  units::quantity< units::si::length > const L
) -> units::quantity< units::si::dimensionless >;
  
} // namespace slab
  
} // namespace model
  
} // namespace thermal

#endif /* defined(__tat__slab__) */
