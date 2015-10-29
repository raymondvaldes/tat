//
//  select_detector_model.cpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "select_detector_model.hpp"
#include "centered_with_view/frequency_sweep.h"
#include "centered_point/frequency_sweep.hpp"
#include "offset_detector/frequency_sweep.hpp"
#include "offset_point/frequency_sweep.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace infinite_disk {
namespace thermal_emission {

using namespace thermal::model::oneLayer2D::thermal_emission;
using equipment::laser::Modulation_frequencies;
using slab::Slab;
using complex::Temperatures;

auto select_detector_model
(
  Detector_model const detector_model
)
-> std::function <
      Temperatures( Slab const &, Optics const &, Modulation_frequencies const & )
    >
{
  auto func = std::function <
      Temperatures( Slab const &, Optics const &, Modulation_frequencies const&)
    >();
  
  switch( detector_model )
  {
    case Detector_model::center_point:
      func = centered_point::frequency_sweeper;
      break;

    case Detector_model::center_with_view:
      func = centered_with_view::frequency_sweeper;
      break;
    
    case Detector_model::offset_point:
      func = offset_detector::frequency_sweeper;
      break;
      
    case Detector_model::offset_with_view:
      throw Detector_model_not_available( detector_model );
      break;
  }

  return func;
}

}
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

