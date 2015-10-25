//
//  frequency_sweep.cpp
//  tat
//
//  Created by Raymond Valdes on 8/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "frequency_sweep.hpp"
#include <cassert>
#include "algorithm/algorithm.h"
#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/thermal_penetration.h"
#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/offset_detector/offset_measurement.hpp"


namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {
namespace offset_detector{

using namespace units;
using std::vector;
using math::complex::properties;
using algorithm::transform;

auto
frequency_sweep
(
  units::quantity< units::si::dimensionless > const b1_beamRadius ,
  units::quantity< units::si::temperature > const deltaT ,
  units::quantity< units::si::dimensionless > const b2_viewRadius ,
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha,
  units::quantity< units::si::dimensionless > const b3_view_offset
)
noexcept -> std::vector< math::complex::properties< units::si::temperature > >
{
  assert( b1_beamRadius > 0 ) ;
  assert( !frequencies.empty() );
  assert( L > 0 * meters ) ;
  assert( alpha.value() > 0  ) ;
  assert( b3_view_offset > 0 );

  auto results =
  vector< properties< si::temperature > >( frequencies.size()  );
  
  transform( frequencies, results.begin(), [&]( auto const f ) noexcept
  {
    auto const l = dimensionless::thermal_penetration( f, L, alpha ) ;
    auto const p = offset_measurement(
      b1_beamRadius,
      l,
      b2_viewRadius,
      b3_view_offset,
      deltaT
    );

    return p;
  } );

  return results;
}

} // namespace offset_point
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
