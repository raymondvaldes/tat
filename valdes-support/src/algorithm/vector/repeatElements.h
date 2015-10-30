//
//  repeatElements.h
//  tat
//
//  Created by Raymond Valdes_New on 2/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_repeatElements_h
#define tat_repeatElements_h

#include <cassert>
#include <vector>
#include <cstddef>


namespace algorithm {

namespace vector {

template< typename T >
auto repeatElements( std::vector< T > const & elements, size_t const count )
noexcept -> std::vector< T >
{
  assert( !elements.empty() );
  assert( count > 0 ) ;

  auto list = std::vector< T >();
  
  auto const count_elements = elements.size();
  list.reserve( count * count_elements );
  
  for( auto i = 0u ; i < count ; ++i ) {
    list.insert( list.end(), elements.begin(), elements.end()  ) ;
  }

  return list;
}
  
} // namespace vector

} // namespace algorithm

#endif
