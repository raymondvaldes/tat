//
//  bessel.h
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_bessel_h
#define tat_bessel_h

#include <boost/math/special_functions/bessel.hpp>
#include <cstddef>
#include "units.h"

namespace math {

namespace special_functions {

template< typename T >
auto bessel_j( size_t const v, units::quantity< T > const x ) noexcept
{
  using boost::math::cyl_bessel_j;
  using namespace units;
  
  //set precision
  using namespace boost::math;
  using namespace boost::math::policies;
  typedef policy<digits10<15> > pol;
  
  auto const j = cyl_bessel_j( v, x.value(), pol() ) ;
  auto const j_dim = quantity< T >::from_value( j );

  return j_dim;
}

} // namespace special_functions

} // math

#endif
