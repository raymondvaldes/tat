/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include <vector>
#include <cstddef>
#include "math/algorithms/combinations.hpp"

namespace math{
namespace algorithms{

size_t factorial( const size_t n ) noexcept
{
    if (n == 0)
       return 1;
    return n * factorial(n - 1);
}

size_t permutations( const size_t n, const size_t r) noexcept
{
  size_t
  val = factorial(n);
  val /= factorial( n -r) * factorial(r);

  return val;
}

}}
