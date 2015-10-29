//
//  frequency_sweep.cpp
//  tat
//
//  Created by Raymond Valdes on 5/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/centered_with_view/frequency_sweep.h"
#include <cassert>

#include "algorithm/algorithm.h"
#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/thermal_penetration.h"
#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/centered_with_view/fast_measurement.h"
#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/b.h"
#include "thermal/model/oneLayer2D/infinite_disk/dimensional/deltaT.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace thermal_emission {
namespace centered_with_view{

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
  
  transform( frequencies, results.begin(), [&]( auto const f )
  {
    auto const l = dimensionless::thermal_penetration( f, L, alpha ) ;
    auto const p = fast_measurement( b, l, r_e );
    
    auto const phase = p.phase;
    auto const amplitude = p.amplitude.value() * deltaT;
    
    auto const T = math::complex::properties< units::si::temperature >
    (phase, amplitude);

    return T;
  });

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
  auto const r_e = dimensionless::b( optics.view_radius, L );
  auto const alpha = slab.thermal_diffusivity();

  auto const temperature_properties =
  frequency_sweep( b, deltaT, r_e, frequencies, L, alpha );
  
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

}
} // namespace thermal_emission
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
