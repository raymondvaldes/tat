//
//  transient_analysis_sweep.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>
#include "thermal/pyrometry/twoColor/transient_analysis_sweep.h"
#include "physics/classical_mechanics/kinematics.h"
#include "algorithm/algorithm.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {
/* angular_velocity */
using algorithm::for_each;
using units::quantity;
using units::si::frequency;
using units::si::angular_frequency;
using units::si::plane_angle;
using std::vector;
using std::pair;
using std::make_pair;
using physics::classical_mechanics::angularFrequencies_from_frequencies;


transient_analysis_sweep_results::transient_analysis_sweep_results
(
  std::vector< transient_analysis_results > const & transient_results_
): transient_results( transient_results_ ) {}


auto transient_analysis_sweep_results::phases_omega(void) const -> void
//std::pair<  std::vector< units::quantity< units::si::angular_frequency>  >,
//            std::vector< units::si::plane_angle > >
{
  auto omegas = vector< quantity< angular_frequency >>();
  auto phases = vector< quantity< plane_angle >>();
  
  for_each( transient_results , [&](auto const& u) noexcept
  {
    omegas.push_back( u.laser_modulation_w );
    phases.push_back( u.transient_temperature_phase );
  });

  auto const output = make_pair( omegas, phases );
  
  std::cout << output.first[0] << "\t" << output.second[0] << "\n";
  std::cout << output.first[1] << "\t" << output.second[1] << "\n";
//  return output;
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
  std::vector< transient_analysis_results > results;
  auto const omegas =
  angularFrequencies_from_frequencies( laser_modulation_frequencies );

  size_t i = 0;
  for_each( omegas , [&]( auto const & omega )
  {
    auto const m_1 = sweep[i].first;
    auto const m_2 = sweep[i].second;
    auto const result = transient_analysis( m_1, m_2, gCoeff, omega );
    results.push_back( result );
    ++i;
  } );

  auto const output = transient_analysis_sweep_results( results );

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
