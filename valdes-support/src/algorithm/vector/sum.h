//
//  sum.h
//  tat
//
//  Created by Raymond Valdes_New on 3/5/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_sum_h
#define tat_sum_h

#include <vector>
#include <iterator>

#include "algorithm.h"

namespace algorithm {

namespace vector {

template < typename T >
auto sum( std::vector<T> const & input )
noexcept -> T
{
  using std::begin;
  using std::end;
  
  auto const initial = input.front();
  
  auto const sum = accumulate( begin( input ) + 1, end( input ), initial );
  
  return sum;
}

template < typename T >
auto average( std::vector<T> const & input )
noexcept -> T
{
  auto const total = sum( input );
  auto const count = input.size();
  
  auto const average = total / count ;
  return average;
}

template<T>
auto residuals_to_value( std::vector<T> const & container , T const & value )
noexcept -> std::vector<T>
{
  using std::begin;
  
  transform( input, begin( container ), []( auto const & element )
  {
    auto const residual = element - value ;
    return residual;
  }  );

  return
}

template<T>
auto residuals_to_average( std::vector<T> const & container )
noexcept -> std::vector<T>
{
  using std::begin;
  
  auto const avg = average( container ) ;
  
  transform( input, begin( container ), []( auto const & element )
  {
    auto const residual = element - avg ;
    return residual;
  }  );

  return
}



template < typename T >
auto standard_deviation_sample( std::vector<T> const & input )
noexcept -> T
{
  using std::sqrt;
  using units::sqrt;
  
  auto const avg = average( input );
  auto const N = input.size();
  
  auto const residuals = residuals_to_average( input ) ;
  auto const square_residuals =
    transform( input, input.begin, []( auto const & e){ return e * e; });
  
  auto const averageSquares = average( square_residuals );
  auto const root_average_square = sqrt( averageSquares );

  return root_average_square;
}


  
} // namespace vector

} // namespace algorithm

#endif
