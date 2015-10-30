//
//  valid_phase_parameters.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "valid_phase_parameters.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace emission{
namespace centered_point{

auto valid_phase_parameters() noexcept -> Parameters
{
  auto const parameters = Parameters({

    Parameter::disk_thermal_diffusivity,
    Parameter::disk_radius,
    
    Parameter::laser_radius,
    Parameter::rc_filter

  });
  
  return parameters;
};

}}}}}}

