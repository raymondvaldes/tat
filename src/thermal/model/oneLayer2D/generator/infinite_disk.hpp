//
//  infinite_disk_center_detector_with_view.hpp
//  tat
//
//  Created by Raymond Valdes on 10/14/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef infinite_disk_center_dettor_with_view_hpp_101415
#define infinite_disk_center_dettor_with_view_hpp_101415

#include "thermal/model/oneLayer2D/model_selection.h"
#include "thermal/equipment/laser/modulation_frequency.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/model/complex/temperatures.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace generator{

class Infinite_disk{

private:
  enum Detector_model detector_model;
  slab::Slab slab;
  Optics optics;

public:
  Infinite_disk
  (
    Detector_model const & detector_model,
    slab::Slab const & slab,
    Optics const & optics
  );

  auto evaluate
  (
    equipment::laser::Modulation_Frequency const & frequency
  )
  const -> thermal::model::complex::Temperature;

  auto evaluate
  (
    equipment::laser::Modulation_frequencies const & modulation_frequencies
  )
  const -> thermal::model::complex::Temperatures;

};

} // namespace generator
} // namespace oneLayer2D
} // namespace model
} // namespace thermal


#endif /* infinite_disk_center_detector_with_view_hpp */
