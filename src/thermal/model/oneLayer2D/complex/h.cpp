//
//  h.cpp
//  tat
//
//  Created by Raymond Valdes on 4/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/complex/h.h"
#include "thermal/model/oneLayer2D/complex/kappa.h"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace complex{

using namespace units;

auto h
(
  units::quantity< units::si::dimensionless, double > const nu,
  units::quantity< units::si::dimensionless, double > const z,
  units::quantity< units::si::dimensionless, double > const l,
  units::quantity< units::si::dimensionless, double > const b
) noexcept -> units::quantity< units::si::dimensionless, std::complex<double> >
{
  auto const inv = []( auto const e ) noexcept { return quantity<si::dimensionless>(1.) / e ; } ;
  auto const csch = [&inv]( auto const e ) noexcept { return inv(sinh(e)); } ;

  auto const k = kappa( nu, b, l );
  auto const two = quantity<si::dimensionless>( 2 );
  auto const four = quantity<si::dimensionless>( 4 );
  
  auto const h_eval =
  exp( -pow<2>(nu)/ four ) * cosh( k * ( inv(b) - z ) ) * csch( k * inv(b) )
  / ( two * k ) ;
 
  return h_eval;
}

} // namespace complex
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
