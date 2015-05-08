//
//  uncertainty_analysis.cpp
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <iostream>
#include <cassert>
//#include <boost/thread.hpp>
#include "math/bisection.hpp"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/uncertainty_analysis.h"

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all/diffusivity_from_phases.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_detectorRadius/diffusivity_from_phases.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_diffusivity/diffusivity_from_phases.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_laser/diffusivity_from_phases.h"

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace phase_analysis{

using namespace units;
using math::solve;

auto uncertainty_analysis(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const slab_initial,
  units::quantity< units::si::length> const beam_radius,
  units::quantity< units::si::length > const detector_view_radius,
  units::quantity< units::si::temperature> const steady_state_temperature,
  units::quantity< units::si::wavelength> const detector_wavelength
) noexcept -> void
{
  assert( beam_radius > 0 * meters);
  assert( detector_view_radius > 0 * meters);
  assert( steady_state_temperature > 280.*kelvin );
  assert( detector_wavelength > 0 * meters );
  assert( frequencies.size() == observations.size() );
  assert( !frequencies.empty() );
  
  auto const best_fit = fit_all::diffusivity_from_phases( frequencies, observations,
  slab_initial, beam_radius, detector_view_radius, steady_state_temperature,
  detector_wavelength );
  auto const target = best_fit.phase_goodness_of_fit;
  
  
  /// uncertainty in detector_radius
  {
    auto const L = best_fit.bulk_slab.characteristic_length;
  
    auto const gFunc =[&best_fit, &steady_state_temperature,
      &detector_wavelength, &beam_radius, &detector_view_radius, &slab_initial]
    ( double const x ) noexcept -> double
    {
      auto slab = best_fit.bulk_slab;
      slab.set_diffusivity_update_rhoCp_hold_k( slab_initial.get_diffusivity());
      
      // updated best-fit slab with perturbed parameter
      auto const L = slab.characteristic_length;
      auto const updated_detectorRadius =
      quantity<si::dimensionless>::from_value( x ) * L;
      
      // update observations to use the original model best-fit
      auto const observations = best_fit.model_phases;
      auto const frequencies = best_fit.frequencies;
      
      
      auto const alternative_best_fit =
      fit_all_but_detectorRadius::diffusivity_from_phases( frequencies, observations,
        slab, beam_radius, updated_detectorRadius, steady_state_temperature,
        detector_wavelength );
      
      auto const error = alternative_best_fit.phase_goodness_of_fit ;
      return error;
    };

    auto const detectorR_best_fit = (best_fit.view_radius / L ).value()  ;
    auto const lowerbound = 0.051 ;
    auto const upperbound = 1.9 ;

    auto const ojb_ub = solve( gFunc, target, detectorR_best_fit, upperbound ) ;
    double soln_ub = ojb_ub.returnSoln();
    double soln_ub_pass = ojb_ub.pass;
    
    std::cout << soln_ub << "\t" << soln_ub_pass << "\n";
    
    auto const obj_lb = solve( gFunc, target, lowerbound, detectorR_best_fit ) ;
    double soln_lb = obj_lb.returnSoln();
    double soln_lb_pass = obj_lb.pass;
    
    std::cout << soln_lb << "\t" << detectorR_best_fit <<"\t" << soln_ub << "\n";
    std::cout << soln_ub_pass << "\t" << soln_lb_pass << "\n";

  }

  
  /// uncertainty in laser_beam
  {
    auto const L = best_fit.bulk_slab.characteristic_length;
  
    auto const gFunc =[&best_fit, &steady_state_temperature,
      &detector_wavelength, &beam_radius, &detector_view_radius, &slab_initial, &L]
    ( double const x ) noexcept -> double
    {
      auto slab = best_fit.bulk_slab;
      slab.set_diffusivity_update_rhoCp_hold_k( slab_initial.get_diffusivity());
      
      // updated best-fit slab with perturbed parameter
      auto const updated_beam_radius =
      quantity<si::dimensionless>::from_value( x ) * L;
      
      // update observations to use the original model best-fit
      auto const observations = best_fit.model_phases;
      auto const frequencies = best_fit.frequencies;
      
      
      auto const alternative_best_fit =
      fit_all_but_laser::diffusivity_from_phases( frequencies, observations,
        slab, updated_beam_radius, detector_view_radius, steady_state_temperature,
        detector_wavelength );
      
      auto const error = alternative_best_fit.phase_goodness_of_fit ;
      return error;
    };

    auto const laser_best_fit = (best_fit.beam_radius / L ).value() ;
    auto const lowerbound = .5;
    auto const upperbound = 5.0;
    
    auto const ojb_ub = solve( gFunc, target, laser_best_fit, upperbound ) ;
    double soln_ub = ojb_ub.returnSoln();
    double soln_ub_pass = ojb_ub.pass;
    
    std::cout << soln_ub << "\t" << soln_ub_pass << "\n";

    auto const obj_lb = solve( gFunc, target, lowerbound, laser_best_fit ) ;
    double soln_lb = obj_lb.returnSoln();
    double soln_lb_pass = obj_lb.pass;
    
    std::cout << soln_lb << "\t" << laser_best_fit <<"\t" << soln_ub << "\n";
    std::cout << soln_ub_pass << "\t" << soln_lb_pass << "\n";
  }

  //uncertainty in diffusivity
  /// uncertainty in diffusivity
  {
    auto const gFunc =[&best_fit, &steady_state_temperature,
      &detector_wavelength, &beam_radius, &detector_view_radius]
    ( double const x ) noexcept -> double
    {
      // updated best-fit slab with perturbed parameter
      auto updated_slab = best_fit.bulk_slab;
      auto const updated_thermal_diffusivity =
      quantity<thermal_diffusivity>::from_value( x );
      updated_slab.set_diffusivity_update_rhoCp_hold_k(updated_thermal_diffusivity);
      
      // update observations to use the original model best-fit
      auto const observations = best_fit.model_phases;
      auto const frequencies = best_fit.frequencies;
      
     // auto const beam_radius = beam_radius;
     // auto const detector_view_radius = detector_view_radius;
            
      auto const alternative_best_fit =
      fit_all_but_diffusivity::diffusivity_from_phases( frequencies, observations,
        updated_slab, beam_radius, detector_view_radius, steady_state_temperature,
        detector_wavelength );
      
      auto const error = alternative_best_fit.phase_goodness_of_fit ;
      return error;
    };


    auto const diffusivity_best_fit =best_fit.bulk_slab.get_diffusivity().value();
    auto const lowerbound = diffusivity_best_fit / 1.2 ;
    auto const upperbound = diffusivity_best_fit / .5 ;

    auto const ojb_ub = solve( gFunc, target, diffusivity_best_fit, upperbound ) ;
    double soln_ub = ojb_ub.returnSoln();
    double soln_ub_pass = ojb_ub.pass;
    
    std::cout << soln_ub << "\t" << soln_ub_pass << "\n";
    
    auto const obj_lb = solve( gFunc, target, lowerbound, diffusivity_best_fit ) ;
    double soln_lb = obj_lb.returnSoln();
    double soln_lb_pass = obj_lb.pass;
    
    std::cout << soln_lb << "\t" << diffusivity_best_fit <<"\t" << soln_ub << "\n";
    std::cout << soln_ub_pass << "\t" << soln_lb_pass << "\n";

  // uncertainty bounds 2.229 to 2.402
  }

}

} // namespace phase_analysis
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal
