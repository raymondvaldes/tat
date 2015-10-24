//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 10/21/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit.hpp"
#include <cassert>
#include <vector>
#include <tuple>

#include "algorithm/algorithm.h"
#include "algorithm/vector/add.h"

#include "math/estimation/settings.h"
#include "math/estimation/lmdiff.hpp"
#include "math/estimation/constrained.hpp"

#include "thermal/emission/phases.h"
#include "thermal/model/complex/temperatures.h"
#include "thermal/model/oneLayer2D/finite_disk/emission/centered_point/frequency_sweep.hpp"

#include "electronics/filter/low-pass/RC-first-order/resistance.h"
#include "electronics/filter/low-pass/RC-first-order/capacitance.h"
#include "electronics/filter/low-pass/RC-first-order/time_constant.h"
#include "electronics/filter/low-pass/RC-first-order/phase_shifts_from_input.hpp"
#include "statistics/uncertainty_analysis/goodness_of_fit/goodness_of_fit.h"
#include "statistics/signal_processing/residuals/residual.h"

namespace thermal {
namespace analysis {
namespace oneLayer2D{
namespace finite_disk {
namespace centered_point {
namespace fit_a_s_RC {
namespace fit_all{

using electronics::filter::low_pass::RC_first_order::Resistance;
using electronics::filter::low_pass::RC_first_order::Capacitance;
using electronics::filter::low_pass::RC_first_order::Time_constant;
using electronics::filter::low_pass::RC_first_order::phase_shifts_from_input;

using math::estimation::x_limiter1;
using math::estimation::kx_limiter1;
using math::estimation::settings;
using math::estimation::lmdif;
using statistics::uncertainty_analysis::goodness_of_fit;
using std::vector;
using std::make_tuple;
using std::get;

using std::generate;
using namespace units;

using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::Best_fit;
using thermal::model::oneLayer2D::finite_disk::disk::emission::centered_point::frequency_sweep;

auto fit
(
  equipment::laser::Modulation_frequencies const & frequencies,
  emission::Phases const & experimental_phases,
  model::slab::Slab const & slab_initial,
  model::Optics const & optics_initial
)
noexcept -> estimate_parameters::phase_analysis::Best_fit
{
  assert( !frequencies.empty() );
  assert( !experimental_phases.empty() );
  assert( frequencies.size() == experimental_phases.size() );
  auto const size = frequencies.size();

  // RC parameter to fit
  auto const resisitance_i = Resistance( 10000 * ohms);
  auto const capacitance_i = Capacitance( 150. * picofarads );
  auto const RC_initial_value = Time_constant( resisitance_i * capacitance_i );
  

  //establish scaling factors
  auto const alpha_scale = slab_initial.thermal_diffusivity().value();
  auto const R_scale = slab_initial.radius().value();
  auto const RC_scale = RC_initial_value.value();

  auto const unity_ratio = 1.0;
  auto model_parameters = vector< double >
  {
    kx_limiter1( unity_ratio ) ,  // diffusivity ratio
    kx_limiter1( unity_ratio ) ,  // sample radius ratio
    kx_limiter1( unity_ratio )    // RC ratio
  };

  // parameter estimation algorithm
  auto const update_system_properties =
  [ &frequencies, alpha_scale, RC_scale, R_scale,&slab_initial, &optics_initial]
  ( const double * x ) noexcept
  {
    auto const alpha_value = x_limiter1( x[0] ) * alpha_scale ;
    auto const R_value = x_limiter1( x[1] ) * R_scale;
    auto const RC_value = x_limiter1( x[2] ) * RC_scale;
    
    auto const alpha = quantity< si::thermal_diffusivity>::from_value( alpha_value );
    auto const R = quantity< si::length>::from_value( R_value );
    auto const RC_time_constant =  quantity< electrical_time_constant >::from_value( RC_value );

    std::cout <<  alpha << "\t" << R << "\t" << RC_time_constant <<  "\n" ;
    
    auto slab_updated = slab_initial;
    slab_updated.set_radius( R );
    slab_updated.set_diffusivity_update_k_hold_rhoCp( alpha );
   
    auto optics_updated = optics_initial;
    
    auto const updated_elements =
    make_tuple( slab_updated, optics_updated, RC_time_constant ) ;
    
    return updated_elements ;
  };

  struct theoretical_modeling {
    emission::Phases observations;
    model::complex::Temperatures model_predictions;
    emission::Phases experimental_bias;
    emission::Phases calibrated_observations;
    
    theoretical_modeling(
      emission::Phases const & observations_,
      model::complex::Temperatures const & model_predictions_,
      emission::Phases const & experimental_bias_
    )
    : observations( observations_ ),
      model_predictions( model_predictions_ ),
      experimental_bias( experimental_bias_ ),
      calibrated_observations( algorithm::vector::add( observations, experimental_bias ) )
//      calibrated_observations(observations )  //enable this to ignore RC filter
    {};
  };

  auto const make_model_predictions =
  [ &frequencies, &experimental_phases, &update_system_properties ]
  ( const double * x ) noexcept
  {
    //check preconditions
    assert( x[0] > -800 );
    assert( x[1] > -800 );
    assert( x[2] > -800 );
    
    auto const t = update_system_properties( x );
    
    auto const slab = get< 0 >(t);
    auto const optics = get< 1 >(t);
    auto const RC = get<2>(t);

    auto const experimental_bias = phase_shifts_from_input( frequencies, RC );
    auto const model_predictions = frequency_sweep( slab, optics, frequencies );

    auto const output =
    theoretical_modeling( experimental_phases, model_predictions, experimental_bias );
    
    return output;
  };

  auto const minimization_equation =
  [ &make_model_predictions]
  ( const double *x, double *fvec ) noexcept
  {
    auto const theoreticalModeling = make_model_predictions( x ) ;
    auto const predictions = theoreticalModeling.model_predictions.phases();
    
    auto const observations = theoreticalModeling.calibrated_observations;

    //populate fvec
    using statistics::signal_processing::residual;    
    algorithm::transform( predictions, observations, fvec,
      [](auto const p, auto const o ) noexcept {
        return residual( p , o ).value();
      }  );
  };
  
  auto lmdif_settings = settings{};
  lmdif_settings.factor = 50 ;   // initial step size
  lmdif_settings.xtol = .00001;   // tolerance between x-iterates
  lmdif_settings.epsfcn = 1e-4; // tolerance of phase function
  lmdif(  minimization_equation, size, model_parameters, lmdif_settings ) ;

//////// prepare output
  auto const x =  model_parameters.data();
  auto const t = update_system_properties( x );
  auto const theoretical_modeling = make_model_predictions( x );

  auto const slab_fit = get< 0 >(t);
  auto const optics_fit = get< 1 >(t);
  auto const RC_fit = get< 2 >(t);

  auto const phase_predictions = theoretical_modeling.model_predictions.phases();
  auto const calibrated_observations = theoretical_modeling.calibrated_observations;
  auto const phase_goodness_of_fit = goodness_of_fit( calibrated_observations , phase_predictions );

  auto const result = Best_fit( slab_fit, optics_fit, phase_goodness_of_fit );
  
  std::cout << "\n" << result.phase_goodness_of_fit  << "\n";
  
 return result;
}

} } } } } } }
