//
//  deltaT.cpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "deltaT.hpp"
#include <gsl.h>

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace dimensional{

using namespace units;

auto deltaT(
  disk::Thermal_conductivity const k,
  equipment::laser::Beam_radius const Rheat,
  equipment::laser::Beam_power const Q
) noexcept -> Temperature_scale
{
  Expects( k.value() > 0 && isnormal(k) );
  Expects( Rheat > 0 * meters && isnormal( Rheat) );
  Expects( Q.value() > 0 && isnormal(Q) );
  
  auto const t = Q / ( Rheat * k );

  Ensures( t.value() > 0 && isnormal(t) );
  return t;
}



} // dimensional
} // finite_disk
} // oneLayer2d
} // model
} // thermal

