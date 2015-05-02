//
//  periodic_cosine.cpp
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/equipment/detector/simulate_measurements/periodic_cosine.h"
#include "math/construct/periodic_time_distribution.h"

using math::construct::periodic_time_distribution;
using math::functions::Cosine;

using namespace units;

namespace thermal {
namespace equipment {
namespace detector{
namespace simulate_measurements{

auto periodic_cosine(
  math::functions::PeriodicProperties< electric_potential > const & properties,
  units::quantity< units::si::wavelength > const detector_wavelength,
  size_t points
) noexcept -> Measurements
{
  auto const frequency = properties.get_temporalFrequency();
  
  // times is simply a vector that of equally spaced times from 0->period
  auto const times = periodic_time_distribution( frequency , points );
  
  // the signal is created with a periodic function evaluated at times
  auto const signals_function = Cosine< electric_potential >( properties );
  auto const signals = signals_function.evaluate( times );

  auto const simulated_measurements =
    Measurements( detector_wavelength, times, signals );
  return simulated_measurements;
}
  
} // namespace  simulate_measurements
} // namespace  detector
} // namespace  equipment
} // namespace  thermal
