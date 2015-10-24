//
//  view_radius.h
//  tat
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef view_radius_h_0123452345234562456
#define view_radius_h_0123452345234562456

#include "thermal/model/oneLayer2D/finite_disk/detector/view_radius.h"
#include "thermal/model/oneLayer2D/finite_disk/laser_beam/radius.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace detector{
namespace dimensionless {

using View_radius = units::quantity< units::si::dimensionless >;

auto view_radius
(
  detector::View_radius const r_e,
  laser_beam::Radius const R
) noexcept -> View_radius;

} // dimensionless
} // detector
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* view_radius_h */
