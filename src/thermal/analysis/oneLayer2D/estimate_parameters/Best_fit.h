//
//  Best_fit.h
//  tat
//
//  Created by Raymond Valdes on 10/19/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef Best_fit_h_101915
#define Best_fit_h_101915

namespace thermal { namespace analysis { namespace oneLayer2D { namespace estimate_parameters{

//
//struct Best_fit{
//  // system properties
//  units::quantity< units::si::length > view_radius;
//  units::quantity< units::si::length > beam_radius;
//  
//  // modeled elements (reconstructed from non-dimensional parameters)
//  thermal::model::slab::Slab bulk_slab;
//  
//  // modulation frequency/thermal penetration
//  std::vector< units::quantity< units::si::frequency > > frequencies;
//  std::vector< units::quantity< units::si::dimensionless > > ls;
//
//  // model predictions
//  std::vector< units::quantity< units::si::plane_angle > > model_phases;
//
//  double phase_goodness_of_fit;
//  units::quantity< units::si::length > view_radius_offset;
//
//  std::vector< units::quantity<units::si::plane_angle > > observations;
//  
//  // optical parameter (holds the best-fit)
//  thermal::model::Optics optics;
//  
//
//  explicit Best_fit
//  (
//    thermal::model::slab::Slab const slab_,
//    units::quantity< units::si::dimensionless > const view_radius_nd,
//    units::quantity< units::si::dimensionless> const b,
//    std::vector< units::quantity<units::si::frequency> > const frequencies_,
//    std::vector< units::quantity<units::si::plane_angle > > const model_phases_,
//    double const phase_goodness_of_fit_
//  ) noexcept ;
//  
//
//  
//  explicit Best_fit
//  (
//    thermal::model::slab::Slab const slab_,
//    units::quantity< units::si::dimensionless > const view_radius_nd,
//    units::quantity< units::si::dimensionless> const b,
//    std::vector< units::quantity<units::si::frequency> > const frequencies_,
//    std::vector< units::quantity<units::si::plane_angle > > const model_phases_,
//    double const phase_goodness_of_fit_,
//    std::vector< units::quantity<units::si::plane_angle > > const observations_
//  ) noexcept ;
//  
//  void plot_model_phases_against(
//    std::vector< units::quantity< units::si::plane_angle > > const & exp_phases
//  ) const;
//  
//  void plot_model_phases_against_observations( void ) const ;
//  
//};

} } } } // end namespace

#endif /* Best_fit_h */
