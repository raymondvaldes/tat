//
//  offset_circle.cpp
//  tat
//
//  Created by Raymond Valdes on 4/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "math/calculus/mean_value/offset_circle/offset_circle.h"

#include "math/numIntegration/integrate.h"
#include "math/geometry/circle.h"
#include "math/geometry/intersect/two_circles/angles_of_intersection.h"
#include <cmath>
#include <vector>

namespace math{
namespace calculus{
namespace mean_value{

using namespace units;
using math::numIntegration::integrate;
using std::pow;
using std::atan;
using std::vector;
using std::make_pair;
using math::geometry::area::circle_from_radius;
using math::geometry::intersect::two_circles::angles_of_intersection;

auto offset_circle
(
  std::function< double( units::quantity< units::si::length > )> const & f,
  units::quantity< units::si::length > const offset,
  units::quantity< units::si::length > const radius
)
noexcept -> double
{
  assert( offset > 0 * meters ) ;
  assert( radius > 0 * meters ) ;

  auto const integrate_dr = [ &f, offset, radius ]() noexcept
  {
    auto r1 = 1e-8;
    if( ( offset - radius ) > 0 * meters ) {
      r1 = ( offset - radius ).value();
    }
    
    auto const r2 = ( offset + radius ).value();
    
    auto const func = [ & ]
    ( vector< double > const & /*y*/, vector< double > & dy, double const r )
    noexcept -> void
    {
      auto const R = quantity< si::length>::from_value( r );
    
      auto const phi = angles_of_intersection( R, offset, radius );
      auto const phi_1 = phi.first.value();
      auto const phi_2 = phi.second.value();

      dy[0] = f( quantity< length >::from_value( r ) ) * r * (  phi_2 -  phi_1 ) ;
    };
    auto ini = vector< double > ( { 0 } );

      auto const dr_i_step = (r2 - r1) / 200.;
    return integrate( func, ini , r1 , r2, dr_i_step );
  };

  auto const area = circle_from_radius( radius );

  auto const integratation_result = integrate_dr();
  auto const mean = integratation_result / area.value() ;

  return mean;
}

auto offset_circle
(
  std::function< std::pair<double, double>( units::quantity< units::si::length > )> const & f,
  units::quantity< units::si::length > const offset,
  units::quantity< units::si::length > const radius
)
noexcept -> std::pair<double, double>
{
  assert( offset > 0 * meters ) ;
  assert( radius > 0 * meters ) ;

  auto const integrate_dr = [ &f, offset, radius ]() noexcept
  {
  
    auto r1 = 1e-8;
    if( ( offset - radius ) > 0 * meters ) {
      r1 = ( offset - radius ).value();
    }
    
    auto const r2 = ( offset + radius ).value();
    
    auto const func = [ & ]
    ( vector< double > const & /*y*/, vector< double > & dy, double const r )
    noexcept -> void
    {
      auto const R = quantity< si::length>::from_value( r );
    
      auto const phi = angles_of_intersection( R, offset, radius );
      auto const phi_1 = phi.first.value();
      auto const phi_2 = phi.second.value();
      auto const f_eval = f( quantity< length >::from_value( r ) );

      dy[0] = f_eval.first * r * (  phi_2 -  phi_1 ) ;
      dy[1] = f_eval.second * r * (  phi_2 -  phi_1 ) ;
    };
    auto ini = vector< double > ( { 0, 0 } );

    auto const dr_i_step = (r2 - r1) / 200.;
    
    integrate( func, ini , r1 , r2, dr_i_step );
    
    return make_pair( ini[0], ini[1] );
  };

  auto const area = circle_from_radius( radius );

  auto const integratation_result = integrate_dr();
  
  
  auto const mean = make_pair(
    integratation_result.first / area.value(),
    integratation_result.second / area.value() ) ;

  return mean;
}


} // namespace mean_value
} // namespace calculus
} // namespace math
