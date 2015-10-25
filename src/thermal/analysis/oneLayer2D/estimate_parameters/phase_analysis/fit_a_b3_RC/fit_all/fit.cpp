//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 9/8/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit.hpp"

#include "algorithm/algorithm.h"
#include <iostream>
#include <tuple>
#include "thermal/model/optics/optics.h"
#include "thermal/model/oneLayer2D/model_selection.h"

#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/b.h"
#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/offset_point/frequency_sweep.h"
using thermal::model::oneLayer2D::thermal_emission::offset_point::frequency_sweep;

#include "math/estimation/constrained.hpp"
#include "math/estimation/settings.h"
#include "math/estimation/lmdiff.hpp"
#include "statistics/uncertainty_analysis/goodness_of_fit/goodness_of_fit.h"
#include "electronics/filter/low-pass/RC-first-order/phase_shifts_from_input.hpp"
#include "statistics/uncertainty_analysis/goodness_of_fit/goodness_of_fit.h"
#include "math/complex/extract_phases_from_properties.h"
#include "math/complex/adjust_phase.h"
#include "math/complex/adjust_phases.h"
#include "algorithm/vector/add.h"

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace phase_analysis{
namespace fit_a_b3_RC{
namespace fit_all{

using namespace units;

using algorithm::for_each;
using std::vector;
using math::estimation::x_limiter1;
using math::estimation::x_limiter2;
using math::estimation::kx_limiter1;
using math::estimation::kx_limiter2;
using math::estimation::x_to_k_constrained_from_0_to_1;
using math::estimation::k_to_x_constrained_from_0_to_1;
using math::estimation::settings;
using electronics::filter::low_pass::RC_first_order::phase_shifts_from_input;

using thermal::model::oneLayer2D::dimensionless::b;
using std::generate;
using std::make_tuple;
using std::tie;
using std::get;
using math::complex::extract_phases_from_properties;
using statistics::uncertainty_analysis::goodness_of_fit;

auto fit
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const slab_initial,
  units::quantity< units::si::length> const beam_radius,
  units::quantity< units::si::length > const detector_offset_point
)
noexcept -> Best_fit
{
  //establish preconditions
  assert( frequencies.size() > 0 );
  assert( frequencies.size() == observations.size() ) ;
  assert( beam_radius.value() > 0 );
  assert( detector_offset_point.value() > 0 );
  

  // establish nondimensional fitting parameters
  auto const L = slab_initial.thickness() ;
  auto const alpha = slab_initial.thermal_diffusivity();
  auto const k = slab_initial.thermal_conductivity();
  
  auto const b1_i = b( beam_radius, L );
  auto const b3_i = b( detector_offset_point, L );

  auto const deltaT = quantity< si::temperature > ( 1.0 * kelvin );
  auto const alpha_scale = alpha.value();

  // RC parameter to fit
  auto const initial_resisitance = quantity< electrical_resistance >( 10000 * ohms);
  auto const initial_capacitance = quantity< electrical_capacitance >( 150. * picofarads );
  auto const RC_initial_value = quantity< electrical_time_constant >( initial_resisitance * initial_capacitance );
  auto const RC_scale = RC_initial_value.value();

  // establish parameters to fit with initial values
  auto const b3min = 0.0005;
  auto const b3max = 2.;
  auto const unity_ratio = 1.0;
  
  auto model_parameters = vector< double >
  {
    kx_limiter1( unity_ratio ) ,  // diffusivity ratio
    kx_limiter2( b3_i.value(), b3min, b3max ),
    kx_limiter1( unity_ratio )
  };
  
  // parameter estimation algorithm
  auto const update_system_properties =
  [ frequencies, &alpha_scale, b1_i, b3min, b3max, &L, &RC_scale ]
  ( const double * x )
  noexcept
  {
    auto const alpha_value = x_limiter1( x[0] ) * alpha_scale ;
    auto const alpha = quantity< si::thermal_diffusivity >::from_value( alpha_value );
    auto const b3 =  quantity< si::dimensionless >( x_limiter2( x[1], b3min, b3max ) ); //  laser radius

    auto const RC_pos = x_limiter1( x[2] );
    auto const RC_value = RC_pos * RC_scale;
    auto const RC_time_constant =  quantity< electrical_time_constant >::from_value( RC_value ); //  experiment phase time-constant

    std::cout <<  alpha << "\t" << b1_i *L << "\t" << b3 *L << "\t" << RC_time_constant <<  "\n" ;
    auto const updated_elements = make_tuple( alpha, b3, RC_time_constant ) ;
    return updated_elements ;
  };


  struct theoretical_modeling {
    std::vector< units::quantity< units::si::plane_angle > > observations;
    std::vector< math::complex::properties< units::si::temperature > > model_predictions;
    std::vector< units::quantity< units::si::plane_angle > > experimental_bias;
    std::vector< units::quantity< units::si::plane_angle > > calibrated_observations;
    
    theoretical_modeling(
      std::vector< units::quantity< units::si::plane_angle > > const & observations_,
      std::vector< math::complex::properties< units::si::temperature > > const & model_predictions_,
      std::vector< units::quantity< units::si::plane_angle > > const & experimental_bias_
    )
    : observations( observations_ ),
      model_predictions( model_predictions_ ),
      experimental_bias( experimental_bias_ ),
      calibrated_observations( algorithm::vector::add( observations, experimental_bias ) )
//      calibrated_observations(observations )
    {};
  };

  auto const make_model_predictions =
  [ &observations, &frequencies, &L, &update_system_properties, &deltaT, b1_i ]
  ( const double * x ) noexcept
  {
    //check preconditions
    assert( x[0] > -800 );
    assert( x[1] > -800 );
    assert( x[2] > -800 );
    
    auto const t = update_system_properties( x );
    
    auto const alpha = get< 0 >(t);
    auto const b3 = get< 1 >(t);
    auto const RC_time_constant = get<2>(t);

    auto const experimental_bias =
    phase_shifts_from_input( frequencies, RC_time_constant );
    
    auto const model_predictions =
    frequency_sweep( b1_i, deltaT, b3 , frequencies, L, alpha ) ;

    auto const output =
    theoretical_modeling( observations, model_predictions, experimental_bias );
    
    return output;
  };
  
  auto const number_of_points_to_Fit = frequencies.size();

  auto const minimization_equation =
  [ number_of_points_to_Fit , &make_model_predictions]
  ( const double *x, double *fvec ) noexcept
  {
    auto const theoreticalModeling = make_model_predictions( x ) ;
    auto const predictions = theoreticalModeling.model_predictions;
    
    auto const observations = theoreticalModeling.calibrated_observations;
    
    auto const residual = [ & ]( const int i ) noexcept {
      return ( predictions[i].phase  -  observations[i] ).value() ;
    } ;

    auto i = 0;
    generate( fvec, fvec + number_of_points_to_Fit , [&]() noexcept {
      return residual( i++ );
    } ) ;
  };

  auto lmdif_settings = settings{};
  lmdif_settings.factor = 10 ;   // initial step size
  lmdif_settings.xtol = .00001;   // tolerance between x-iterates
  lmdif_settings.epsfcn = 1e-4; // tolerance of phase function

  lmdif(  minimization_equation, number_of_points_to_Fit,
          model_parameters, lmdif_settings ) ;

  auto const x = model_parameters.data();
  auto const t = update_system_properties( x );
  auto const alpha_fit = get< 0 >(t);
  auto const b3 = get< 1 >(t);
  auto const RC_time_constant_fitted = get< 2 >(t);

  auto const model_predictions = make_model_predictions( x );
  auto const phase_predictions = extract_phases_from_properties( model_predictions.model_predictions  ) ;
  auto const fitted_slab = thermal::model::slab::Slab( L , alpha_fit , k ) ;
  auto const calibrated_observations = model_predictions.calibrated_observations;
  auto const phase_goodness_of_fit = goodness_of_fit( calibrated_observations , phase_predictions );
  
  
  auto const l_r = thermal::equipment::laser::Beam_radius::from_value(42);
  auto const l_i = thermal::equipment::laser::Beam_intensity::from_value(42);
  auto const d_r = thermal::equipment::detector::View_radius::from_value(42);
  auto const l_m = thermal::equipment::laser::Modulation_depth::from_value(42);
  
  auto const optics_fitted =
  thermal::model::Optics( l_r, l_i, d_r, l_m );
  
  auto const conduction_model = thermal::model::oneLayer2D::Conduction_model::infinite_disk;
  auto const detector_model = thermal::model::oneLayer2D::Detector_model::center_with_view;
  
  auto const result = Best_fit( conduction_model, detector_model,
    fitted_slab, optics_fitted, phase_goodness_of_fit );
  
  std::cout << "\n" << result.phase_goodness_of_fit  << "\n";
  
 return result;
}


auto fit
(
  thermal::experimental::observations::Slab const & initial_slab,
  units::quantity< units::si::length > const detector_offset_point
)
noexcept -> Best_fit
{
  auto const frequencies = initial_slab.frequencies;
  auto const observations = initial_slab.phases;
  auto const slab_initial = initial_slab.disk;
  auto const beam_radius = initial_slab.beam_radius;

  auto const best_fit = fit(  frequencies, observations,
                              slab_initial, beam_radius,
                              detector_offset_point ) ;
  
  return best_fit;
}

} // namespace fit_all
} // namespace fit_a_b3_RC
} // namespace phase_analysis
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal
