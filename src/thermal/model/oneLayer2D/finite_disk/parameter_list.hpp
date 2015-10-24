//
//  parameter_list.hpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef parameter_list_hpp_1344523423462445gwefg
#define parameter_list_hpp_1344523423462445gwefg

#include <vector>

namespace thermal { 
namespace model {
namespace oneLayer2D { 
namespace finite_disk {

enum class Parameter{
  thermal_diffusivity,
  laser_radius,
  specimen_radius,
  detector_radius,
  rc_filter
};

using Parameters = std::vector< Parameter >;


} } } }

#endif /* parameter_list_hpp */
