//
//  frequency_sweep.cpp
//  tat
//
//  Created by Raymond Valdes on 9/8/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "frequency_sweep.hpp"
#include <cassert>
#include "algorithm/algorithm.h"
#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/thermal_penetration.h"
#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/point_measurement.h"
#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/b.h"
#include "thermal/model/oneLayer2D/infinite_disk/dimensional/deltaT.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {
namespace centered_point{

using namespace units;
using std::vector;
using math::complex::properties;
using algorithm::transform;


auto
frequency_sweep
(
  units::quantity< units::si::dimensionless > const b ,
  units::quantity< units::si::temperature > const deltaT ,
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  units::quantity< units::si::length > const L,
  units::quantity< units::si::thermal_diffusivity > const alpha
)
noexcept -> std::vector< math::complex::properties< units::si::temperature > >
{
  assert( b > 0 ) ;
  assert( deltaT > 0 * kelvin   );
  assert( !frequencies.empty() );
  assert( L > 0 * meters ) ;
  assert( alpha.value() > 0  ) ;

  auto const r_offset = quantity< si::dimensionless > (  0 );

  auto results =
  vector< properties< si::temperature > >( frequencies.size()  );
  
  transform( frequencies, results.begin(), [&]( auto const f ) noexcept
  {
    auto const l = dimensionless::thermal_penetration( f, L, alpha ) ;
    auto const p = point_measurement( b, l, deltaT, r_offset );
    return p;
  } );
  
  return results;
}

auto
frequency_sweeper
(
  slab::Slab const & slab,
  Optics const & optics,
  equipment::laser::Modulation_frequencies const & frequencies
)
noexcept -> thermal::model::complex::Temperatures
{
  assert( !frequencies.empty() );
  
  using thermal::model::complex::Temperatures;
  using algorithm::transform;
  
  auto const k = slab.thermal_conductivity();
  auto const L = slab.thickness() ;
  auto const I = optics.laser_power;
  
  auto const deltaT = dimensional::deltaT( I , L, k ) ;
  
  auto const b = dimensionless::b( optics.laser_radius, L );
  auto const alpha = slab.thermal_diffusivity();

  auto const temperature_properties =
  frequency_sweep( b, deltaT, frequencies, L, alpha );
  
  assert( temperature_properties.size() == frequencies.size() );
  
  auto complex_temperatures = std::vector< complex::Temperature >( frequencies.size() );
  
  transform( temperature_properties, complex_temperatures.begin(),
  []( auto const & e) noexcept
  {
    return complex::Temperature( e );
  } );
  
  auto const temperatures = complex::Temperatures( complex_temperatures );
  
  assert( frequencies.size() == temperatures.size() );
  return temperatures;
}


} // namespace centered_point
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
