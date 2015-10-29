//
//  print_table_values.h
//  tat
//
//  Created by Raymond Valdes on 10/29/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef print_table_values_h
#define print_table_values_h

#include "algorithm/algorithm.h"
#include "units/quantity.h"
#include <cassert>
#include <iostream>

namespace units{
namespace io{

template< typename T , typename F >
auto print_table_values(
  std::vector< units::quantity<T> > const & first_list,
  std::vector< units::quantity<F> > const & second_list,
  size_t precision = 6
) noexcept
{
  using namespace units ;
  using algorithm::for_each ;
  using std::cout ;
  assert( first_list.size() == second_list.size() );
  
  std::cout << std::setprecision( static_cast<int>(precision) );
  
  auto i = 0u;
  for_each( first_list, [&]( auto const & /*e*/ ) noexcept
  {
    cout << first_list[i].value() << "\t" << second_list[i].value() << "\n";
    ++i;
  } ) ;
}

}
}

#endif /* print_table_values_h */
