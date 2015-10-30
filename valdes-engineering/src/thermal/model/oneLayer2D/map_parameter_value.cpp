//
//  map_parameter_value.cpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "map_parameter_value.h"

namespace thermal{
namespace model{
namespace oneLayer2D{

auto map_parameter_value
(
  Parameter const parameter,
  slab::Slab const & slab,
  Optics const & optics
)
noexcept -> double
{
  auto v = double();
    
  switch( parameter ) {
    case Parameter::detector_radius : {
      v = optics.view_radius.value(); break;
    }
    case Parameter::laser_radius : {
      v = optics.laser_radius.value(); break;
    }
    case Parameter::disk_radius : {
      v = slab.radius().value(); break;
    }
    case Parameter::disk_thermal_diffusivity : {
      v = slab.thermal_diffusivity().value(); break;
    }
    case Parameter::rc_filter : {
      v = optics.filter_constant.value(); break;
    }
    case Parameter::disk_thermal_conductivity : {
      v = slab.thermal_diffusivity().value(); break;
    }
    case Parameter::detector_offset : {
      v = optics.detector_offset.value(); break;
    }
 
  }
  return v;
}

}}}
