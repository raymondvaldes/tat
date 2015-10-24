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
#include "thermal/equipment/laser/beam_intensity.h"
#include "thermal/equipment/detector/view_radius.h"
#include "thermal/equipment/laser/modulation_depth.h"
#include "electronics/filter/low-pass/RC-first-order/time_constant.h"
#include "electronics/filter/low-pass/RC-first-order/resistance.h"
#include "electronics/filter/low-pass/RC-first-order/capacitance.h"

namespace thermal{
namespace model{

struct Optics{

  equipment::laser::Beam_radius laser_radius;
  equipment::laser::Beam_intensity  laser_intensity;
  equipment::detector::View_radius view_radius;
  equipment::laser::Modulation_depth laser_modulation;
  electronics::filter::low_pass::RC_first_order::Time_constant filter_constant;

  Optics(
    equipment::laser::Beam_radius const & laser_radius,
    equipment::laser::Beam_intensity  const & laser_intensity,
    equipment::detector::View_radius const & view_radius,
    equipment::laser::Modulation_depth const laser_modulation
  ):
  laser_radius(laser_radius),
  laser_intensity(laser_intensity),
  view_radius(view_radius),
  laser_modulation( laser_modulation ),
  filter_constant(
    electronics::filter::low_pass::RC_first_order::Resistance( 10000 * units::si::ohms )  *
    electronics::filter::low_pass::RC_first_order::Capacitance( 150. * units::si::picofarads )
  )
  {}
};

} // namespace model
} // namespace thermal

#endif /* optics_h */