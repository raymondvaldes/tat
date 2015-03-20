//
//  normalizedDetectorMeasurements.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/pyrometry/twoColor/normalizedDetectorMeasurements.h"
#include "assert/assertExtensions.h"
#include "thermal/pyrometry/twoColor/normalizedSignalRatio.h"
#include "thermal/pyrometry/twoColor/calibratedSignalRatio.h"
#include "thermal/pyrometry/twoColor/signalRatio.h"
#include "thermal/pyrometry/twoColor/normalizedSignalRatio_from_measurement.h"
#include "algorithm/algorithm.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {

using std::vector;
using std::make_pair;
using units::quantity;
using units::si::time;
using units::si::one_over_temperature;
using thermal::pyrometer::twoColor::signalRatio;
using thermal::pyrometer::twoColor::calibratedSignalRatio;
using thermal::pyrometer::twoColor::normalizedSignalRatio;
using algorithm::generate;

auto normalizedDetectorMeasurements
(
  thermal::equipment::detector::Measurements const & first,
  thermal::equipment::detector::Measurements const & second,
  units::quantity< units::si::dimensionless > const & gCoeff
)
noexcept  ->
std::pair<
  std::vector< units::quantity< units::si::time > > ,
  std::vector< units::quantity< units::si::one_over_temperature > > >
{
  assert_gt_zero( first.size() ) ;
  assert_gt_zero( second.size() );
  
 // assert_ge(  );
  
  assert_gt_zero( gCoeff ) ;
  
  auto const count = first.size();
  auto normalizedSRs = vector< quantity<one_over_temperature> >( count ) ;
  
  auto i = 0u;
  auto const normalizeSR_generator = [&first, &second, &gCoeff, &i]() noexcept
  {
    using thermal::pyrometry::twoColor::normalizedSignalRatio_from_measurement;
    auto const val =  normalizedSignalRatio_from_measurement(
      first.wavelength, first.measurements[i].signal ,
      second.wavelength, second.measurements[i].signal,  gCoeff  ) ;
    i++;
    return val ;
  } ;
  
  generate( normalizedSRs, normalizeSR_generator ) ;

  auto const times = first.referenceTimes();

  return make_pair( times, normalizedSRs ) ;
}
  
} // namespace twoColor
  
} // namespace pyrometry
  
} // namespace thermal
