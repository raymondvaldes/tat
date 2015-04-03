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
  auto const arc_length = [ &f, offset, radius ]( double const r ) noexcept
  {
    auto const R = quantity< si::length>::from_value( r );
    auto const phi = angles_of_intersection( R, offset, radius );
    auto const phi_1 = phi.first.value();
    auto const phi_2 = phi.second.value();
  
    auto const func = [&f]
    ( vector< double > const & y, vector< double > & dy, double const r )
    noexcept -> void
    {
      dy[0] = f( quantity< length >::from_value( r ) ) * r ;
    };
    auto const ini = vector< double > ( { 0 } );
    
    return integrate( func, ini, phi_1 , phi_2, ( (phi_2 - phi_1) / 100 ) );
  };
  

  auto const integrate_dr = [ &f, offset, radius, &arc_length ]() noexcept
  {
    auto const r1 = ( offset - radius ).value();
    auto const r2 = ( offset + radius ).value();
    
    auto const func = [ &arc_length ]
    ( vector< double > const & y, vector< double > & dy, double const r )
    noexcept -> void
    {
      dy[0] = arc_length(r) ;
    };
    
    auto const ini = vector< double > ( { 0 } );
    
    return integrate( func, ini , r1 , r2, ( ( r2 - r1 ) / 100 ) );
  };

  auto const area = circle_from_radius( radius );

  auto const integratation_result = integrate_dr();
  auto const mean = integratation_result / area.value() ;

  return mean;
}

} // namespace mean_value
} // namespace calculus
} // namespace math
