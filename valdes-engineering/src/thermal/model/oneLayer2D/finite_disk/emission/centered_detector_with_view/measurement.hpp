//
//  measurement.hpp
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef measurement_hpp_10161523234twrgw3
#define measurement_hpp_10161523234twrgw3

#include "thermal/model/oneLayer2d/finite_disk/laser_beam/modulation_depth.h"
#include "thermal/model/oneLayer2d/finite_disk/disk/dimensionless/radius.hpp"
#include "thermal/model/oneLayer2D/finite_disk/detector/dimensionless/view_radius.h"
#include "thermal/model/oneLayer2D/finite_disk/disk/dimensionless/thickness.hpp"
#include "thermal/model/oneLayer2D/finite_disk/dimensionless/biot.h"
#include "thermal/model/oneLayer2D/finite_disk/dimensionless/thermal_penetration.h"
#include "thermal/model/complex/temperature.h"

#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/model/complex/temperature.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace disk{
namespace emission{
namespace centered_with_view{

auto measurement
(
  laser_beam::Modulation_depth const m,
  detector::dimensionless::View_radius const r_e,
  disk::dimensionless::Radius_s const s,
  disk::dimensionless::Thickness_w const w,
  finite_disk::dimensionless::Biot const Bi1,
  finite_disk::dimensionless::Biot const Bi2,
  finite_disk::dimensionless::Thermal_penetration const l
)
noexcept -> thermal::model::complex::Temperature;

auto
measurement
(
  slab::Slab const & slab,
  Optics const & optics,
  equipment::laser::Modulation_Frequency const frequency
)
noexcept -> thermal::model::complex::Temperature ;

} // centered_point
} // dimensionless
} // disk
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* measurement_hpp */
