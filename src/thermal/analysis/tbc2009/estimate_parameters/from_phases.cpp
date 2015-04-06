//
//  estimate_properties.cpp
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <utility>
#include <tuple>
#include <algorithm>
#include <iostream>

#include "thermal/model/tbc2009/average_surface_phases.h"
#include "thermal/model/tbc2009/dimensionless/coating_from_dimensionless.h"
#include "thermal/model/tbc2009/dimensionless/a.h"
#include "thermal/model/tbc2009/dimensionless/b.h"
#include "thermal/model/tbc2009/dimensionless/gamma.h"
#include "thermal/analysis/tbc2009/estimate_parameters/from_phases.h"
#include "thermal/define/lthermal.h"

#include "math/estimation/constrained.hpp"
#include "math/estimation/settings.h"
#include "math/estimation/lmdiff.hpp"
#include "algorithm/vector/split_vector_of_pairs.h"

namespace thermal {
namespace analysis {
namespace tbc2009 {
namespace estimate_parameters{

using namespace units;
using namespace model::tbc2009;
using dimensionless::ThermalProperties;
using dimensionless::coating_from_dimensionless;
using thermal::define::thermalPenetrations_from_frequencies;
using std::vector;
using math::estimation::x_limiter1;
using math::estimation::kx_limiter1;
using math::estimation::x_to_k_constrained_from_0_to_1;
using math::estimation::k_to_x_constrained_from_0_to_1;



using math::estimation::settings;
using std::generate;
using std::make_tuple;
using std::get;

Best_fit::Best_fit
(
  units::quantity< units::si::length > const L_coat_,
  units::quantity< units::si::dimensionless > const view_radius_,
  thermal::model::slab::Slab const substrate_slab,
  model::tbc2009::dimensionless::HeatingProperties const & hp_,
  model::tbc2009::dimensionless::ThermalProperties const & tp_,
 
  std::vector< units::quantity<units::si::frequency> > const frequencies_,
  std::vector< units::quantity< units::si::plane_angle > > const model_phases_
) noexcept :
  view_radius( view_radius_ * L_coat_ ),
  hp( hp_ ),
  tp( tp_ ),
  coating_slab( coating_from_dimensionless( L_coat_, tp, substrate_slab ) ),
  frequencies( frequencies_ ),
  ls( thermalPenetrations_from_frequencies(
        frequencies, coating_slab.get_diffusivity() , L_coat_ ) ),
  model_phases( model_phases_ )
{}

auto from_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const slab_initial,
  thermal::model::slab::Slab const substrate,

  model::tbc2009::dimensionless::HeatingProperties const & hp_initial,
  units::quantity< units::si::length > const detector_view_radius
) noexcept -> Best_fit
{
  //establish preconditions
  assert( frequencies.size() > 0 );
  assert( frequencies.size() == observations.size() ) ;
  assert( detector_view_radius.value() > 0 ) ;

  // establish nondimensional fitting parameters
  auto const L_coat = slab_initial.characteristic_length;
  auto const alpha_coat = slab_initial.get_diffusivity();
  auto const alpha_sub = substrate.get_diffusivity();
  auto const a_sub_i = dimensionless::a( alpha_sub, alpha_coat ) ;
  
  auto const e_coat = slab_initial.get_effusivity();
  auto const e_sub = substrate.get_effusivity();
  auto const gamma_i = dimensionless::gamma( e_coat, e_sub ) ;
  auto const b_i = hp_initial.b ;
  auto const b2_i = dimensionless::b( detector_view_radius, L_coat );

  // establish parameters to fit with initial values
  auto model_parameters = vector< double >
  {
    kx_limiter1( a_sub_i.value() ) ,  // diffusivity ratio
    kx_limiter1( gamma_i.value() ) ,  // effusivity ratio
    kx_limiter1( b_i.value() ) ,      // beam radius
    kx_limiter1( b2_i.value() ),      // detector radius
    x_to_k_constrained_from_0_to_1( hp_initial.Lambda.value() ),  // optical penetration
//    x_to_k_constrained_from_0_to_1( hp_initial.R0.value() ) ,     // surface reflectivity
//    x_to_k_constrained_from_0_to_1( hp_initial.R1.value() )      // interface reflectivity
  };
  
  // parameter estimation algorithm
  auto const number_of_points_to_Fit = frequencies.size();
  
  auto const update_system_properties = [ &hp_initial ] ( const double * x )
  noexcept
  {
    auto const a_sub = quantity<si::dimensionless>( x_limiter1( x[0] ) );
    auto const gamma =  quantity<si::dimensionless>( x_limiter1( x[1] ) );
    auto const b =  quantity<si::dimensionless>( x_limiter1( x[2] ) );  //  beam radius
    auto const b2 =  quantity<si::dimensionless>( x_limiter1( x[3] ) ); //  detector radius


    auto const Lambda =
    quantity<si::dimensionless>( k_to_x_constrained_from_0_to_1( x[4] ) );
    
    auto const R0 =hp_initial.R0;
  //  quantity<si::dimensionless>( k_to_x_constrained_from_0_to_1( x[5] ) );
    
    auto const R1 = hp_initial.R1;
  //  quantity<si::dimensionless>( k_to_x_constrained_from_0_to_1( x[6] ) );
    
    std::cout << a_sub << "\t" << gamma << "\t" << b << "\t" << b2 << "\t" << Lambda <<"\t";
    std::cout << R0 << "\t" << R1 << "\n";
//    auto const Lambda = hp_initial.Lambda; // quantity<si::dimensionless>(x_limiter1(x[4]))
//    auto const R0 = hp_initial.R0;  // quantity<si::dimensionless>(x_limiter1(x[5]))
//    auto const R1 = hp_initial.R1;  // quantity<si::dimensionless>(x_limiter1(x[6]))

    auto const tp = dimensionless::ThermalProperties( gamma, a_sub );
    auto const hp = dimensionless::HeatingProperties( Lambda, R0, R1 , b);

    auto const updated_elements = make_tuple( b2, hp, tp ) ;
    return updated_elements ;
  };

  auto const make_model_predictions =
  [ &frequencies, &L_coat, &substrate, &update_system_properties ]
  ( const double * x ) noexcept
  {
    auto const t = update_system_properties( x );
    auto const b2 = get< 0 >(t);
    auto const hp = get< 1 >(t);
    auto const tp = get< 2 >(t);
    
    auto const predictions =
    average_surface_phases(
      b2, frequencies, hp, tp, L_coat, substrate.get_diffusivity() );
    return predictions;
  };

  auto const minimization_equation =
  [ & ] ( const double *x, double *fvec ) noexcept
  {
    auto const predictions = make_model_predictions( x );
    
    auto const residual = [ & ]( const int i ) noexcept {
      return ( predictions[i]  -  observations[i] ).value() ;
    } ;

    auto i = 0;
    generate( fvec, fvec + number_of_points_to_Fit , [&]() noexcept {
      return residual( i++ );
    } ) ;
  };

  auto lmdif_settings = settings{};
  lmdif_settings.factor = 1.;

  lmdif(  minimization_equation, number_of_points_to_Fit,
          model_parameters, lmdif_settings );

  auto const x = model_parameters.data();
  auto const t = update_system_properties( x );
  auto const b2 = get< 0 >(t);
  auto const hp = get< 1 >(t);
  auto const tp = get< 2 >(t);
  auto const model_predictions = make_model_predictions( x );

  auto const result =
  Best_fit( L_coat, b2, substrate, hp, tp, frequencies, model_predictions );
  
  return result;
}

auto from_phases
(
  std::pair<
  std::vector< units::quantity< units::si::frequency > > ,
  std::vector< units::quantity< units::si::plane_angle > > > const & o,
  thermal::model::slab::Slab const & slab_initial,
  thermal::model::slab::Slab const & slab_substrate,
  model::tbc2009::dimensionless::HeatingProperties const & hp_initial,
  units::quantity< units::si::length > const & detector_view_radius
) noexcept -> Best_fit
{
  assert( o.first.size() == o.second.size() );
  assert( o.first.size() > 0);

  return from_phases(
    o.first, o.second ,
    slab_initial, slab_substrate, hp_initial, detector_view_radius );
}


} // namespace estimate_parameters
} // namespace tbc2009
} // namespace analysis
} // namespace thermal
