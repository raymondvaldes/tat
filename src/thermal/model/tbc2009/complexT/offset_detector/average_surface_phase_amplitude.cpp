//
//  average_surface_phase_amplitude.cpp
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/tbc2009/complexT/offset_detector/average_surface_phase_amplitude.h"
#include "thermal/model/tbc2009/complexT/surface_phase_amplitude.h"
#include "math/calculus/mean_value/offset_circle/offset_circle.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT {
namespace offset_detector {

using namespace units;
using std::pair;
using std::make_pair;
using namespace math::calculus;

auto average_surface_phase_amplitude
(
  dimensionless::HeatingProperties const & hp,
  dimensionless::ThermalProperties const & tp,
  units::quantity< units::si::dimensionless > const l,
  units::quantity< units::si::dimensionless > const offset,
  units::quantity< units::si::dimensionless > const view_radius
) noexcept -> std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> >
{
  assert( l > 0 );
  assert( offset > 0 );
  assert( view_radius > 0 );
  
  auto mean_values =
    pair< quantity< plane_angle >,quantity< si::dimensionless> >();


  auto const a = quantity<length>::from_value( offset );
  auto const b = quantity<length>::from_value( view_radius );

  auto const T_phase =
  [ &hp, &tp, l ]( quantity< length > const r ) noexcept -> double
  {
    return surface_phase_amplitude(
      quantity< si::dimensionless >( r.value() ), hp, tp, l ).first.value();
  };
  
  auto const phase =
  quantity< plane_angle >::from_value( mean_value::offset_circle( T_phase, a, b ) );


//  auto const T_amplitude =
//  [ hp, tp, l ]( quantity< length > const r ) noexcept -> double
//  {
//    return surface_phase_amplitude(
//      quantity< si::dimensionless >( r.value()), hp, tp, l ).second.value();
//  };
//  auto const amplitude =
//  quantity< si::dimensionless>(mean_value::offset_circle( T_amplitude, a, b ) );

  auto const amplitude =
  quantity< si::dimensionless>();

  mean_values = make_pair( phase, amplitude );
  

  return mean_values;
}
  
} // namespace offset_detector
} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal
