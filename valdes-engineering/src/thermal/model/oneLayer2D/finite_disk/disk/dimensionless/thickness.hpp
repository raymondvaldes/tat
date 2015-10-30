//
//  thickness.hpp
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef thickness_hpp_101615
#define thickness_hpp_101615


#include "units.h"
#include "thermal/model/oneLayer2D/finite_disk/dimensional/thickness.h"
#include "thermal/equipment/laser/Beam_radius.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace disk{
namespace dimensionless{

using Thickness_w = units::quantity< units::si::dimensionless >;

auto thickness_w
(
 disk::thickness const L,
 equipment::laser::Beam_radius const R_heat
) noexcept -> Thickness_w;

} // dimensionless
} // disk
} // finite_disk
} // oneLayer2d
} // model
} // thermal


#endif /* thickness_hpp */
