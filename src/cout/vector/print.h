//
//  print.h
//  tat
//
//  Created by Raymond Valdes on 5/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_cout_vector_print__
#define __tat_cout_vector_print__

#include <iostream>
#include <vector>
#include "algorithm.h"
#include "units.h"

namespace cout {
namespace vector {

template< typename T >
auto print( std::vector< T > const & list ) noexcept
{
  using namespace units ;
  using algorithm::for_each ;
  using std::cout ;
  
  for_each( list, []( auto const & e ) noexcept
  {
    cout << e << "\n";
  } ) ;
}
  
} // namespace vector
} // namespace cout
#endif /* defined(__tat__print__) */
