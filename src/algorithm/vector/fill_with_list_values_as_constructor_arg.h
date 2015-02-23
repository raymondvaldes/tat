//
//  fill_with_list_values_as_constructor_arg.h
//  tat
//
//  Created by Raymond Valdes_New on 2/23/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_fill_with_list_values_as_constructor_arg_h
#define tat_fill_with_list_values_as_constructor_arg_h

#include <cassert>
#include <vector>
#include <algorithm>

namespace algorithm {

namespace vector {

template< class element_type, class list_A, class list_B > auto
fill_with_list_values_as_constructor_arg( list_A const & A, list_B const & B )
noexcept -> std::vector< element_type >
{
  using std::vector;
  using std::for_each;
  using std::begin;
  using std::end;
 
  assert( !A.empty() );
  assert( A.size() == B.size() ) ;
  auto const N_length = A.size();
  
  auto elements = vector< element_type >();
  elements.reserve( N_length );

  auto i = 0u;
  auto const push_back_each_element =
    [&elements, &A, &B, &i]( auto const & a )
  {
    auto const element = element_type( A[i], B[i] );
    elements.push_back( element );
    i++;
  };
  
  for_each( A.begin(), A.end() , push_back_each_element ) ;
  
  return elements;
};

} // namespace vector

} // namespace algorithm

#endif
