//
//  vector_to_valarray.h
//  tat
//
//  Created by Raymond Valdes_New on 2/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_vector_to_valarray_h
#define tat_vector_to_valarray_h

#include <vector>
#include <valarray>

namespace alogorithm {

namespace valarray {

template< typename T >
auto vector_to_valarray( std::vector<T> const & vector ) noexcept ->
std::valarray<T>
{
  auto const valarray = std::valarray<T>( vector.data(), vector.size() );
  return valarray;
}

  
} // namespace valarray
  
} // namespace alogorithm

#endif
