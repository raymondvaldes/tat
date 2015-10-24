//
//  finite_disk.hpp
//  tat
//
//  Created by Raymond Valdes on 10/14/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef finite_disk_hpp_101415
#define finite_disk_hpp_101415

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

class Finite_disk{

private:
  enum Detector_model detector_model;
  slab::Slab slab;
  Optics optics;

public:
  Finite_disk
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

#endif /* finite_disk_hpp */
