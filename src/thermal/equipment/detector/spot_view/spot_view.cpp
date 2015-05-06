//
//  spot_view.cpp
//  tat
//
//  Created by Raymond Valdes on 5/4/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/equipment/detector/spot_view/spot_view.h"

#include "thermal/emission/planks_law/planks_law.h" 
#include "math/calculus/weighted_mean_value/circle.h"

using namespace units;
using std::make_pair;
using std::pair;
using math::calculus::weighted_mean_value::circle_complex;
using thermal::emission::monochromatic_blackbody_emissive_power::planks_law;
using math::complex::properties;

namespace thermal{
namespace equipment{
namespace detector{

/* The spot-view function takes the weighted-average value of a function.  The
    weighted function is derived from the monochromatic emissive power.
*/
auto spot_view_2
(
  std::function< math::complex::properties< units::si::temperature > ( double ) > const phase_amplitude_field,
  units::quantity< units::si::temperature > const reference_temperature,
  units::quantity< units::si::wavelength> const detector_wavelength,
  units::quantity< units::si::dimensionless> const R
)
noexcept -> math::complex::properties< units::si::temperature >
{
  auto const dr_i_step = R / 200.;
  auto const lambda = detector_wavelength;
  auto const T_ss = reference_temperature;
  auto const E_steadyState = planks_law( reference_temperature, lambda );
  
  auto const w =
  [&phase_amplitude_field, &lambda, &T_ss, &E_steadyState]
  ( double const r) noexcept
  {
    auto const eval = phase_amplitude_field( r );
    auto const amplitude = eval.amplitude;

    auto const T = T_ss + amplitude ;
    auto const E_trans = planks_law( T, lambda );

    auto const weight = ( E_trans / E_steadyState ) - 1.0 ;
    return weight;
  };
  
  auto const f = [&]( double const r )
  noexcept -> std::pair< double, double >
  {
    auto const eval = phase_amplitude_field( r );
    auto const amplitude = eval.amplitude;
    auto const phase = eval.phase;
    
    return make_pair( phase.value() , amplitude.value() );
  };
  
  auto const mean_values = circle_complex( f, w, R, dr_i_step );


  auto const mean_phase =
    quantity< si::plane_angle >::from_value( mean_values.first );
  
  auto const mean_amplitude =
    quantity< si::temperature >::from_value( mean_values.second );

  auto const mean_pair =
  properties< si::temperature >( mean_phase, mean_amplitude ) ;

  return mean_pair;
}

} // namespace detector
} // namespace equipment
} // namespace thermal
