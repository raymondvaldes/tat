//
//  select_emission_model.hpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef select_emission_model_hpp_102515
#define select_emission_model_hpp_102515

#include "model_selection.h"
#include <functional>
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/model/complex/temperatures.h"

#include "thermal/equipment/laser/modulation_frequencies.h"


namespace thermal{
namespace model{
namespace oneLayer2D{

auto select_emission_model
(
  Conduction_model const conduction_model,
  Detector_model const detector_model
)
-> std::function<
    complex::Temperatures(
        slab::Slab const &,
        Optics const &,
        equipment::laser::Modulation_frequencies const & )
  >;

}}}

#endif /* select_emission_model_hpp */
