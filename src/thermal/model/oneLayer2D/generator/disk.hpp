//
//  disk.hpp
//  tat
//
//  Created by Raymond Valdes on 10/21/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef disk_hpp_102115
#define disk_hpp_102115

#include "thermal/model/oneLayer2D/model_selection.h"
#include "thermal/equipment/laser/modulation_frequency.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/model/complex/temperatures.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include <functional>

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace generator{

class Disk{

private:
  enum Detector_model detector_model;
  enum Conduction_model conduction_model;
  slab::Slab slab;
  Optics optics;

public:
  Disk
  (
    Conduction_model const & conduction_model,
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

  auto get_emission_sweep() const -> std::function<
    thermal::model::complex::Temperatures(
        slab::Slab const &,
        Optics const &,
        equipment::laser::Modulation_frequencies const & ) >;

  auto get_slab() const noexcept -> slab::Slab;
  auto get_optics() const noexcept -> Optics;
};

} // namespace generator
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* disk_hpp */
