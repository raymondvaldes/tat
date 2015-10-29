//
//  deltaT.hpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef deltaT_hpp_10261534f23vc
#define deltaT_hpp_10261534f23vc

#include "temperature_scale.hpp"

#include "thermal/equipment/laser/Beam_radius.h"
#include "thermal/equipment/laser/beam_power.h"
#include "thermal/model/oneLayer2D/finite_disk/disk/thermal_conductivity.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace dimensional{

auto deltaT(
  disk::Thermal_conductivity const k,
  equipment::laser::Beam_radius const Rheat,
  equipment::laser::Beam_power const Q
) noexcept -> Temperature_scale;



} // dimensional
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* deltaT_hpp */
