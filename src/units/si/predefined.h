//
//  length.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__length__
#define __tat__length__

#include <boost/units/systems/si.hpp>
#include <boost/units/systems/temperature/celsius.hpp>
#include <boost/units/systems/temperature/fahrenheit.hpp>

#include "units/physical_dimensions.h"
#include "units/systems/si/base.h"
#include "units/si/prefixes.h"
#include "units/quantity.h"


namespace units {

namespace celsius {

  using boost::units::celsius::temperature;

} // namespace celsius

namespace fahrenheit {

  using boost::units::fahrenheit::temperature;
  
} // namespace fahrenheit


inline namespace si {

//Dimensions
using length        = boost::units::si::length;
using mass_density  = boost::units::si::mass_density;
using mass          = boost::units::si::mass;
using kinematic_viscosity = boost::units::si::kinematic_viscosity;
using dynamic_viscosity = boost::units::si::dynamic_viscosity;
using acceleration = boost::units::si::acceleration;

typedef boost::units::si::temperature         temperature;
typedef boost::units::si::power               power;
typedef boost::units::si::plane_angle         plane_angle;
typedef boost::units::si::solid_angle         solid_angle;
typedef boost::units::si::electric_potential  electric_potential;
typedef boost::units::si::dimensionless       dimensionless ;
typedef boost::units::si::velocity            velocity;
typedef boost::units::si::area                area;
typedef boost::units::si::volume              volume;
typedef boost::units::si::time                time;
typedef boost::units::si::frequency           frequency;
typedef boost::units::si::angular_velocity    angular_velocity;
typedef angular_velocity                      angular_frequency;
typedef boost::units::si::pressure            pressure;
typedef boost::units::si::wavenumber          wavenumber;
typedef boost::units::si::conductivity        electrical_conductivity;

/// Add dimensions to the SI system
  using heat_flux =
    unit< heat_flux_dimension , si::system>;
  
  using thermal_conductivity =
    unit< thermal_conductivity_dimension , si::system>;
  
  using thermal_diffusivity =
    unit< thermal_diffusivity_dimension , si::system >;
  
  using volumetric_thermal_expansion_coefficient =
    unit< volumetric_thermal_expansion_coefficient_dimension, si::system > ;
  
  using volumetric_heat_capacity =
    unit< volumetric_heat_capacity_dimension, si::system > ;
  

  using Archimedes_number = dimensionless;
  using Bingham_number = dimensionless;
  using Biot_number = dimensionless;
  using Blake_number = dimensionless;
  using Bodenstein_number = dimensionless;
  using Brinkman_number = dimensionless;
  using Capillary_number = dimensionless;
  
  using Cauchy_number = dimensionless;
  using Cavitation_number = dimensionless;
  using Coefficient_of_Frication = dimensionless;
  using Condensation_number = dimensionless;

  using Dean_number = dimensionless;
  using Drag_coefficient = dimensionless;
  using Eckert_number = dimensionless;
  using Elasticity_number = dimensionless;

  using Etovos_number = dimensionless;
  using Euler_coefficient = dimensionless;
  using Fourier_number = dimensionless;
  using Frictio_factor = dimensionless;

  using Froude_number = dimensionless;
  using Galileo_number = dimensionless;
  using Gratz_number = dimensionless;
  using Grashof_number = dimensionless;

  using Colburn_j_factor_h = dimensionless;
  using Colburn_j_factor_m = dimensionless;
  using Hodgson_number = dimensionless;
  using Jakob_number = dimensionless;
  
  using Knudsen_number = dimensionless;
  using Lewis_number = dimensionless;
  using Mach_number = dimensionless;
  using Nusselt_number = dimensionless;
  
  using Ohnesorge_number = dimensionless;
  using Peclet_number = dimensionless;
  using Peclet_number_mass_transfer = dimensionless;
  using Pipeline_parameter = dimensionless;

  using Power_number = dimensionless;
  using Prandtl_number = dimensionless;
  using Rayleigh_number = dimensionless;
  using Reynolds_number = dimensionless;
  using Richardson_number = dimensionless;
  
  using Schmidt_number = dimensionless;
  using Sherwood_number = dimensionless;
  using Stanton_number = dimensionless;
  using Stanton_number_mass = dimensionless;

  using Strouhal_number = dimensionless;
  using Weber_number = dimensionless;




//Units
using boost::units::si::radian_per_second;
using boost::units::si::radians_per_second;

using boost::units::si::radians;
using boost::units::si::radian;

using boost::units::si::meters;
using boost::units::si::meter;
using boost::units::si::second;
using boost::units::si::seconds;

using boost::units::si::watts;
using boost::units::si::watt;
using boost::units::si::volts;
using boost::units::si::kelvin;

using namespace boost::units::celsius;
using namespace boost::units::fahrenheit;

using boost::units::si::hertz;

//more stuff
static auto const nanometers = nano * meters;
static auto const micrometers = micro * meters;
static auto const millimeters = milli * meters;
static auto const centimeters = centi * meters;
static auto const kilometers = kilo * meters;

static auto const microvolts = micro * volts;
static auto const millivolts = milli * volts;
static auto const kilovolts = kilo * volts;
static auto const megavolts = mega * volts;
static auto const gigavolts = giga * volts;


  
//BOOST_UNITS_STATIC_CONSTANT( millimeters, length );


using boost::units::si::square_meter;
static auto const square_millimeters = millimeters * millimeters ;

// nameless units
auto static const thermal_conductivity_units = watts / ( meter * kelvin ) ;
auto static const thermal_diffusivity_units = meter * meter / second ;
auto static const kinematic_viscosity_units = meter * meter / second ;
auto static const volumetric_thermal_expansion_coefficient_units = meter / kelvin / meter ;

} //namespace si




using boost::units::absolute;
using boost::units::conversion_helper;

typedef conversion_helper<
        quantity<absolute<fahrenheit::temperature> >,
        quantity<absolute<boost::units::si::temperature> > >
        absolute_conv_F_to_K_type;
  
typedef conversion_helper<
        quantity<fahrenheit::temperature>,
        quantity<si::temperature> >
        relative_conv_F_to_K_type;

typedef conversion_helper<
        quantity<absolute<celsius::temperature> >,
        quantity<absolute<si::temperature> > >
        absolute_conv_C_to_K_type;
  
typedef conversion_helper<
        quantity<celsius::temperature>,
        quantity<si::temperature> >
        relative_conv_C_to_K_type;


namespace celsius{
  using degrees = absolute< celsius::temperature > ;
}

namespace fahrenheit{
  using degrees = absolute< fahrenheit::temperature > ;
}


} //namespace units

#endif /* defined(__tat__length__) */
