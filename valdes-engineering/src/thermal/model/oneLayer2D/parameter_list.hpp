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
#include <exception>
#include <set>

namespace thermal{
namespace model{
namespace oneLayer2D{



class Parameter_list_empty: public std::exception
{
  virtual const char* what() const throw()
  {
    return "The parameter list is empty.";
  }
};

class Parameter_list_is_invalid: public std::exception
{
  virtual const char* what() const throw()
  {
    return "A parameter is not valid";
  }
};

enum class Parameter{
  disk_thermal_diffusivity,
  disk_thermal_conductivity,
  disk_radius,
  
  laser_radius,

  detector_radius,
  detector_offset,

  rc_filter
};

using Parameters = std::set< Parameter >;

struct Valid_parameters {

  Parameters phase_model;
  Parameters amplitude_model;
  
  auto empty() const noexcept -> bool
  {
    return phase_model.empty() || amplitude_model.empty();
  }

};

}}}

#endif /* parameter_list_h */
