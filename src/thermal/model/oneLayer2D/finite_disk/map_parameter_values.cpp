//
//  scale_parameters.cpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "map_parameter_values.hpp"
#include "algorithm/algorithm.h"
#include <utility>

namespace thermal { 
namespace model {
namespace oneLayer2D { 
namespace finite_disk {

using algorithm::for_each;
using std::make_pair;

auto map_parameter_values
(
  Parameters const & parameters,
  Disk const & disk,
  Optics const & optics
)
noexcept -> Map_parameter_values
{
  auto m = Map_parameter_values();

  auto const get_value = [ &disk, &optics ]( auto const p ) noexcept
  {
    auto v  = double();
    
    switch( p ) {
      case Parameter::detector_radius : {
        v = optics.view_radius.value(); break;
      }
      case Parameter::laser_radius : {
        v = optics.laser_radius.value(); break;
      }
      case Parameter::specimen_radius : {
        v = disk.radius().value(); break;
      }
      case Parameter::thermal_diffusivity : {
        v = disk.thermal_diffusivity().value(); break;
      }
      case Parameter::rc_filter : {
        v = optics.filter_constant.value(); break;
      }
    }
  
    return v;
  };


  for_each( parameters, [&m, &get_value]( auto const p ) noexcept {
    m.emplace( make_pair( p, get_value( p ) ) );
  } );

  return m;
}


} } } }
