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
#include "thermal/model/optics/optics.h"

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace phase_analysis{

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
  units::quantity< units::si::length > view_radius_offset;

  std::vector< units::quantity<units::si::plane_angle > > observations;
  
  // optical parameter (holds the best-fit)
  thermal::model::Optics optics;
  

  explicit Best_fit
  (
    thermal::model::slab::Slab const slab_,
    units::quantity< units::si::dimensionless > const view_radius_nd,
    units::quantity< units::si::dimensionless> const b,
    std::vector< units::quantity<units::si::frequency> > const frequencies_,
    std::vector< units::quantity<units::si::plane_angle > > const model_phases_,
    double const phase_goodness_of_fit_
  ) noexcept ;
  

  explicit Best_fit
  (
    thermal::model::slab::Slab const slab_,
    units::quantity< units::si::dimensionless > const view_radius_nd,
    units::quantity< units::si::dimensionless> const b,
    std::vector< units::quantity<units::si::frequency> > const frequencies_,
    std::vector< units::quantity<units::si::plane_angle > > const model_phases_,
    double const phase_goodness_of_fit_,
    units::quantity< units::si::dimensionless > const view_radius_offset_input
  ) noexcept ;  

  

  explicit Best_fit
  (
    thermal::model::slab::Slab const slab,
    thermal::model::Optics const optics,
    double const phase_goodness_of_fit
  ) noexcept ;
  
  void plot_model_phases_against(
    std::vector< units::quantity< units::si::plane_angle > > const & exp_phases
  ) const;
  
  void plot_model_phases_against_observations( void ) const ;
  
  auto phase_goodness_of_fit_function() const -> double;
  
};

} // namespace phase_analysis
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal


#endif /* defined(__tat__Best_fit__) */
