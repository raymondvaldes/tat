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
  auto const dr_i_step = double( 0.005 );
  auto f_0 = vector< double > ( { 0, 0 } );
  

  // given integrate f(x) from a to b.  Must satisfy F(a) = 0;
  auto const func = [ &]
  (
    vector< double > const & /*yphase*/,
    vector< double > & dy,  // thing integrate
    double const r
  ) noexcept -> void
  {
    auto const r_dim = quantity<si::dimensionless>( r );
    auto const a = surface_phase_amplitude( r_dim , hp, tp, l );
    
    dy[0] = a.first.value() * r;
    dy[1] = a.second.value() * r;
  };

  math::numIntegration::integrate( func, f_0, r0, r1, dr_i_step );

  
  auto const average_phase = ( 2. / pow( r1, 2 ) ) * f_0[0] ;
  auto const average_amplitude = ( 2. / pow( r1, 2 ) ) * f_0[1] ;

  return make_pair( quantity<plane_angle>::from_value( average_phase),
                    quantity<si::dimensionless >( average_amplitude ) ) ;
}
  
} // complexT
} // tbc2009
} // model
} // thermal
