//
//  transient_analysis.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include <utility>
#include <iostream>
#include "thermal/pyrometry/twoColor/periodic/transient_analysis.h"
#include "thermal/pyrometry/twoColor/normalizedDetectorMeasurements.h"
#include "math/functions/periodicData.h"
#include "math/functions/PeriodicProperties.h"
#include "math/curveFit/cosine.h"
#include "physics/classical_mechanics/kinematics.h"

#include "tools/interface/filesystem.hpp"
#include "units/algorithm/vector/quantity_to_value.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

using namespace units;

using math::functions::PeriodicData;
using math::functions::PeriodicProperties;
using math::curveFit::cosine;
using math::functions::Cosine;
using physics::classical_mechanics::frequency_to_angularFrequency;

using std::pair;
using std::vector;
using std::make_pair;
using units::container::quantityTodouble;


auto transient_analysis
(
  thermal::equipment::detector::Measurements const & measurements_1,
  thermal::equipment::detector::Measurements const & measurements_2,
  units::quantity< units::si::dimensionless > const  gCoeff,
  units::quantity< units::si::frequency > const laser_frequency,
  units::quantity< units::si::plane_angle > const laser_phase )
noexcept -> transient_analysis_results
{
  assert( laser_frequency > 0 * units::si::hertz );
  assert( gCoeff  > 0 );
  assert( measurements_1.size() == measurements_2.size() );
  assert( measurements_1.wavelength < measurements_2.wavelength );
  assert( measurements_1.size() > 0 );
  assert( measurements_2.size() > 0 );
  
  auto const normalized_SRs =
  normalizedDetectorMeasurements( measurements_1, measurements_2, gCoeff );

  auto const myPeriodicData =
  PeriodicData< one_over_temperature >( normalized_SRs ) ;
  
  auto const initialConditions =
  PeriodicProperties<one_over_temperature>{
    myPeriodicData.initialEstimateOffset() ,
    myPeriodicData.initialEstimateAmplitude(),
    laser_frequency,
    quantity<plane_angle>{ M_PI/4 * radians }
  } ;
  

  auto const fit_cosine =
  cosine( normalized_SRs, initialConditions, laser_phase );

  auto const fitted_cosine_function = fit_cosine.fitted_cosine;

  auto const myFittedAmplitude = abs( fitted_cosine_function.get_amplitude() );
  auto const myFittedOffset = fitted_cosine_function.get_offset() ;
  
  auto  const transient_temperature_phase = fitted_cosine_function.get_phase() ;
  
  auto const steady_temperature =
  quantity<si::temperature>( quantity<dimensionless>{1} / myFittedOffset ) ;
  
  auto const transient_temperature_amplitude =
  myFittedAmplitude * pow<2>( steady_temperature );

  auto const omega = frequency_to_angularFrequency( laser_frequency );

  auto const output =
  transient_analysis_results
  (
    steady_temperature,
    transient_temperature_phase,
    transient_temperature_amplitude,
    normalized_SRs,
    fitted_cosine_function,
    omega,
    laser_phase
  );


  return output;
}

} // namespace periodic
} // namespace twoColor
} // namespace napyrometryme
} // namespace thermal
