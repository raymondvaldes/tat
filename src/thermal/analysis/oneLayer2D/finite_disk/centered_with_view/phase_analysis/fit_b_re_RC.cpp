//
////
////  fit.cpp
////  tat
////
////  Created by Raymond Valdes on 10/19/15.
////  Copyright © 2015 Raymond Valdes. All rights reserved.
////
//
//#include "fit_b_re_RC.hpp"
//
//#include <cassert>
//#include <vector>
//#include <tuple>
//#include <cmath>
//
//#include "math/estimation/constrained.hpp"
//#include "electronics/filter/low-pass/RC-first-order/resistance.h"
//#include "electronics/filter/low-pass/RC-first-order/capacitance.h"
//#include "theoretical_modeling.hpp"
//#include "make_minimization_equation.hpp"
//#include "fitting_algorithm.hpp"
//
//namespace thermal { 
//namespace analysis { 
//namespace oneLayer2D { 
//namespace finite_disk { 
//namespace centered_with_view {
//namespace phase_analysis{
//
//using electronics::filter::low_pass::RC_first_order::Resistance;
//using electronics::filter::low_pass::RC_first_order::Capacitance;
//using electronics::filter::low_pass::RC_first_order::Time_constant;
//using math::estimation::x_limiter1;
//using math::estimation::kx_limiter1;
//using std::vector;
//using std::make_tuple;
//using namespace units;
//
//inline auto update_system_properties_generator(
//  model::slab::Slab const & slab_initial,
//  model::Optics const & optics_initial
//) noexcept ->
//  std::pair< std::vector<double> ,
//    std::function<
//    std::tuple<
//      model::slab::Slab,
//      model::Optics,
//      electronics::filter::low_pass::RC_first_order::Time_constant >( const double * x)> >
//{
//  auto const unity_ratio = 1.0;
//  auto model_parameters = vector< double >
//  {
//    kx_limiter1( unity_ratio ) ,  // diffusivity ratio
//    kx_limiter1( unity_ratio ) ,  // sample radius ratio
//    kx_limiter1( unity_ratio ) ,  // detector radius ratio
//    kx_limiter1( unity_ratio )    // RC ratio
//  };
//
//
//  //establish scaling factors
//  auto const resisitance_i = Resistance( 10000 * ohms);
//  auto const capacitance_i = Capacitance( 150. * picofarads );
//  auto const RC_initial_value = Time_constant( resisitance_i * capacitance_i );
//  auto const alpha_scale = slab_initial.thermal_diffusivity().value();
//  auto const R_scale = slab_initial.radius().value();
//  auto const re_scale = optics_initial.view_radius.value();
//  auto const RC_scale = RC_initial_value.value();
//
//  // parameter estimation algorithm
//  auto const update_system_properties =
//  [ alpha_scale, RC_scale, R_scale ,
//    re_scale, &slab_initial, &optics_initial]
//  ( const double * x ) noexcept
//  {
//    auto const alpha_value =  x_limiter1( x[0] ) * alpha_scale ;
//    auto const R_value =      x_limiter1( x[1] ) * R_scale;
//        auto const Re_value = x_limiter1( x[2] ) * re_scale;
//    auto const RC_value =     x_limiter1( x[3] ) * RC_scale;
//
//    assert( isnormal( alpha_value ) );
//    assert( isnormal( R_value ) );
//    assert( isnormal( Re_value ) );
//    assert( isnormal( RC_value ) );
//    
//    auto const alpha = quantity< si::thermal_diffusivity>::from_value( alpha_value );
//    auto const R = quantity< si::length>::from_value( R_value );
//    auto const Re = quantity< si::length>::from_value( Re_value );
//    auto const RC_time_constant =  quantity< electrical_time_constant >::from_value( RC_value );
//
//    std::cout <<  alpha << "\t" << R<< "\t" << Re << "\t" << RC_time_constant <<  "\n" ;
//    
//    auto slab_updated = slab_initial;
//      slab_updated.set_diffusivity_update_k_hold_rhoCp( alpha );
//      slab_updated.set_radius( R );
//   
//    auto optics_updated = optics_initial;
//    optics_updated.view_radius = Re;
//    
//    auto const updated_elements =
//    make_tuple( slab_updated, optics_updated, RC_time_constant ) ;
//    
//    return updated_elements ;
//  };
//
//  return make_pair( model_parameters, update_system_properties );
//};
//
//auto fit_b_re_RC
//(
//  equipment::laser::Modulation_frequencies const & frequencies,
//  emission::Phases const & exp_phases,
//  model::slab::Slab const & slab_initial,
//  model::Optics const & optics_initial
//)
//noexcept -> estimate_parameters::phase_analysis::Best_fit
//{
//  assert( !frequencies.empty() );
//  assert( !exp_phases.empty() );
//  assert( frequencies.size() == exp_phases.size() );
//
//  // parameter estimation algorithm
//  auto const model =
//  update_system_properties_generator( slab_initial, optics_initial );
//  
//  auto m_parameters = model.first;
//  auto m_evaluate = model.second;
//  
//  auto const result =
//  fitting_algorithm( frequencies, exp_phases, m_parameters , m_evaluate  );
//
//  
// return result;
//}
//
//} } } } } }
