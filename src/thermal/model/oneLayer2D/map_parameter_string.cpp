//
//  map_parameter_string.cpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "map_parameter_string.hpp"
#include "units/cout/use_engineering_prefix.hpp"
#include <sstream>
#include <iostream>  

namespace thermal{
namespace model{
namespace oneLayer2D{

auto map_parameter_string
(
  Parameter const parameter,
  slab::Slab const & slab,
  Optics const & optics
)
noexcept -> std::string
{
  std::stringstream v;
  v << units::engineering_prefix;
  
  
  switch( parameter ) {
    case Parameter::detector_radius : {
      v << optics.view_radius; break;
    }
    case Parameter::laser_radius : {
      v << optics.laser_radius; break;
    }
    case Parameter::disk_radius : {
      v << slab.radius(); break;
    }
    case Parameter::disk_thermal_diffusivity : {
      v << slab.thermal_diffusivity(); break;
    }
    case Parameter::rc_filter : {
      v << optics.filter_constant; break;
    }
    case Parameter::disk_thermal_conductivity : {
      v << slab.thermal_diffusivity(); break;
    }
    case Parameter::detector_offset : {
      v << optics.detector_offset; break;
    }
 
  }
  
  return v.str();
}

}}}
