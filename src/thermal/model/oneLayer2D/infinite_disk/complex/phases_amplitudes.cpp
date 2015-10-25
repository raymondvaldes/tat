//
//  phases_amplitudes.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/infinite_disk/complex/phases_amplitudes.h"
#include "thermal/model/oneLayer2D/infinite_disk/complex/phase_amplitude.h"
#include "algorithm/algorithm.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

using std::vector;
using math::complex::properties;
using namespace units;
using algorithm::transform;

auto phases_amplitudes
(
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r, 
  units::quantity< units::si::dimensionless > const b,
  std::vector< units::quantity< units::si::dimensionless > > const ls,
  units::quantity< units::si::temperature > const deltaT
) noexcept -> std::vector< math::complex::properties< units::si::temperature >>
{
  assert( z >= 0 );
  assert( r >= 0 );
  assert( b > 0 );
  assert( ls.size() > 0 );
  assert( deltaT > 0 * kelvin );

  auto info = vector< properties< si::temperature > >( ls.size() );
  
  transform( ls , info.begin(), [&]( auto const & l) noexcept
  {
    return phase_amplitude( z, r, b, l, deltaT );
  } ) ;

  return info;

}

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
