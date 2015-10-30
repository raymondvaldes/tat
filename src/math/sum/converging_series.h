//
//  sum.h
//  tat
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef sum_h_101815
#define sum_h_101815

#include <functional>
#include <cstddef>
#include <cmath>
#include <cassert>
#include <iostream>

namespace math { namespace sum{

template< typename T, typename F >
auto converging_series
(
  F const & func,
  T const relative_tolerance
) noexcept -> T
{
  using std::abs;

  auto eval_n = func(0);
  auto const tol = relative_tolerance * abs(eval_n);
  
  auto const convergence_criteria = [tol]( auto const a, auto const b )
  noexcept
  {
    auto const error = abs( abs(a) - abs(b) )  ;
    auto const is_not_converged = abs( error )  >  abs( tol );
    return is_not_converged;
  };

  auto is_not_converged = true;
  auto i = size_t(0);
  auto summation = eval_n;
  
  do
  {
    auto const eval = eval_n;
    eval_n = func( i + 1 );

    summation += eval_n;
    ++i;
    
    is_not_converged = convergence_criteria( eval, eval_n );
    assert( i < 200 );
  } while(  is_not_converged );
  
    
  return summation;
}

} }

#endif /* sum_h */
