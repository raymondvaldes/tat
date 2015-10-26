//
//  valid_phase_parameters.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "valid_phase_parameters.hpp"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace infinite_disk{
namespace thermal_emission {
namespace offset_detector{

auto valid_phase_parameters() noexcept -> Parameters
{
  auto const parameters = Parameters({

    Parameter::disk_thermal_diffusivity,
    
    Parameter::laser_radius,
    Parameter::rc_filter,
    
    Parameter::detector_radius,
    Parameter::detector_offset

  });
  
  return parameters;
}

}}}}}}


