//
//  thickness.cpp
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "thickness.hpp"
#include <cassert>

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace disk{
namespace dimensionless{

using namespace units;

auto thickness_w
(
 disk::thickness const L,
 equipment::laser::Beam_radius const R_heat
) noexcept -> Thickness_w
{
  assert( isnormal( L ) );
  assert( L > 0 * meters );
  assert( isnormal( R_heat ) );
  assert( R_heat > 0 * meters );
  
  auto const w = L / R_heat;
  return w;
}

} // dimensionless
} // disk
} // finite_disk
} // oneLayer2d
} // model
} // thermal
