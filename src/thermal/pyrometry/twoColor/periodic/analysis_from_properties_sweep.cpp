//
//  analysis_from_properties_sweep.cpp
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/pyrometry/twoColor/periodic/analysis_from_properties_sweep.h"

#include <cassert>

#include "thermal/pyrometry/twoColor/periodic/analysis_from_properties.h"
using namespace units;

using algorithm::for_each;
using std::vector;

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

auto analysis_from_properties_sweep
(
  std::vector<
  math::functions::PeriodicProperties< units::si::electric_potential >> const & properties_1,
  units::quantity<units::si::wavelength> const detector_wavelength_1,
  std::vector<
  math::functions::PeriodicProperties< units::si::electric_potential >> const & properties_2,
  units::quantity<units::si::wavelength> const detector_wavelength_2,
  units::quantity< units::si::dimensionless > const & gCoeff,
  std::vector< units::quantity< units::si::frequency > > const & laser_frequencies
)
noexcept -> transient_analysis_sweep_results
{
  assert( !properties_1.empty() );
  assert( properties_1.size() == properties_2.size() );
  assert( properties_1.size() == laser_frequencies.size() );
  assert( detector_wavelength_1 > 0 * meters );
  assert( detector_wavelength_1 < detector_wavelength_2 );
  assert( gCoeff > 0 );

  auto const laser_phase = quantity< si::plane_angle >::from_value(0);
  
  vector< transient_analysis_results > results;

  size_t i = 0;
  for_each( laser_frequencies , [&]( auto const & laser_frequency ) noexcept
  {
    auto const result =
    analysis_from_properties(
      properties_1[i], detector_wavelength_1,
      properties_2[i], detector_wavelength_2,
      gCoeff, laser_frequency, laser_phase
    ) ;
    
    results.push_back( result );
    ++i;
  } );

  auto const output = transient_analysis_sweep_results( results );

  return output;
}

} // namespace periodic  
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal
