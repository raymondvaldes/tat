//
//  diffusivity_from_phases.h
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_ther_anais_oneer2D_estimarfitr_all_but_diffusivity_
#define __tat_ther_anais_oneer2D_estimarfitr_all_but_diffusivity_


#include "units.h"
#include "thermal/model/slab/slab.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/weighted_average/Best_fit.h"

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace weighted_average{
namespace fit_all_but_diffusivity{

auto diffusivity_from_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const slab_initial,
  units::quantity< units::si::length> const beam_radius,
  units::quantity< units::si::length > const detector_view_radius,
  units::quantity< units::si::temperature> const steady_state_temperature,
  units::quantity< units::si::wavelength> const detector_wavelength
) noexcept -> Best_fit;

} // namespace fit_all_but_diffusivty
} // namespace weighted_average
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal

#endif /* defined(__tat__diffusivity_from_phases__) */
