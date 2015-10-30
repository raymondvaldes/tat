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
#include <cassert>
#include <iomanip>

#include "algorithm/algorithm.h"

namespace cout { namespace vector {

template< typename T >
auto print( std::vector< T > const & list ) noexcept
{
  using algorithm::for_each ;
  using std::cout ;
  
  for_each( list, []( auto const & e ) noexcept
  {
    cout << e << "\n";
  } ) ;
}

template< typename T , typename F >
auto print_table(
  std::vector< T > const & first_list,
  std::vector< F > const & second_list
) noexcept
{
//  using namespace units ;
  using algorithm::for_each ;
  using std::cout ;
  assert( first_list.size() == second_list.size() );

  auto i = 0u;
  for_each( first_list, [&]( auto const & /*e*/ ) noexcept
  {
    cout << first_list[i] << "\t" << second_list[i] << "\n";
    ++i;
  } ) ;
}

  
} } // namespace
#endif /* defined(__tat__print__) */
