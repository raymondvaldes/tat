//
//  results.h
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_pyrometery_twoColor_periodic_results__
#define __tat_thermal_pyrometery_twoColor_periodic_results__

#include "units.h"
#include "math/functions/cosine.h"
#include "filesystem/path.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

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
  units::quantity< units::si::plane_angle > laser_modulation_phase;

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
   
    units::quantity< units::si::angular_frequency > const & laser_modulation_w_,
   
    units::quantity< units::si::plane_angle > const & laser_modulation_phase_

  )  : steady_temperature( steady_temperature_ ),
      transient_temperature_phase( transient_temperature_phase_ ),
      transient_temperature_amplitude( transient_temperature_amplitude_ ),
      normalized_SRs( normalized_SRs_ ),
      fitted_cosine_function( fitted_cosine_function_ ),
      laser_modulation_w( laser_modulation_w_ ),
      laser_modulation_phase( laser_modulation_phase_ )
  {} ;
  
  
  auto plot_normalized_SR( filesystem::path const & print_file = filesystem::path("") )
  const noexcept -> void;

  auto plot_twoColor_measurements( filesystem::path const & print_file = filesystem::path("") )
  const noexcept -> void;
  
  auto plot_normalized_SR_exp_model( filesystem::path const & print_file = filesystem::path("") )
  const noexcept -> void;
};


} // namespace periodic
} // namespace twoColor
} // namespace napyrometryme
} // namespace thermal

#endif /* defined(__tat__results__) */
