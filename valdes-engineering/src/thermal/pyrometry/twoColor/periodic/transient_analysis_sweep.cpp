//
//  transient_analysis_sweep.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>
#include "thermal/pyrometry/twoColor/periodic/transient_analysis_sweep.h"
#include "thermal/define/lthermal.h"
#include "algorithm/algorithm.h"
#include "physics/classical_mechanics/kinematics.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

using algorithm::for_each;
using namespace units;
using std::vector;
using std::pair;
using std::make_pair;



auto transient_analysis_sweep
(
  std::vector<
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > > laser_modulations,

  std::vector< std::pair<
    thermal::equipment::detector::Measurements,
    thermal::equipment::detector::Measurements > > const & sweep,
 
  units::quantity< units::si::dimensionless > const & gCoeff
)
noexcept -> transient_analysis_sweep_results
{
  assert( gCoeff.value() > 0 );
  assert( laser_modulations.size() == sweep.size() );
  vector< transient_analysis_results > results;

  size_t i = 0;
  for_each( laser_modulations , [&]( auto const & laser_modulation ) noexcept
  {
    auto const m_1 = sweep[i].first;
    auto const m_2 = sweep[i].second;
    auto const laser_frequency =  laser_modulation.first;
    auto const laser_phase = laser_modulation.second;
    auto const result =
    transient_analysis( m_1, m_2, gCoeff, laser_frequency, laser_phase ) ;
    
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
    p.laser_modulations,
    p.measurements,
    p.gCoefficient
  );
}
  
} // namespace periodic
} // namespace twoColor
} // namespace napyrometryme
} // namespace thermal
