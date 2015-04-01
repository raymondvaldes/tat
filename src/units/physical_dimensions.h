//
//  physical_dimensions.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_physical_dimensions_h
#define tat_physical_dimensions_h

#include <boost/units/operators.hpp>
#include <boost/units/physical_dimensions.hpp>
#include <boost/type.hpp>
#include <boost/units/dimensionless_unit.hpp>
#include <boost/units/derived_dimension.hpp>

//namespace that holds units
namespace units {

// dimensions that already exist in the boost units library

  typedef boost::units::temperature_dimension temperature_dimension;
  typedef boost::units::temperature_base_dimension temperature_base_dimension;

  typedef boost::units::length_dimension length_dimension;  
  typedef boost::units::length_base_dimension length_base_dimension;
  
  typedef boost::units::time_dimension time_dimension;
  typedef boost::units::time_base_dimension time_base_dimension;
  
  typedef boost::units::mass_dimension  mass_dimension;
  typedef boost::units::mass_base_dimension mass_base_dimension;
  
  typedef boost::units::plane_angle_dimension plane_angle_dimension;
  typedef boost::units::plane_angle_base_dimension plane_angle_base_dimension;
  
  typedef boost::units::solid_angle_dimension solid_angle_dimension;
  typedef boost::units::solid_angle_base_dimension solid_angle_base_dimension;

  typedef boost::units::amount_dimension amount_dimension;
  typedef boost::units::amount_base_dimension amount_base_dimension;
  
  typedef boost::units::power_dimension power_dimension;

  typedef boost::units::energy_dimension energy_dimension;
  
  typedef boost::units::velocity_dimension velocity_dimension;
  
  typedef boost::units::electric_potential_dimension electric_potential_dimension;
  
  typedef boost::units::frequency_dimension frequency_dimension;
  
  typedef boost::units::dimensionless_type dimensionless_type;

  typedef boost::units::specific_volume_dimension specific_volume_dimension;
  
  typedef boost::units::specific_heat_capacity_dimension specific_heat_capacity_dimension;
  
  typedef boost::units::specific_energy_dimension specific_energy_dimension;
  
  typedef boost::units::mass_density_dimension mass_density_dimension;
  
  typedef boost::units::acceleration_dimension acceleration_dimension;
  

// dimensions that I need are not yet defined
  using boost::units::derived_dimension;


/// derived dimensions:
  typedef derived_dimension<  mass_base_dimension,1,
                              length_base_dimension, 1,
                              time_base_dimension, -3,
                              temperature_base_dimension, -1>::type
                              thermal_conductivity_dimension;

  typedef derived_dimension<  mass_base_dimension,1,
                              length_base_dimension, -1,
                              time_base_dimension, -2,
                              temperature_base_dimension, -1>::type
                              volumetric_heat_capacity_dimension;

  typedef derived_dimension<  mass_base_dimension,1,
                              time_base_dimension, -3>::type
                              heat_flux_dimension;
                              
  typedef derived_dimension<  length_base_dimension, 2,
                              time_base_dimension, -1>::type
                              thermal_diffusivity_dimension;


  typedef derived_dimension<  temperature_base_dimension, -1 >::type
                              volumetric_thermal_expansion_coefficient_dimension;

  typedef derived_dimension< dimensionless_type, 1 >::type Archimedes_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Arrhenius_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Bingham_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Biot_number;
  
  typedef derived_dimension< dimensionless_type, 1 >::type Blake_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Bodenstein_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Brinkman_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Capillary_number;

  typedef derived_dimension< dimensionless_type, 1 >::type Cauchy_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Cavitation_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Coefficient_of_Frication;
  typedef derived_dimension< dimensionless_type, 1 >::type Condensation_number;

  typedef derived_dimension< dimensionless_type, 1 >::type Dean_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Drag_coefficient;
  typedef derived_dimension< dimensionless_type, 1 >::type Eckert_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Elasticity_number;

  typedef derived_dimension< dimensionless_type, 1 >::type Etovos_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Euler_coefficient;
  typedef derived_dimension< dimensionless_type, 1 >::type Fourier_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Frictio_factor;

  typedef derived_dimension< dimensionless_type, 1 >::type Froude_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Galileo_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Gratz_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Grashof_number;

  typedef derived_dimension< dimensionless_type, 1 >::type Colburn_j_factor_h;
  typedef derived_dimension< dimensionless_type, 1 >::type Colburn_j_factor_m;
  typedef derived_dimension< dimensionless_type, 1 >::type Hodgson_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Jakob_number;
  
  typedef derived_dimension< dimensionless_type, 1 >::type Knudsen_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Lewis_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Mach_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Nusselt_number;
  
  typedef derived_dimension< dimensionless_type, 1 >::type Ohnesorge_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Peclet_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Peclet_number_mass_transfer;
  typedef derived_dimension< dimensionless_type, 1 >::type Pipeline_parameter;

  typedef derived_dimension< dimensionless_type, 1 >::type Power_number_dimension;
  typedef derived_dimension< dimensionless_type, 1 >::type Prandtl_number_dimension;
  typedef derived_dimension< dimensionless_type, 1 >::type Rayleigh_number_dimension;
  typedef derived_dimension< dimensionless_type, 1 >::type Reynolds_number_dimension;
  
  typedef derived_dimension< dimensionless_type, 1 >::type Schmidt_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Sherwood_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Stanton_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Stanton_number_mass;

  typedef derived_dimension< dimensionless_type, 1 >::type Strouhal_number;
  typedef derived_dimension< dimensionless_type, 1 >::type Weber_number;
  
  

  
  
  
} // namespace units


#endif
