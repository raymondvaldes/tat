//
//  reserve.h
//  tat
//
//  Created by Raymond Valdes_New on 3/18/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_reserve_h
#define tat_reserve_h

#include <vector>
#include "algorithm/algorithm.h"

namespace algorithm {

namespace vector {

template< typename T >
auto reserve( size_t const dim )
{
  using std::vector;
  
  auto output = vector<T>();
  output.reserve( dim );

  return output;
}

template< typename T >
auto reserve( size_t const dim_1, size_t const dim_2 )
{
  using std::vector;
  
  auto output = vector< vector<T> >();
  
  output.reserve( dim_1 );
  for_each( output, [ dim_2 ]( auto vecs )
  {
    vecs.reserve( dim_2 );
  } );

  return output;
}
  
} // namespace vector
  
} // namespace algorithm

#endif
