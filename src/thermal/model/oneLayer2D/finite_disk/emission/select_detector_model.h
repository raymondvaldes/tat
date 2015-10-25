//
//  select_detector_model.h
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef select_detector_model_h_102515
#define select_detector_model_h_102515

#include "thermal/model/oneLayer2D/model_selection.h"
#include <functional>
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/model/complex/temperatures.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace emission{

auto select_detector_model
(
  Detector_model const detector_model
)
noexcept
-> std::function<
    complex::Temperatures(
        slab::Slab const &,
        Optics const &,
        equipment::laser::Modulation_frequencies const & )
  >;


}}}}}

#endif /* select_detector_model_h */
