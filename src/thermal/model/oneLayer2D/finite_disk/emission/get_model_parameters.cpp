//
//  get_model_parameters.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "get_model_parameters.hpp"

#include "centered_detector_with_view/valid_amplitude_parameters.h"
#include "centered_detector_with_view/valid_phase_parameters.h"

#include "centered_point/valid_amplitude_parameters.h"
#include "centered_point/valid_phase_parameters.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace emission{

auto
get_model_parameters( Detector_model const detector_model )
-> Valid_parameters
{
  auto v = Valid_parameters();

  switch( detector_model ) {
  
    case Detector_model::center_point:
      v.phase_model = centered_point::valid_phase_parameters();
      v.amplitude_model = centered_point::valid_amplitude_parameters();
      break;

    case Detector_model::center_with_view:
      v.phase_model = centered_detector_with_view::valid_phase_parameters();
      v.amplitude_model = centered_detector_with_view::valid_amplitude_parameters();
      break;
    
    case Detector_model::offset_point:
      throw Detector_model_not_available( detector_model );
      break;
      
    case Detector_model::offset_with_view:
      throw Detector_model_not_available( detector_model );
      break;
  }
  
  return v;
}

} // namespace thermal_emission
}
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

