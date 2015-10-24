//
//  frequency_sweep.hpp
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef frequency_sweep_hpp_101615123412452345
#define frequency_sweep_hpp_101615123412452345

#include <vector>
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/model/complex/temperatures.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace disk{
namespace emission{
namespace centered_detector_with_view{

auto
frequency_sweep
(
  slab::Slab const & slab,
  Optics const & optics,
  equipment::laser::Modulation_frequencies const & frequencies
)
noexcept -> thermal::model::complex::Temperatures ;


} // centered_point
} // dimensionless
} // disk
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* frequency_sweep_hpp */
