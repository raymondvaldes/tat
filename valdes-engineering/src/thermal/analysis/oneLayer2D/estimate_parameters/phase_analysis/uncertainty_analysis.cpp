//
//  uncertainty_analysis.cpp
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <iostream>
#include <cassert>
#include "math/bisection.hpp"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/uncertainty_analysis.h"

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all/diffusivity_from_phases.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_detectorRadius/diffusivity_from_phases.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_diffusivity/diffusivity_from_phases.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_laser/diffusivity_from_phases.h"
#include "thermal/model/oneLayer2D/generator/disk.hpp"
#include "thermal/model/oneLayer2D/model_selection.h"

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace phase_analysis{

using namespace units;
using math::solve;
using thermal::model::oneLayer2D::generator::Disk;
using model::oneLayer2D::Conduction_model;
using model::oneLayer2D::Detector_model;

auto uncertainty_analysis(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const slab_initial,
  units::quantity< units::si::length> const beam_radius,
  units::quantity< units::si::length > const detector_view_radius
) noexcept -> void
{
  assert( beam_radius > 0 * meters);
  assert( detector_view_radius > 0 * meters);
  assert( frequencies.size() == observations.size() );
  assert( !frequencies.empty() );
  
  auto const best_fit = fit_all::fit( frequencies, observations,
  slab_initial, beam_radius, detector_view_radius );
  auto const target = best_fit.phase_goodness_of_fit;
  
  //uncertainty in diffusivity
  /// uncertainty in diffusivity
  {
    auto const gFunc =[&best_fit, &beam_radius, &detector_view_radius, &frequencies]
    ( double const x ) noexcept -> double
    {
      // updated best-fit slab with perturbed parameter
      auto updated_slab = best_fit.slab;
      auto const updated_thermal_diffusivity =
      quantity<thermal_diffusivity>::from_value( x );
      updated_slab.set_diffusivity_update_rhoCp_hold_k(updated_thermal_diffusivity);
      
      // update observations to use the original model best-fit
      auto const conduction_model = Conduction_model::infinite_disk;
      auto const detector_model = Detector_model::center_with_view;
      auto const model_generator =
      Disk ( conduction_model, detector_model, best_fit.slab, best_fit.optics );
      
      auto const observations_T = model_generator.evaluate( frequencies );
      auto const observations = observations_T.phases();
//      auto const frequencies = best_fit.frequencies;
      
     // auto const beam_radius = beam_radius;
     // auto const detector_view_radius = detector_view_radius;
            
      auto const alternative_best_fit =
      fit_all_but_diffusivity::diffusivity_from_phases( frequencies, observations,
        updated_slab, beam_radius, detector_view_radius );
      
      auto const error = alternative_best_fit.phase_goodness_of_fit ;
      return error;
    };


    auto const diffusivity_best_fit =best_fit.slab.thermal_diffusivity().value();
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
  
  /// uncertainty in detector_radius
  {
    auto const L = best_fit.slab.thickness();
  
    auto const gFunc =[&best_fit, &beam_radius, &detector_view_radius, &slab_initial, &frequencies]
    ( double const x ) noexcept -> double
    {
      auto slab = best_fit.slab;
      slab.set_diffusivity_update_rhoCp_hold_k( slab_initial.thermal_diffusivity());
      
      // updated best-fit slab with perturbed parameter
      auto const L = slab.thickness();
      auto const updated_detectorRadius =
      quantity<si::dimensionless>::from_value( x ) * L;
      
      // update observations to use the original model best-fit
      auto const conduction_model = Conduction_model::infinite_disk;
      auto const detector_model = Detector_model::center_with_view;
      auto const model_generator =
      Disk ( conduction_model, detector_model, best_fit.slab, best_fit.optics );
      
      auto const observations_T = model_generator.evaluate( frequencies );
      auto const observations = observations_T.phases();
      
      
      auto const alternative_best_fit =
      fit_all_but_detectorRadius::diffusivity_from_phases( frequencies, observations,
        slab, beam_radius, updated_detectorRadius );
      
      auto const error = alternative_best_fit.phase_goodness_of_fit ;
      return error;
    };
    auto const detectorR_best_fit = (best_fit.optics.view_radius / L).value();
//    auto const detectorR_best_fit = (best_fit.view_radius / L ).value()  ;
    auto const lowerbound = 0.0501 ;
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
    auto const L = best_fit.slab.thickness();
  
    auto const gFunc =[&best_fit, &beam_radius, &detector_view_radius, &slab_initial, &L, &frequencies]
    ( double const x ) noexcept -> double
    {
      auto slab = best_fit.slab;
      slab.set_diffusivity_update_rhoCp_hold_k( slab_initial.thermal_diffusivity());
      
      // updated best-fit slab with perturbed parameter
      auto const updated_beam_radius =
      quantity<si::dimensionless>::from_value( x ) * L;
      
      // update observations to use the original model best-fit
      auto const conduction_model = Conduction_model::infinite_disk;
      auto const detector_model = Detector_model::center_with_view;
      auto const model_generator =
      Disk ( conduction_model, detector_model, best_fit.slab, best_fit.optics );
      
      auto const observations_T = model_generator.evaluate( frequencies );
      auto const observations = observations_T.phases();
      
      
      auto const alternative_best_fit =
      fit_all_but_laser::diffusivity_from_phases( frequencies, observations,
        slab, updated_beam_radius, detector_view_radius );
      
      auto const error = alternative_best_fit.phase_goodness_of_fit ;
      return error;
    };

    auto const laser_best_fit = (best_fit.optics.laser_radius / L ).value() ;
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



}

} // namespace phase_analysis
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal
