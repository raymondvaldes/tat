////
////  uncertainty_analysis.cpp
////  tat
////
////  Created by Raymond Valdes on 5/6/15.
////  Copyright (c) 2015 Raymond Valdes. All rights reserved.
////
//
//#include "thermal/analysis/oneLayer2D/estimate_parameters/weighted_average/fit_all_but_laser/uncertainty_analysis.h"
//#include "thermal/analysis/oneLayer2D/estimate_parameters/weighted_average/fit_all_but_laser/diffusivity_from_phases.h"
//#include "math/bisection.hpp"
//
//namespace thermal{
//namespace analysis {
//namespace oneLayer2D {
//namespace estimate_parameters{
//namespace weighted_average{
//namespace fit_all_but_laser{
//
//using namespace units;
//
//auto uncertainty_analysis(
//  std::vector< units::quantity< units::si::frequency > > const & frequencies,
//  std::vector< units::quantity< units::si::plane_angle > > const & observations,
//  thermal::model::slab::Slab const slab_initial,
//  units::quantity< units::si::length> const beam_radius,
//  units::quantity< units::si::length > const detector_view_radius,
//  units::quantity< units::si::temperature> const steady_state_temperature,
//  units::quantity< units::si::wavelength> const detector_wavelength
//) noexcept
//{
//  auto const best_fit = diffusivity_from_phases( frequencies, observations,
//  slab_initial, beam_radius, detector_view_radius, steady_state_temperature,
//  detector_wavelength );
//
//  auto const best_fit_model_predictions = best_fit.model_phases;
//
//
//  auto const gFunc_diffusivity = [&best_fit_model_predictions, &slab_initial]( double const x ) noexcept -> double
//  {
//    auto updated_slab =slab_initial;
//    auto const updated_thermal_diffusivity = quantity<thermal_diffusivity>( x * square_millimeters / second );
//    
//    updated_slab.set_diffusivity_update_rhoCp_hold_k( updated_thermal_diffusivity );
//    
//    auto const observations = best_fit_model_predictions ;
//  
//    auto const alternative_best_fit =
//    diffusivity_from_phases( frequencies, observations,
//      slab_initial, beam_radius, detector_view_radius, steady_state_temperature,
//      detector_wavelength );
//    
//    
//    
//    auto const error = alternative_best_fit.phase_goodness_of_fit ;
//    return error;
//  };
//
//  // thermal diffusivity
//  {
//    auto const diff_best_fit = best_fit.bulk_slab.get_diffusivity();
//    auto const lowerbound = quantity<thermal_diffusivity>( 2. * square_millimeters / second );
//    auto const upperbound = quantity< thermal_diffusivity>( 220. * square_millimeters / second );
//    
//    
//    
//    
//  }
//  
//  
//
//
//
//
//}
//
//} // namespace fit_all_but_laser
//} // namespace weighted_average
//} // namespace estimate_parameters
//} // namespace oneLayer2D
//} // namespace analysis
//} // namespace thermal
