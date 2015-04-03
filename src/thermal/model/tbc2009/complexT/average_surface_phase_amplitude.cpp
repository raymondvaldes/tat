//
//  average_surface_phase_amplitude.cpp
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <cmath>
#include <vector>

#include "thermal/model/tbc2009/complexT/surface_phase_amplitude.h"
#include "average_surface_phase_amplitude.h"
#include "math/numIntegration/integrate.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT {

using std::vector;
using namespace units;
using std::pow;
using std::make_pair;

auto average_surface_phase_amplitude
(
  units::quantity< units::si::dimensionless > const view_radius,
  dimensionless::HeatingProperties const hp,
  dimensionless::ThermalProperties const tp,
  units::quantity< units::si::dimensionless > const l
) noexcept -> std::pair<
  units::quantity< units::si::plane_angle >,
  units::quantity< units::si::dimensionless> >
{
  // integration domain
  auto const r0 = double(0) ;
  auto const r1 = view_radius.value() ;
  auto const dr_i_step = double( 0.01 );
  auto const f_r0 = vector< double > ( { 0 } );
  
  auto const phase = [&]( double const & r ) noexcept -> double {
    auto const r_dim = quantity<si::dimensionless>( r );
    auto const phase_dim = surface_phase_amplitude( r_dim , hp, tp, l );
    return phase_dim.first.value();
  };

  auto const amplitude = [&]( double const & r ) noexcept -> double {
    auto const r_dim = quantity<si::dimensionless>( r );
    auto const a_dim = surface_phase_amplitude( r_dim , hp, tp, l );
    return a_dim.second.value();
  };

  // given integrate f(x) from a to b.  Must satisfy F(a) = 0;
  auto const func_phase = [ &]
  (
    vector< double > const & yphase,
    vector< double > & dy,  // thing integrate
    double const r
  ) noexcept -> void
  {
    dy[0] = phase( r ) * r;
  };

  auto const func_amplitude = [ & ]
  (
    vector< double > const & yphase,
    vector< double > & dy,  // thing integrate
    double const r
  ) noexcept -> void
  {
    dy[0] = amplitude( r ) * r;
  };

  auto const area_phase =
  math::numIntegration::integrate( func_phase, f_r0, r0, r1, dr_i_step );

  auto const area_amplitude =
  math::numIntegration::integrate( func_amplitude, f_r0, r0, r1, dr_i_step );
  
  auto const average_phase = ( 2. / pow( r1, 2 ) ) * area_phase ;
  auto const average_amplitude = ( 2. / pow( r1, 2 ) ) * area_amplitude ;

  return make_pair( quantity<plane_angle>::from_value( average_phase),
                    quantity<si::dimensionless >( average_amplitude ) ) ;
}
  
} // complexT
} // tbc2009
} // model
} // thermal
