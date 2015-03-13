//
//  find_all.h
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_find_all_h
#define tat_find_all_h

#include <iostream>
#include <vector>
#include "algorithm/algorithm.h"

namespace algorithm{

namespace vector {

template< typename T, typename Y, typename BinaryPredicate >
auto find_all
(
  std::vector< T > const & list,
  Y const & element ,
  BinaryPredicate const & p
)
noexcept -> std::vector< T >
{
  auto const searchElement = std::vector< Y >( {element} ) ;

  auto const first = find_first_of( list, searchElement , p ) ;
  auto const last = find_end( list, searchElement , p ) ;
  
  auto const all_found = std::vector<T>( first , last+1 ) ;
  return all_found;
}

} // namespace vector

} // namespace algorithm

#endif
