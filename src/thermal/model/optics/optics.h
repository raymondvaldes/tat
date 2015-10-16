//
//  optics.h
//  tat
//
//  Created by Raymond Valdes on 10/15/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef optics_h_101515
#define optics_h_101515

#include "thermal/equipment/laser/Beam_radius.h"
#include "thermal/equipment/laser/beam_power.h"
#include "thermal/equipment/detector/view_radius.h"

namespace thermal{
namespace model{

struct Optics{

  equipment::laser::Beam_radius laser_radius;
  equipment::laser::Beam_power  laser_power;
  equipment::detector::View_radius view_radius;

  Optics(
    equipment::laser::Beam_radius const & laser_radius,
    equipment::laser::Beam_power  const & laser_power,
    equipment::detector::View_radius const & view_radius
  ):
  laser_radius(laser_radius), laser_power(laser_power), view_radius(view_radius)
  {}
};

} // namespace model
} // namespace thermal

#endif /* optics_h */
