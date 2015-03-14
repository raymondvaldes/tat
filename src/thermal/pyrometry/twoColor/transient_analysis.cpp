//
//  transient_analysis.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/pyrometry/twoColor/transient_analysis.h"
#include "thermal/pyrometry/twoColor/normalizedDetectorMeasurements.h"
#include "math/functions/periodicData.h"
#include "math/functions/PeriodicProperties.h"
#include "math/curveFit/cosine.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {

using units::quantity;
using units::si::radians;
using units::si::one_over_temperature;
using units::si::temperature;
using units::si::plane_angle;
using units::si::time;
using units::si::dimensionless;
using units::pow;

using math::functions::PeriodicData;
using math::functions::PeriodicProperties;
using math::curveFit::cosine;
using math::functions::Cosine;

using std::pair;
using std::vector;

auto transient_analysis
(
  thermal::equipment::detector::Measurements const & measurements_1,
  thermal::equipment::detector::Measurements const & measurements_2,
  units::quantity< units::si::dimensionless > const & gCoeff,
  units::quantity< units::si::angular_frequency > const & laser_modulation
)
noexcept -> transient_analysis_results
{
  auto const normalized_SRs =
  normalizedDetectorMeasurements( measurements_1, measurements_2, gCoeff );

  auto const myPeriodicData =
  PeriodicData< one_over_temperature >( normalized_SRs ) ;
  
  auto const initialConditions =
  PeriodicProperties<one_over_temperature>{
    myPeriodicData.initialEstimateOffset(),
    myPeriodicData.initialEstimateAmplitude(),
    laser_modulation,
    quantity<plane_angle>{ -1.6 * radians }
  } ;

  auto const fitted_cosine_function =
  cosine( normalized_SRs, initialConditions );

  auto const myFittedAmplitude = fitted_cosine_function.get_amplitude() ;
  auto const myFittedOffset = fitted_cosine_function.get_offset() ;
  
  auto const transient_temperature_phase = fitted_cosine_function.get_phase() ;
  auto const steady_temperature =
  quantity<temperature>(quantity<dimensionless>{1} / myFittedOffset) ;
  
  auto const transient_temperature_amplitude =
  myFittedAmplitude * pow<2>( steady_temperature );

  auto const output =
  transient_analysis_results
  (
    steady_temperature,
    transient_temperature_phase,
    transient_temperature_amplitude,
    normalized_SRs,
    fitted_cosine_function,
    laser_modulation
  );

  return output;
}

  
} // namespace twoColor
  
} // namespace napyrometryme
  
} // namespace thermal
