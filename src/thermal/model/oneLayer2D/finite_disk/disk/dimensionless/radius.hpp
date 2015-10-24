//
//  radius.hpp
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef radius_hpp_101615
#define radius_hpp_101615

#include "units.h"
#include "thermal/model/oneLayer2D/finite_disk/disk/radius.h"
#include "thermal/equipment/laser/Beam_radius.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace disk{
namespace dimensionless{

using Radius_s = units::quantity< units::si::dimensionless, double >;

auto radius_s
(
 disk::radius const R_disk,
 equipment::laser::Beam_radius const R_heat
) noexcept -> Radius_s;

} // dimensionless
} // disk
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* radius_hpp */
