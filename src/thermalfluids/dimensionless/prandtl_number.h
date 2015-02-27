//
//  prandtl_number.h
//  tat
//
//  Created by Raymond Valdes_New on 2/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_prandtl_number_h
#define tat_prandtl_number_h

#include "units.h"

namespace thermalfluids {

namespace dimensionless {

//Ratio of gravitational force to viscous force
auto
Archimedes_number( units::quantity< units::si::acceleration > const & gravitational_acceleration,
                   units::quantity< units::si::mass_density  > const & density_fluid,
                   units::quantity< units::si::mass_density  > const & density_body,
                   units::quantity< units::si::length  > const & characteristic_length,
                   units::quantity< units::si::dynamic_viscosity  > const & fluid_viscosity  )
noexcept -> units::quantity< units::si::Archimedes_number >
{
  using units::pow;
  
  auto const g      = gravitational_acceleration;
  auto const L      = characteristic_length;
  auto const rho_f  = density_fluid;
  auto const rho    = density_body;
  auto const mu     = fluid_viscosity;

  auto const external_forces = g * pow< 3 >( L ) * rho_f * ( rho - rho_f ) ;
  
  auto const internal_viscous_forces = pow< 2 >( mu ) ;
  
  auto const Ar = external_forces / internal_viscous_forces ;
  
  return Ar;
}

auto
Archimedes_number( units::quantity< units::si::Richardson_number > const & Ri,
                   units::quantity< units::si::Reynolds_number  > const & Re )
noexcept -> units::quantity< units::si::Archimedes_number >
{
  using units::pow;

  auto const Ar = Ri * pow< 2 >( Re ) ;
  
  return Ar;
}



auto
Richardson_number( units::quantity< units::si::acceleration > const & gravitational_acceleration,
                   units::quantity< units::si::volumetric_thermal_expansion_coefficient > const & thermal_expansion_coefficient,
                   units::quantity< units::absolute< units::si::temperature > > const & temperature_wall,
                   units::quantity< units::absolute< units::si::temperature > > const & temperature_inf,
                   units::quantity< units::si::length  > const & characteristic_length,
                   units::quantity< units::si::velocity  > const & characteristic_velocity  )
noexcept -> units::quantity< units::si::Richardson_number >
{
  using units::pow;
  
  auto const g      = gravitational_acceleration;
  auto const beta   = thermal_expansion_coefficient;
  auto const T      = temperature_wall;
  auto const T_inf  = temperature_inf;
  auto const L      = characteristic_length;
  auto const V      = characteristic_velocity;

  auto const bouyancy_terms = g * beta * ( T - T_inf ) * L ;
  
  auto const flow_gradient_terms = pow< 2 >( V ) ;
  
  auto const Ri = bouyancy_terms / flow_gradient_terms ;
  return Ri;
}

auto
Richardson_number(  units::quantity< units::si::Grashof_number > const & Gr,
                    units::quantity< units::si::Reynolds_number > const & Re)
noexcept -> units::quantity< units::si::Richardson_number>
{
  using units::pow;

  auto const Ri = Gr / pow< 2 >( Re ) ;
  return Ri;
}

auto
Reynolds_number( units::quantity< units::si::velocity > const & fluid_velocity,
                 units::quantity< units::si::length > const & characteristic_length,
                 units::quantity< units::si::kinematic_viscosity > const & kinematic_viscosity
                     )
noexcept -> units::quantity< units::si::Reynolds_number >
{
  using units::pow;
  
  auto const v    = fluid_velocity;
  auto const L    = characteristic_length;
  auto const nu   = kinematic_viscosity;

  auto const intertial_forces = v * L ;
  
  auto const viscous_forces = nu;
  
  auto const Re = intertial_forces / viscous_forces ;
  return Re;
}

auto
Reynolds_number( units::quantity< units::si::velocity > const & fluid_velocity,
                 units::quantity< units::si::length > const & characteristic_length,
                 units::quantity< units::si::dynamic_viscosity  > const & fluid_viscosity,
                 units::quantity< units::si::mass_density > const & fluid_density
                     )
noexcept -> units::quantity< units::si::Reynolds_number >
{

  auto const v = fluid_velocity;
  auto const L = characteristic_length;
  auto const kinematic_viscosity = fluid_viscosity / fluid_density;
  
  auto const Re = Reynolds_number( v, L, kinematic_viscosity ) ;
  return Re;
}


auto
Grashof_number( units::quantity< units::si::acceleration > const & gravitational_acceleration,
                   units::quantity< units::si::volumetric_thermal_expansion_coefficient > const & thermal_expansion_coefficient,
                   units::quantity< units::absolute< units::si::temperature > > const & temperature_wall,
                   units::quantity< units::absolute< units::si::temperature > > const & temperature_inf,
                   units::quantity< units::si::length  > const & characteristic_length,
                   units::quantity< units::si::kinematic_viscosity > const & kinematic_viscosity  )
noexcept -> units::quantity< units::si::Grashof_number >
{
  using units::pow;
  
  auto const g      = gravitational_acceleration;
  auto const beta   = thermal_expansion_coefficient;
  auto const T      = temperature_wall;
  auto const T_inf  = temperature_inf;
  auto const L      = characteristic_length;
  auto const nu   = kinematic_viscosity;

  auto const bouyancy_forces = g * beta * ( T - T_inf ) * pow< 3 >( L ) ;

  auto const viscous_forces = pow< 2 >( nu ) ;
  
  auto const Gr = bouyancy_forces / viscous_forces ;
  return Gr;
}





//Ratio of momentum and thermal diffusivities
auto
Prandtl_number( units::quantity< units::si::kinematic_viscosity > const & viscousDiffusion,
                units::quantity< units::si::thermal_diffusivity  > const & thermalDiffusion )
noexcept -> units::quantity< units::si::Prandtl_number >
{  
  auto const Pr = viscousDiffusion / thermalDiffusion ;
  return Pr;
}


//steps to creating my functions that return dimensionless fluid mechanics numbers
//1) create the dimensionless types in the units::namespace
//2) make a list of all the dimensions that need to be defined
//3) define those dimnesions
//4) define the functions
  

} // namespace dimensionless

} // namespace thermalfluids

#endif
