//
//  diffusivity_from_phases.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_analysis_two_layer_speciman_diffusivity_from_phases__
#define __tat_thermal_analysis_two_layer_speciman_diffusivity_from_phases__

#include <vector>
#include <utility>

#include "thermal/model/slab/slab.h"
#include "units.h"

namespace thermal {
namespace analysis {
namespace two_layer_speciman {


struct fitting_result{
  std::vector< units::quantity<units::si::frequency> > frequencies;

  thermal::model::slab::Slab initial_slab;
  thermal::model::slab::Slab fitted_slab;
  thermal::model::slab::Slab substrate_slab;

  std::vector< units::quantity< units::si::plane_angle > > experimenta_phases;
  std::vector< units::quantity< units::si::plane_angle > > bestFit_phases;

  fitting_result
  (
    std::vector< units::quantity<units::si::frequency> > const  frequencies_,
    thermal::model::slab::Slab const initial_slab_,
    thermal::model::slab::Slab const fitted_slab_,
    thermal::model::slab::Slab const substrate_slab,
    std::vector< units::quantity< units::si::plane_angle > > const experimenta_phases_,
    std::vector< units::quantity< units::si::plane_angle > > const bestFit_phases_
  );

};

auto diffusivity_from_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const & slab_initial,
  thermal::model::slab::Slab const & slab_substrate
) noexcept -> fitting_result;

} // namespace two_layer_speciman
} // namespace analysis
} // namespace thermal

#endif /* defined(__tat_thermal_analysis_two_layer_speciman_diffusivity_from_phases__) */
