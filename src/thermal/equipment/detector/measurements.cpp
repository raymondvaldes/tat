//
//  measurements.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/equipment/detector/measurements.h"
#include "algorithm/algorithm.h"
#include "assert/assertExtensions.h"

namespace thermal {

namespace equipment {

namespace detector {

Measurements::Measurements(
  units::quantity<units::si::wavelength> const & wavelengthIn,
  std::vector< units::quantity< units::si::time> > referenceTime,
  std::vector< units::quantity< units::si::electric_potential > > const & signals )
  : wavelength( wavelengthIn), measurements( signals.size() )
{
  assert_gt_zero( wavelengthIn );
  assert_equal( referenceTime.size(), signals.size() );
  
  auto i = 0u;
  using algorithm::generate;
  generate( measurements, [&referenceTime, &signals, &i]() noexcept
  {
    auto const melissa = Measurement{ referenceTime[i], signals[i] };
    ++i;
    return melissa;
  } );
  
};

auto Measurements::size( void )
const noexcept -> size_t
{
  return measurements.size();
};

auto Measurements::referenceTimes( void )
const noexcept-> std::vector< units::quantity<units::si::time> >
{
  using std::vector;
  using units::quantity;
  using units::si::time;
  using algorithm::generate;
  
  auto const count = size();
  
  auto const myMeasurements = measurements;
  auto times = vector< quantity< time > >{ count };
  auto i = 0;

  generate( times, [ &myMeasurements, &i]() noexcept
  {
    auto const time = myMeasurements[i].reference_time;
    ++i;
    return time ;
  } );

  return times;
}
  
} // namespace detector

} // namespace equipment

} // namespace thermal
