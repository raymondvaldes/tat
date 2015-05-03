//
//  transient_analysis_sweep_results.cpp
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/pyrometry/twoColor/periodic/transient_analysis_sweep_results.h"
#include "thermal/define/lthermal.h"
#include "algorithm/algorithm.h"
#include "physics/classical_mechanics/kinematics.h"

using algorithm::for_each;
using namespace units;
using std::vector;
using std::pair;
using std::make_pair;

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

transient_analysis_sweep_results::transient_analysis_sweep_results
(
  std::vector< transient_analysis_results > const & transient_results_
)
: transient_results( transient_results_ )
{}

auto transient_analysis_sweep_results::surface_temperature_phases( void )
const -> std::vector< units::quantity< units::si::plane_angle > >
{
  auto phases = vector< quantity<plane_angle> >();
  for_each(transient_results , [&phases]( auto const & at_each_frequency)
  {
    phases.push_back( at_each_frequency.transient_temperature_phase);
  });
  return phases;
}

auto transient_analysis_sweep_results::surface_steady_temperature( void )
const -> std::vector< units::quantity< units::si::temperature > >
{
  auto steady_temperatures = vector< quantity< si::temperature > >();
  for_each(transient_results , [&steady_temperatures]( auto const & at_each_frequency)
  {
    steady_temperatures.push_back( at_each_frequency.steady_temperature);
  });
  return steady_temperatures;
}

auto transient_analysis_sweep_results::surface_temperature_amplitudes( void )
const -> std::vector< units::quantity< units::si::temperature > >
{
  auto surface_temperatures = vector< quantity< si::temperature > >();
  for_each( transient_results , [&surface_temperatures]
  ( auto const & at_each_frequency)
  {
    surface_temperatures.push_back( at_each_frequency.transient_temperature_amplitude);
  });
  return surface_temperatures;
}


auto transient_analysis_sweep_results::phases_omega(void) const -> 
  std::pair<
    std::vector< units::quantity< units::si::angular_frequency>>,
    std::vector< units::quantity< units::si::plane_angle      >> >
{
  auto omegas = vector< quantity< angular_frequency >>();
  auto phases = vector< quantity< plane_angle >>();
  
  for_each( transient_results , [&](auto const& u) noexcept
  {
    omegas.push_back( u.laser_modulation_w );
    phases.push_back( u.transient_temperature_phase );
  });

  auto const output = make_pair( omegas, phases );
  return output;
}

auto transient_analysis_sweep_results::phases_frequency(void) const ->
std::pair<
  std::vector< units::quantity< units::si::frequency        >>,
  std::vector< units::quantity< units::si::plane_angle      >> >
{
  auto frequencies = vector< quantity< frequency >>();
  auto phases = vector< quantity< plane_angle >>();
  
  using physics::classical_mechanics::angularFrequency_to_frequency;

  for_each( transient_results , [&](auto const& u) noexcept
  {
    auto const f = angularFrequency_to_frequency( u.laser_modulation_w );
    frequencies.push_back( f );
    phases.push_back( u.transient_temperature_phase );
  });

  auto const output = make_pair( frequencies, phases );
  return output;
}

} // namespace periodic
} // namespace twoColor
} // namespace napyrometryme
} // namespace thermal
