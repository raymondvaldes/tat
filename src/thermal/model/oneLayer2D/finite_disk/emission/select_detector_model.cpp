//
//  select_detector_model.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "select_detector_model.h"

#include "centered_detector_with_view/frequency_sweep.hpp"
#include "centered_point/frequency_sweep.hpp"
//#include "offset_detector/frequency_sweep.hpp"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace emission{

using equipment::laser::Modulation_frequencies;
using slab::Slab;
using complex::Temperatures;

auto select_detector_model
(
  Detector_model const detector_model
)
noexcept
-> std::function <
      Temperatures( Slab const &, Optics const &, Modulation_frequencies const & )
    >
{
  
  auto func = std::function <
      Temperatures( Slab const &, Optics const &, Modulation_frequencies const&)
    >();
  
  switch( detector_model ) {
  
    case Detector_model::center_point:
      func = disk::emission::centered_point::frequency_sweep;
      break;

    case Detector_model::center_with_view:
      func = disk::emission::centered_with_view::frequency_sweep;
      break;
      
    case Detector_model::offset_with_view:
      throw Detector_model_not_available( detector_model );
      break;
    
    case Detector_model::offset_point:
      throw Detector_model_not_available( detector_model );
      break;
  }

  return func;
}


}}}}}
