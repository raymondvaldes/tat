//
//  thermal_penetration.cpp
//  tat
//
//  Created by Raymond Valdes on 10/19/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/finite_disk/dimensionless/thermal_penetration.h"

#include <cassert>

namespace thermal { namespace model { namespace oneLayer2D { namespace finite_disk { namespace dimensionless{

using namespace units;

auto
thermal_penetration(
  disk::Thermal_diffusivity const alpha,
  laser_beam::Modulation_frequency const frequency,
  laser_beam::Radius const R_heat
) noexcept -> Thermal_penetration
{
  assert( alpha.value() > 0  );
  assert( R_heat > 0 * si::meters );
  assert( frequency > 0 * si::hertz );

  auto const l = sqrt( alpha / ( 2. * M_PI * frequency ) ) / R_heat;
  
  assert( l > 0 );
  return l;
}

} } } } }
