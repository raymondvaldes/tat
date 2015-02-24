//
//  valarray_to_vector.h
//  tat
//
//  Created by Raymond Valdes_New on 2/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_valarray_to_vector_h
#define tat_valarray_to_vector_h

#include <vector>
#include <valarray>
#include <algorithm>

namespace alogorithm {

namespace valarray {

template< typename T >
auto valarray_to_vector( std::valarray<T> const & valarray ) noexcept ->
std::vector<T>
{
  auto vector = std::vector<T>();
  
  auto const count = valarray.size();
  vector.reserve( count );
  
  using std::for_each;
  using std::begin;
  using std::end;
  
  for_each( begin( valarray ), end( valarray ),
  [ &vector ]( auto const & Element ) noexcept
  {
    vector.push_back( Element );
  });
  
  assert( vector.size() == count );
    
  return vector;
}

  
} // namespace valarray
  
} // namespace alogorithm

#endif
