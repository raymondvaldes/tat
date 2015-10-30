//
//  view_radius.cpp
//  tat
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/finite_disk/detector/dimensionless/view_radius.h"
#include <cassert>

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace detector{
namespace dimensionless {

using namespace units;

auto view_radius
(
  detector::View_radius const R_view_radius,
  laser_beam::Radius const R
) noexcept -> View_radius
{
  assert( R_view_radius > 0 * si::meters );
  assert( R > 0 * si::meters );
  
  auto const r = R_view_radius / R ;
  return r;
}

} // dimensionless
} // detector
} // finite_disk
} // oneLayer2d
} // model
} // thermal
