//
//  radial_coordinate.h
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef radial_coordinate_h_101615
#define radial_coordinate_h_101615

#include "thermal/equipment/laser/Beam_radius.h"
#include "units.h"
#include "thermal/model/oneLayer2D/finite_disk/dimensional/radial_coordinate.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace dimensionless{

using R = units::quantity< units::si::dimensionless >;

auto
radial_coordinate(
  dimensional::Z const & r_coordinate,
  equipment::laser::Beam_radius const & R_heat
) noexcept -> R ;

} // dimensionless
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* radial_coordinate_h */
