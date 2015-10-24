//
//  axial_coordinate.h
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef axial_coordinate_h_101615
#define axial_coordinate_h_101615

#include "thermal/equipment/laser/Beam_radius.h"
#include "units.h"
#include "thermal/model/oneLayer2D/finite_disk/dimensional/axial_coordinate.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace dimensionless{

using Z = units::quantity< units::si::dimensionless >;

auto
axial_coordiate(
  dimensional::Z const & z_coordinate,
  equipment::laser::Beam_radius const & R_heat
) noexcept -> Z ;

} // dimensionless
} // finite_disk
} // oneLayer2d
} // model
} // thermal


#endif /* axial_coordinate_h */
