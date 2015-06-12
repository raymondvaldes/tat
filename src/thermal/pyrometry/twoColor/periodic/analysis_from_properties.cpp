//
//  analyis_from_properties.cpp
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include "thermal/pyrometry/twoColor/periodic/analysis_from_properties.h"

#include "thermal/equipment/detector/simulate_measurements/periodic_cosine.h"
#include "math/functions/PeriodicProperties.h"
#include "thermal/pyrometry/twoColor/periodic/transient_analysis.h"

using namespace units;
using thermal::equipment::detector::simulate_measurements::periodic_cosine;

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

auto analysis_from_properties
(
  math::functions::PeriodicProperties< units::si::electric_potential >
  const & properties_1,
  units::quantity<units::si::wavelength> const detector_wavelength_1,
  math::functions::PeriodicProperties< units::si::electric_potential >
  const & properties_2,
  units::quantity<units::si::wavelength> const detector_wavelength_2,
  units::quantity< units::si::dimensionless > const & gCoeff,
  units::quantity< units::si::frequency > const & laser_frequency,
  units::quantity< units::si::plane_angle> const laser_phase
)
noexcept -> transient_analysis_results
{
  assert( detector_wavelength_1 > 0 * meters );
  assert( detector_wavelength_2 > detector_wavelength_1 );
  assert( gCoeff > 0 );
  assert( laser_frequency > 0 * hertz );

  auto const points = size_t( 500 );

  auto const measurements_1 =
    periodic_cosine( properties_1, detector_wavelength_1, points);
  
  auto const measurements_2 =
    periodic_cosine( properties_2, detector_wavelength_2, points );
  
  auto const results = transient_analysis(
    measurements_1,
    measurements_2,
    gCoeff,
    laser_frequency,
    laser_phase
  );
  
  return results;
}

} // namespace periodic  
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal