//
//  diffusivity_from_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 4/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <algorithm>
#include <iostream>
#include <tuple>

#include "thermal/analysis/oneLayer2D/offset_detector/estimate_parameters/diffusivity_from_phases.h"
#include "thermal/model/oneLayer2D/offset_detector/average_surface_phases_amplitudes.h"

#include "thermal/define/lthermal.h"
#include "thermal/model/oneLayer2D/dimensionless/b.h"
#include "math/estimation/constrained.hpp"
#include "math/estimation/settings.h"
#include "math/estimation/lmdiff.hpp"
#include "math/complex/extract_phases_from_properties.h"

namespace thermal {
namespace analysis {
namespace oneLayer2D {
namespace offset_detector{
namespace estimate_parameters{

using namespace units;

using thermal::define::thermalPenetrations_from_frequencies;
using std::vector;
using math::estimation::x_limiter1;
using math::estimation::x_limiter2;
using math::estimation::kx_limiter1;
using math::estimation::kx_limiter2;

using math::estimation::x_to_k_constrained_from_0_to_1;
using math::estimation::k_to_x_constrained_from_0_to_1;
using thermal::model::oneLayer2D::dimensionless::b;
using thermal::model::oneLayer2D::offset_detector::average_surface_phases_amplitudes;
using math::estimation::settings;
using std::generate;
using std::make_tuple;
using std::get;
using math::complex::extract_phases_from_properties;

Best_fit::Best_fit
(
  thermal::model::slab::Slab const slab_,

  units::quantity< units::si::dimensionless > const view_radius_nd,
  units::quantity< units::si::dimensionless> const b,
 
  std::vector< units::quantity<units::si::frequency> > const frequencies_,
  std::vector< units::quantity< units::si::plane_angle > > const model_phases_
) noexcept :
  bulk_slab( slab_ ),
  view_radius( view_radius_nd * bulk_slab.characteristic_length ),
  beam_radius( b * bulk_slab.characteristic_length ),

  frequencies( frequencies_ ),
  ls( thermalPenetrations_from_frequencies(
        frequencies,
        bulk_slab.get_diffusivity() ,
        bulk_slab.characteristic_length ) ),
  model_phases( model_phases_ )
{}

auto diffusivity_from_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const slab_initial,
  units::quantity< units::si::length> const beam_radius,
  units::quantity< units::si::length > const detector_view_radius,
  units::quantity< units::si::length > const detector_offset_i
) noexcept -> Best_fit
{
  //establish preconditions
  assert( frequencies.size() > 0 );
  assert( frequencies.size() == observations.size() ) ;
  assert( detector_view_radius.value() > 0 ) ;

  // establish nondimensional fitting parameters
  auto const L = slab_initial.characteristic_length;
  auto const alpha = slab_initial.get_diffusivity();
  auto const k = slab_initial.get_conductivity();
  
  auto const b1 = b( beam_radius, L );
  auto const b2_i = b( detector_view_radius, L );
  auto const deltaT = quantity< si::temperature > ( 1.0 * kelvin );
  auto const b3 = b( detector_offset_i, L );

  // establish parameters to fit with initial values
  auto model_parameters = vector< double >
  {
    kx_limiter1( alpha.value() ) ,  // diffusivity ratio
    kx_limiter2(  b2_i.value(), 0, 5.0 ),
  //  kx_limiter1( b1.value() ) ,      // beam radius
    kx_limiter1( b3.value() )       // detector offset
  };
  
  // parameter estimation algorithm
  auto const number_of_points_to_Fit = frequencies.size();
  
  auto const update_system_properties = [&b1] ( const double * x )
  noexcept
  {
    auto const alpha = quantity<si::thermal_diffusivity>::from_value( x_limiter1( x[0] ) );
    auto const b2 =  quantity<si::dimensionless>( x_limiter2( x[1], 0.0, 4.0 ) ); //  detector radius
    auto const b3 =  quantity<si::dimensionless>( x_limiter1( x[2] ) );  //  beam radius
    //auto const b1 =  quantity<si::dimensionless>( x_limiter1( x[3] ) );  //  beam radius


    std::cout << alpha << "\t" << b2 << "\t" << b1 <<"\t" << b3 << "\n" ;
    auto const updated_elements = make_tuple( alpha, b2, b1, b3 ) ;
    return updated_elements ;
  };

  auto const make_model_predictions =
  [ &frequencies, &L, &update_system_properties, &deltaT]
  ( const double * x ) noexcept
  {
    auto const t = update_system_properties( x );
    
    auto const alpha = get< 0 >(t);
    auto const b2 = get< 1 >(t);
    auto const detector_offset = get< 2 >(t);
    auto const b1 = get< 3 >(t);
    
    auto const predictions =
    thermal::model::oneLayer2D::offset_detector::average_surface_phases_amplitudes( b1, deltaT, b2, frequencies, L, alpha, detector_offset );
    
    return predictions;
  };

  auto const minimization_equation =
  [ & ] ( const double *x, double *fvec ) noexcept
  {
    auto const predictions = make_model_predictions( x );
    
    auto const residual = [ & ]( const int i ) noexcept {
      return ( predictions[i].phase  -  observations[i] ).value() ;
    } ;

    auto i = 0;
    generate( fvec, fvec + number_of_points_to_Fit , [&]() noexcept {
      return residual( i++ );
    } ) ;
  };

  auto lmdif_settings = settings{};
  lmdif_settings.factor = .1;

  lmdif(  minimization_equation, number_of_points_to_Fit,
          model_parameters, lmdif_settings );

  auto const x = model_parameters.data();
  auto const t = update_system_properties( x );
  auto const alpha_fit = get< 0 >(t);
  auto const b2 = get< 1 >(t);
  auto const b3_fit = get< 2 >(t);
  auto const b1_fit = get< 3 >(t);
  
  auto const model_predictions = make_model_predictions( x );
  auto const phases = extract_phases_from_properties( model_predictions  ) ;
  auto const fitted_slab = thermal::model::slab::Slab( L , alpha_fit , k ) ;
  
  auto const result =
  Best_fit( fitted_slab, b2, b1_fit, frequencies, phases );
  
  return result;
}

} // namespace estimate_parameters
} // namespace offset_detector
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal
