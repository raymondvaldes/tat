//
//  radius.cpp
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "radius.hpp"
#include <cassert>

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace disk{
namespace dimensionless{

using namespace units;

auto radius_s
(
 disk::radius const R_disk,
 equipment::laser::Beam_radius const R_heat
) noexcept -> Radius_s
{
  assert( isnormal( R_disk ) );
  assert( R_disk > 0 * meters ) ;
  assert( isnormal( R_heat ) );
  assert( R_heat > 0 * meters );

  auto const s = R_disk / R_heat;
  return s;
}

} // dimensionless
} // disk
} // finite_disk
} // oneLayer2d
} // model
} // thermal
