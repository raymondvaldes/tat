//
//  transient_analysis.h
//  tat
//
//  Created by Raymond Valdes_New on 3/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__transient_analysis__
#define __tat__transient_analysis__

#include <vector>
#include <utility>

#include "math/functions/cosine.h"
#include "thermal/equipment/detector/Measurements.h"
#include "units.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {

struct transient_analysis_results{

  units::quantity< units::si::temperature > steady_temperature;

  units::quantity< units::si::plane_angle> transient_temperature_phase;

  units::quantity< units::si::temperature > transient_temperature_amplitude;

  std::pair<
  std::vector< units::quantity< units::si::time > > ,
  std::vector< units::quantity< units::si::one_over_temperature > >
  > normalized_SRs;

  math::functions::Cosine< units::si::one_over_temperature >
  fitted_cosine_function;
  
  units::quantity< units::si::angular_frequency > laser_modulation_w;

  transient_analysis_results
  (
    units::quantity< units::si::temperature > const &
    steady_temperature_,

    units::quantity< units::si::plane_angle> const &
    transient_temperature_phase_,

    units::quantity< units::si::temperature > const &
    transient_temperature_amplitude_,

    std::pair<
      std::vector< units::quantity< units::si::time > > ,
      std::vector< units::quantity< units::si::one_over_temperature > >> const &
    normalized_SRs_,

    math::functions::Cosine< units::si::one_over_temperature > const &
    fitted_cosine_function_,
   
    units::quantity< units::si::angular_frequency > const & laser_modulation_w_

  )  : steady_temperature( steady_temperature_ ),
      transient_temperature_phase( transient_temperature_phase_ ),
      transient_temperature_amplitude( transient_temperature_amplitude_ ),
      normalized_SRs( normalized_SRs_ ),
      fitted_cosine_function( fitted_cosine_function_ ),
      laser_modulation_w( laser_modulation_w_ )
  {};
};

auto transient_analysis
(
  thermal::equipment::detector::Measurements const & measurements_1,
  thermal::equipment::detector::Measurements const & measurements_2,
  units::quantity< units::si::dimensionless > const & gCoeff,
  units::quantity< units::si::angular_frequency > const & laser_modulation,
  units::quantity< units::si::plane_angle > const & laser_phase,
  units::quantity< units::si::plane_angle> const & cosine_phase =
  units::quantity< units::si::plane_angle>::from_value(0)
)
noexcept -> transient_analysis_results;
  
} // namespace twoColor
  
} // namespace napyrometryme
  
} // namespace thermal


#endif /* defined(__tat__transient_analysis__) */
