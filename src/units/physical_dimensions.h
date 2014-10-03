//
//  physical_dimensions.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_physical_dimensions_h
#define tat_physical_dimensions_h

#include <boost/units/physical_dimensions.hpp>
#include <boost/type.hpp>

#include <boost/units/physical_dimensions/time.hpp>
#include <boost/units/physical_dimensions/mass.hpp>
#include <boost/units/physical_dimensions/temperature.hpp>
#include <boost/units/physical_dimensions/length.hpp>
#include <boost/units/physical_dimensions/power.hpp>
#include <boost/units/physical_dimensions/solid_angle.hpp>
#include <boost/units/physical_dimensions/electric_potential.hpp>

namespace units {
  
  
  typedef boost::units::time_base_dimension time_base_dimension;
  
  typedef boost::units::mass_base_dimension mass_base_dimension;
  
  typedef boost::units::temperature_base_dimension temperature_base_dimension;
  
  typedef boost::units::length_base_dimension length_base_dimension;
  
  
  typedef boost::units::solid_angle_dimension solid_angle_dimension;
  
  typedef boost::units::power_dimension power_dimension;

  typedef boost::units::energy_dimension energy_dimension;
  
  typedef boost::units::electric_potential_dimension electric_potential_dimension;
  
  
  using boost::units::derived_dimension;
  
  typedef
  derived_dimension< power_dimension , 1 >::type
  thermal_emission_dimension;
  
//  typedef
//  derived_dimension<  mass_base_dimension,2,
//                      solid_angle_dimension,1>::type
//  thermal_emission_dimension2;
  
//  using boost::units::derived_dimension;
//  typedef derived_dimension< power_dimension,1,
//                             solid_angle_dimension,-1,
//                             time_base_dimension,-3>::type thermal_emission_dimension;
  


  



}


#endif
