//
//  valid_amplitude_parameters.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "valid_amplitude_parameters.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace emission{
namespace centered_detector_with_view{

auto valid_amplitude_parameters() noexcept -> Parameters
{
  auto const parameters = Parameters({

    Parameter::disk_thermal_conductivity,
    
  });
  
  return parameters;
}

}}}}}}
