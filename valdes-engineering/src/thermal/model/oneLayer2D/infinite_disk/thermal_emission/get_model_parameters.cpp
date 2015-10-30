//
//  get_model_parameters.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "get_model_parameters.hpp"

#include "centered_point/valid_amplitude_parameters.hpp"
#include "centered_point/valid_phase_parameters.hpp"

#include "centered_with_view/valid_amplitude_parameters.hpp"
#include "centered_with_view/valid_phase_parameters.hpp"

#include "offset_detector/valid_amplitude_parameters.hpp"
#include "offset_detector/valid_phase_parameters.hpp"

#include "offset_point/valid_amplitude_parameters.hpp"
#include "offset_point/valid_phase_parameters.hpp"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace infinite_disk{
namespace thermal_emission {

auto
get_model_parameters( Detector_model const detector_model )
noexcept -> Valid_parameters
{
  auto v = Valid_parameters();

  switch( detector_model ) {
  
    case Detector_model::center_point:
      v.phase_model = centered_point::valid_phase_parameters();
      v.amplitude_model = centered_point::valid_phase_parameters();
      break;

    case Detector_model::center_with_view:
      v.phase_model = centered_with_view::valid_phase_parameters();
      v.amplitude_model = centered_with_view::valid_phase_parameters();
      break;
    
    case Detector_model::offset_point:
      v.phase_model = offset_point::valid_phase_parameters();
      v.amplitude_model = offset_point::valid_phase_parameters();
      break;
      
    case Detector_model::offset_with_view:
      v.phase_model = offset_detector::valid_phase_parameters();
      v.amplitude_model = offset_detector::valid_phase_parameters();
      break;
  }
  
  return v;
}

} // namespace thermal_emission
}
} // namespace oneLayer2D
} // namespace model
} // namespace thermal


