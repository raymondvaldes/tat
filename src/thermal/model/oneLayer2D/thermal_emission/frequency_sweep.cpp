//
//  frequency_sweep.cpp
//  tat
//
//  Created by Raymond Valdes on 5/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/thermal_emission/frequency_sweep.h"
#include <cassert>

#include "algorithm/algorithm.h"
#include "thermal/model/oneLayer2D/dimensionless/thermal_penetration.h"
#include "thermal/model/oneLayer2D/thermal_emission/fast_measurement.h"


namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {

using namespace units;
using std::vector;
using math::complex::properties;
using algorithm::transform;

auto
frequency_sweep
(
  units::quantity< units::si::dimensionless > const b ,
  units::quantity< units::si::temperature > const deltaT ,
  units::quantity< units::si::dimensionless > const r_e ,
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> std::vector< math::complex::properties< units::si::temperature > >
{
  assert( b > 0 ) ;
  assert( !frequencies.empty() );
  assert( L > 0 * meters ) ;
  assert( alpha.value() > 0  ) ;

  auto results =
  vector< properties< si::temperature > >( frequencies.size()  );
  
  transform( frequencies, results.begin(), [&]( auto const f ) noexcept
  {
    auto const l = dimensionless::thermal_penetration( f, L, alpha ) ;
    auto const p = fast_measurement( b, l, r_e );

    return p;
  } );

  return results;
}

} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
