//
//  transient_analysis_sweep_results.h
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_pyrometry_twoColor_periodic_transient_analysis_sweep_results__
#define __tat_thermal_pyrometry_twoColor_periodic_transient_analysis_sweep_results__

#include <vector>
#include <utility>
#include "thermal/pyrometry/twoColor/periodic/results.h"
#include "units.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

struct transient_analysis_sweep_results
{
  std::vector< transient_analysis_results > transient_results;
  std::vector< units::quantity< units::si::frequency> > laser_modulation_freq;

  transient_analysis_sweep_results(
    std::vector< transient_analysis_results > const & transient_results_
  );

  auto phases_omega(void) const -> 
  std::pair<
    std::vector< units::quantity< units::si::angular_frequency>>,
    std::vector< units::quantity< units::si::plane_angle      >> >;
  
  auto phases_frequency(void) const ->
  std::pair<
    std::vector< units::quantity< units::si::frequency        >>,
    std::vector< units::quantity< units::si::plane_angle      >> >;
  
  auto surface_temperature_phases( void ) const
  -> std::vector< units::quantity< units::si::plane_angle > >;
  
  auto surface_temperature_amplitudes( void ) const
  -> std::vector< units::quantity< units::si::temperature > >;
  
  auto surface_steady_temperature( void ) const
  -> std::vector< units::quantity< units::si::temperature > >;
};

} // namespace periodic
} // namespace twoColor
} // namespace napyrometryme
} // namespace thermal



#endif /* defined(__tat__transient_analysis_sweep_results__) */
