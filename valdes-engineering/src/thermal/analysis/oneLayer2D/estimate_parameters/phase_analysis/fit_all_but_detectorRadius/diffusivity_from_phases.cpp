//
//  diffusivity_from_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_detectorRadius/diffusivity_from_phases.h"
#include "algorithm/algorithm.h"
#include <iostream>
#include <tuple>

#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/b.h"
#include "thermal/model/oneLayer2D/model_selection.h"

#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/centered_with_view/frequency_sweep.h"
using thermal::model::oneLayer2D::thermal_emission::centered_with_view::frequency_sweep;

#include "math/estimation/constrained.hpp"
#include "math/estimation/settings.h"
#include "math/estimation/lmdiff.hpp"

#include "statistics/uncertainty_analysis/goodness_of_fit/goodness_of_fit.h"

#include "math/complex/extract_phases_from_properties.h"

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace phase_analysis{
namespace fit_all_but_detectorRadius{

using namespace units;

using algorithm::for_each;
using std::vector;
using math::estimation::x_limiter1;
using math::estimation::x_limiter2;
using math::estimation::kx_limiter1;
using math::estimation::kx_limiter2;

using math::estimation::x_to_k_constrained_from_0_to_1;
using math::estimation::k_to_x_constrained_from_0_to_1;
using thermal::model::oneLayer2D::dimensionless::b;
using math::estimation::settings;
using std::generate;
using std::make_tuple;
using std::tie;
using std::get;
using math::complex::extract_phases_from_properties;
using statistics::uncertainty_analysis::goodness_of_fit;

auto diffusivity_from_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const slab_initial,
  units::quantity< units::si::length> const beam_radius,
  units::quantity< units::si::length > const detector_view_radius
) noexcept -> Best_fit
{
  //establish preconditions
  assert( frequencies.size() > 0 );
  assert( frequencies.size() == observations.size() ) ;
  assert( detector_view_radius.value() > 0 ) ;

  // establish nondimensional fitting parameters
  auto const L = slab_initial.thickness() ;
  auto const alpha = slab_initial.thermal_diffusivity();
  auto const k = slab_initial.thermal_conductivity();
  
  auto const b1_i = b( beam_radius, L );
  auto const b2 = b( detector_view_radius, L );
  auto const deltaT = quantity< si::temperature > ( 1.0 * kelvin );
  auto const alpha_scale = alpha.value();


  // establish parameters to fit with initial values
  auto model_parameters = vector< double >
  {
    kx_limiter1( 1.0 ) ,  // diffusivity ratio
    kx_limiter2( b1_i.value(), 0.05, 10. )
  };
  
  // parameter estimation algorithm
  auto const number_of_points_to_Fit = frequencies.size();
  
  auto const update_system_properties = [&b2, &alpha_scale] ( const double * x )
  noexcept
  {
    auto const alpha_value = x_limiter1( x[0] ) ;
    auto const alpha = quantity<si::thermal_diffusivity>::from_value(
     alpha_value * alpha_scale  );
    
    auto const b1 =  quantity<si::dimensionless>( x_limiter2( x[1], .05, 10. ) ); //  detector radius

    std::cout << alpha << "\t" << b1 << "\t" << b2 << "\n" ;
    auto const updated_elements = make_tuple( alpha, b1 ) ;
    return updated_elements ;
  };

  auto const make_model_predictions =
  [ &frequencies, &L, &update_system_properties, &deltaT, &b2]
  ( const double * x ) noexcept
  {
    auto const t = update_system_properties( x );
    
    auto const alpha = get< 0 >(t);
    auto const b1 = get< 1 >(t);
    
    auto const predictions =
    frequency_sweep(
      b1, deltaT, b2, frequencies, L, alpha );
    
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
  lmdif_settings.factor = 10;   // initial step size
  lmdif_settings.xtol = .001;   // tolerance between x-iterates
  lmdif_settings.epsfcn = 1e-4; // tolerance of phase function

  lmdif(  minimization_equation, number_of_points_to_Fit,
          model_parameters, lmdif_settings );

  auto const x = model_parameters.data();
  auto const t = update_system_properties( x );
  auto const alpha_fit = get< 0 >(t);
  auto const b1 = get< 1 >(t);
  
  auto const model_predictions = make_model_predictions( x );
  auto const phase_predictions = extract_phases_from_properties( model_predictions  ) ;
  auto const fitted_slab = thermal::model::slab::Slab( L , alpha_fit , k ) ;
  auto const phase_goodness_of_fit = goodness_of_fit( observations , phase_predictions );
  
  
  auto const l_r = thermal::equipment::laser::Beam_radius(b1 * L );
  auto const l_i = thermal::equipment::laser::Beam_power::from_value(42);
  auto const d_r = thermal::equipment::detector::View_radius::from_value(42);
  auto const l_m = thermal::equipment::laser::Modulation_depth::from_value(42);
  
  auto const optics_fitted =
  thermal::model::Optics( l_r, l_i, d_r, l_m );
  
  auto const detector_model = thermal::model::oneLayer2D::Detector_model::center_with_view;
  auto const conduction_model = thermal::model::oneLayer2D::Conduction_model::infinite_disk;
  
  auto const result = Best_fit( conduction_model, detector_model,
      fitted_slab, optics_fitted, phase_goodness_of_fit );
  
  return result;
}

} // namespace
} // namespace phase_analysis
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal
