//
//  J1.h
//  tat
//
//  Created by Raymond Valdes on 5/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_64767_J1_h
#define tat_64767_J1_h

#include "math/special_functions/bessel.h"
//#include "units.h"
#include <cassert>
#include <cmath>

namespace math{
namespace special_functions {
namespace bessel {

template< typename T >
auto J1( T const x ) noexcept
{
//  using namespace units;
//  using std::isfinite;
  assert( isfinite( x ) );

  auto constexpr v = size_t( 1 );

  auto const J_eval = bessel_j( v , x );
  assert( isfinite( J_eval ) );

  return J_eval;
}

} // namespace bessel
} // namespace special_functions
} // namespace math

#endif
