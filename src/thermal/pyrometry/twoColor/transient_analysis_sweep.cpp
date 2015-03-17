//
//  transient_analysis_sweep.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>
#include "assert/assertExtensions.h"
#include "thermal/pyrometry/twoColor/transient_analysis_sweep.h"
#include "thermal/define/lthermal.h"
#include "physics/classical_mechanics/kinematics.h"
#include "algorithm/algorithm.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {
/* angular_velocity */
using algorithm::for_each;
using units::quantity;
using units::si::frequency;
using units::si::temperature;
using units::si::angular_frequency;
using units::si::plane_angle;
using std::vector;
using std::pair;
using std::make_pair;
using physics::classical_mechanics::angularFrequencies_from_frequencies;


transient_analysis_sweep_results::transient_analysis_sweep_results
(
  std::vector< transient_analysis_results > const & transient_results_,
  std::vector< units::quantity< units::si::frequency> > const & laser_modulation_freq_
)
: transient_results( transient_results_ ),
  laser_modulation_freq(laser_modulation_freq_)
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
  auto steady_temperatures = vector< quantity<temperature> >();
  for_each(transient_results , [&steady_temperatures]( auto const & at_each_frequency)
  {
    steady_temperatures.push_back( at_each_frequency.steady_temperature);
  });
  return steady_temperatures;
}



auto transient_analysis_sweep_results::surface_temperature_amplitudes( void )
const -> std::vector< units::quantity< units::si::temperature > >
{
  auto surface_temperatures = vector< quantity<temperature> >();
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

auto transient_analysis_sweep
(
  std::vector< units::quantity< units::si::frequency> > const &
  laser_modulation_frequencies,
 
  std::vector< std::pair<
    thermal::equipment::detector::Measurements,
    thermal::equipment::detector::Measurements > > const & sweep,
 
  units::quantity< units::si::dimensionless > const & gCoeff
)
noexcept -> transient_analysis_sweep_results
{
  assert_gt_zero( laser_modulation_frequencies );
  
  assert( gCoeff.value() > 0 );

  std::vector< transient_analysis_results > results;
  auto const omegas =
  angularFrequencies_from_frequencies( laser_modulation_frequencies );

  size_t i = 0;
  for_each( omegas , [&]( auto const & omega ) noexcept
  {
    auto const m_1 = sweep[i].first;
    auto const m_2 = sweep[i].second;
    auto const result = transient_analysis( m_1, m_2, gCoeff, omega );
    results.push_back( result );
    ++i;
  } );
  

  auto const output =
  transient_analysis_sweep_results( results, laser_modulation_frequencies );

  return output;
}

auto transient_analysis_sweep
(
  gTBC::gMeasure::processed_scope_data const & p
)
noexcept -> transient_analysis_sweep_results
{
  return transient_analysis_sweep(
    p.laser_modulation_freq,
    p.measurements,
    p.gCoefficient
  );
}
  
} // namespace twoColor
  
} // namespace pyrometry
  
} // namespace thermal
