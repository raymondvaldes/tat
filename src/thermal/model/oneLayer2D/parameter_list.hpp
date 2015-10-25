//
//  parameter_list.hpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef parameter_list_h_1025152f234f3v
#define parameter_list_h_1025152f234f3v

#include <vector>


namespace thermal{
namespace model{
namespace oneLayer2D{

enum class Parameter{
  thermal_diffusivity,
  laser_radius,
  specimen_radius,
  detector_radius,
  rc_filter
};

using Parameters = std::vector< Parameter >;


}}}

#endif /* parameter_list_h */
