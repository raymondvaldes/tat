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

#include <boost/units/physical_dimensions/time.hpp>
#include <boost/units/physical_dimensions/mass.hpp>
#include <boost/units/physical_dimensions/temperature.hpp>
#include <boost/units/physical_dimensions/length.hpp>
#include <boost/units/physical_dimensions/power.hpp>
#include <boost/units/physical_dimensions/solid_angle.hpp>
#include <boost/units/physical_dimensions/electric_potential.hpp>
#include <boost/units/physical_dimensions/temperature.hpp>
#include <boost/units/physical_dimensions/energy.hpp>
#include <boost/units/dimensionless_unit.hpp>
#include <boost/units/physical_dimensions/amount.hpp>

namespace units {

  typedef boost::units::temperature_dimension temperature_dimension;
  
  typedef boost::units::time_dimension time_dimension;
  
  typedef boost::units::mass_base_dimension mass_base_dimension;
  
  typedef boost::units::temperature_base_dimension temperature_base_dimension;
  
  typedef boost::units::length_base_dimension length_base_dimension;
  
  typedef boost::units::solid_angle_dimension solid_angle_dimension;
  
  typedef boost::units::power_dimension power_dimension;

  typedef boost::units::energy_dimension energy_dimension;
  
  typedef boost::units::electric_potential_dimension electric_potential_dimension;
  
  typedef boost::units::solid_angle_base_dimension solid_angle_base_dimension;
  
  typedef boost::units::frequency_dimension frequency_dimension;
  
  typedef boost::units::length_dimension length_dimension;
  
  typedef boost::units::dimensionless_type dimensionless_type;
  
  typedef boost::units::amount_dimension amount_dimension;
  
} // namespace units


#endif
