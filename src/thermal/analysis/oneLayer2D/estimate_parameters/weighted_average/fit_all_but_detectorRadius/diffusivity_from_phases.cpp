////
////  diffusivity_from_phases.cpp
////  tat
////
////  Created by Raymond Valdes on 5/4/15.
////  Copyright (c) 2015 Raymond Valdes. All rights reserved.
////
//
//#include "thermal/analysis/oneLayer2D/estimate_parameters/weighted_average/fit_all_but_detectorRadius/diffusivity_from_phases.h"
//#include "algorithm/algorithm.h"
//#include <iostream>
//#include <tuple>
//
//#include "thermal/model/oneLayer2D/dimensionless/b.h"
//#include "thermal/model/oneLayer2D/average/weighted_avg_surface_phases_amplitudes.h"
//
//#include "math/estimation/constrained.hpp"
//#include "math/estimation/settings.h"
//#include "math/estimation/lmdiff.hpp"
//
//#include "statistics/uncertainty_analysis/goodness_of_fit/goodness_of_fit.h"
//
//#include "math/complex/extract_phases_from_properties.h"
//
//namespace thermal{
//namespace analysis {
//namespace oneLayer2D {
//namespace estimate_parameters{
//namespace weighted_average{
//namespace fit_all_but_detectorRadius{
//
//using namespace units;
//
//using algorithm::for_each;
//using std::vector;
//using math::estimation::x_limiter1;
//using math::estimation::x_limiter2;
//using math::estimation::kx_limiter1;
//using math::estimation::kx_limiter2;
//
//using math::estimation::x_to_k_constrained_from_0_to_1;
//using math::estimation::k_to_x_constrained_from_0_to_1;
//using thermal::model::oneLayer2D::dimensionless::b;
//using thermal::model::oneLayer2D::average::weighted_avg_surface_phases_amplitudes;
//using math::estimation::settings;
//using std::generate;
//using std::make_tuple;
//using std::tie;
//using std::get;
//using math::complex::extract_phases_from_properties;
//using statistics::uncertainty_analysis::goodness_of_fit;
//
//auto diffusivity_from_phases
//(
//  std::vector< units::quantity< units::si::frequency > > const & frequencies,
//  std::vector< units::quantity< units::si::plane_angle > > const & observations,
//  thermal::model::slab::Slab const slab_initial,
//  units::quantity< units::si::length> const beam_radius,
//  units::quantity< units::si::length > const detector_view_radius,
//  units::quantity< units::si::temperature> const steady_state_temperature,
//  units::quantity< units::si::wavelength> const detector_wavelength
//) noexcept -> Best_fit
//{
//  //establish preconditions
//  assert( frequencies.size() > 0 );
//  assert( frequencies.size() == observations.size() ) ;
//  assert( detector_view_radius.value() > 0 ) ;
//
//  // establish nondimensional fitting parameters
//  auto const L = slab_initial.characteristic_length;
//  auto const alpha = slab_initial.get_diffusivity();
//  auto const k = slab_initial.get_conductivity();
//  
//  auto const b1_i = b( beam_radius, L );
//  auto const b2 = b( detector_view_radius, L );
//  auto const deltaT = quantity< si::temperature > ( 1.0 * kelvin );
//
//
//  // establish parameters to fit with initial values
//  auto model_parameters = vector< double >
//  {
//    kx_limiter1( alpha.value() ) ,  // diffusivity ratio
//    kx_limiter2( b1_i.value(), 0, 5.0 )
//  };
//  
//  // parameter estimation algorithm
//  auto const number_of_points_to_Fit = frequencies.size();
//  
//  auto const update_system_properties = [&b2] ( const double * x )
//  noexcept
//  {
//    auto const alpha = quantity<si::thermal_diffusivity>::from_value( x_limiter1( x[0] ) );
//    auto const b1 =  quantity<si::dimensionless>( x_limiter2( x[1], 0.0, 5.0 ) ); //  detector radius
//
//    std::cout << alpha << "\t" << b1 << "\t" << b2 << "\n" ;
//    auto const updated_elements = make_tuple( alpha, b1 ) ;
//    return updated_elements ;
//  };
//
//  auto const make_model_predictions =
//  [ &frequencies, &L, &update_system_properties, &deltaT, &b2,
//    &steady_state_temperature, &detector_wavelength]
//  ( const double * x ) noexcept
//  {
//    auto const t = update_system_properties( x );
//    
//    auto const alpha = get< 0 >(t);
//    auto const b1 = get< 1 >(t);
//    
//    auto const predictions =
//    weighted_avg_surface_phases_amplitudes(
//      b1, deltaT, b2, frequencies, L, alpha,
//      steady_state_temperature,
//      detector_wavelength );
//    
//    return predictions;
//  };
//
//  auto const minimization_equation =
//  [ & ] ( const double *x, double *fvec ) noexcept
//  {
//    auto const predictions = make_model_predictions( x );
//    
//    auto const residual = [ & ]( const int i ) noexcept {
//      return ( predictions[i].phase  -  observations[i] ).value() ;
//    } ;
//
//    auto i = 0;
//    generate( fvec, fvec + number_of_points_to_Fit , [&]() noexcept {
//      return residual( i++ );
//    } ) ;
//  };
//
//  auto lmdif_settings = settings{};
//  lmdif_settings.factor = 10;
//
//  lmdif(  minimization_equation, number_of_points_to_Fit,
//          model_parameters, lmdif_settings );
//
//  auto const x = model_parameters.data();
//  auto const t = update_system_properties( x );
//  auto const alpha_fit = get< 0 >(t);
//  auto const b1 = get< 1 >(t);
//  
//  auto const model_predictions = make_model_predictions( x );
//  auto const phase_predictions = extract_phases_from_properties( model_predictions  ) ;
//  auto const fitted_slab = thermal::model::slab::Slab( L , alpha_fit , k ) ;
//  auto const phase_goodness_of_fit = goodness_of_fit( observations , phase_predictions );
//  
//  
//  //for_each( phases, []( auto const p) { std::cout << p << "\n";} );
//  
//  auto const result =
//  Best_fit( fitted_slab, b2, b1, frequencies, phase_predictions, phase_goodness_of_fit );
//  
//  return result;
//}
//
//} // namespace
//} // namespace fit_all_but_laser
//} // namespace estimate_parameters
//} // namespace oneLayer2D
//} // namespace analysis
//} // namespace thermal
