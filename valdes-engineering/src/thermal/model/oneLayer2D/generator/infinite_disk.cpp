//
//  infinite_disk_center_detector_with_view.cpp
//  tat
//
//  Created by Raymond Valdes on 10/14/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "infinite_disk.hpp"
#include <cassert>
#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/centered_with_view/frequency_sweep.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace generator{

Infinite_disk::Infinite_disk
(
  Detector_model const & detector_model,
  slab::Slab const & slab,
  Optics const & optics
)
  : detector_model( detector_model ), slab( slab ), optics(optics)
{

}


auto Infinite_disk::evaluate
(
  equipment::laser::Modulation_frequencies const & modulation_frequencies
)
const -> thermal::model::complex::Temperatures
{
  assert( !modulation_frequencies.empty() );
  assert( detector_model == Detector_model::center_with_view );

  auto const out =
    thermal_emission::centered_with_view::frequency_sweeper(slab, optics, modulation_frequencies);

  assert( out.size() == modulation_frequencies.size() );
  return out;
}


} // namespace generator
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

