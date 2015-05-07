//
//  Best_fit.h
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_analysis_oneL2D_estte_paramrs_weighted_average_Bes9629__
#define __tat_thermal_analysis_oneL2D_estte_paramrs_weighted_average_Bes9629__

#include <vector>
#include "units.h"
#include "thermal/model/slab/slab.h"

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace weighted_average{

struct Best_fit{
  // system properties
  units::quantity< units::si::length > view_radius;
  units::quantity< units::si::length > beam_radius;
  
  // modeled elements (reconstructed from non-dimensional parameters)
  thermal::model::slab::Slab bulk_slab;
  
  // modulation frequency/thermal penetration
  std::vector< units::quantity< units::si::frequency > > frequencies;
  std::vector< units::quantity< units::si::dimensionless > > ls;

  // model predictions
  std::vector< units::quantity< units::si::plane_angle > > model_phases;

  double phase_goodness_of_fit;

  explicit Best_fit
  (
    thermal::model::slab::Slab const slab_,
    units::quantity< units::si::dimensionless > const view_radius_nd,
    units::quantity< units::si::dimensionless> const b,
    std::vector< units::quantity<units::si::frequency> > const frequencies_,
    std::vector< units::quantity<units::si::plane_angle > > const model_phases_,
    double const phase_goodness_of_fit_
  ) noexcept ;
  
};

} // namespace weighted_average
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal


#endif /* defined(__tat__Best_fit__) */
