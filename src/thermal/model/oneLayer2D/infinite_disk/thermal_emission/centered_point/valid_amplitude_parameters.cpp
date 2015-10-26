//
//  valid_amplitude_parameters.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "valid_amplitude_parameters.hpp"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace infinite_disk{
namespace thermal_emission {
namespace centered_point{

auto valid_amplitude_parameters() noexcept -> Parameters
{
  auto parameters = Parameters({

    Parameter::disk_thermal_conductivity,
    
  });
  
  return parameters;
}

}}}}}}

