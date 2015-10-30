//
//  map_parameter_name.cpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "map_parameter_name.hpp"

namespace thermal{
namespace model{
namespace oneLayer2D{

auto map_parameter_name
(
  Parameter const parameter,
  slab::Slab const & slab,
  Optics const & optics
)
noexcept -> std::string
{
  auto v = std::string();
    
  switch( parameter ) {
    case Parameter::detector_radius : {
      v = "detector radius"; break;
    }
    case Parameter::laser_radius : {
      v = "laser radius"; break;
    }
    case Parameter::disk_radius : {
      v = "disk radius"; break;
    }
    case Parameter::disk_thermal_diffusivity : {
      v = "disk thermal diffusivity"; break;
    }
    case Parameter::rc_filter : {
      v = "phase RC Filter"; break;
    }
    case Parameter::disk_thermal_conductivity : {
      v = "disk thermal conductivity"; break;
    }
    case Parameter::detector_offset : {
      v = "detector offset"; break;
    }
 
  }
  return v;
}

}}}

