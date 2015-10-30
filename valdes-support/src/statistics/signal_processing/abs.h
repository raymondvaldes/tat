//
//  abs.h
//  tat
//
//  Created by Raymond Valdes on 10/6/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef abs_h_2341235
#define abs_h_2341235

#include <vector>
#include "algorithm/algorithm.h"
#include "units.h"

namespace statistics{
namespace signal_processing{

template < typename T  >
auto abs( std::vector< T > const & list ) noexcept
{
  using algorithm::transform;
  using std::abs;
  using units::abs;
  using std::vector;
  
  auto const N = list.size();
  auto abs_list = vector<T>( N );
  
  transform( list, abs_list.begin(), []( auto const e )
  {
    return abs( e ) ;
  } );
  
  
  return abs_list;
  
}

}
}


#endif /* abs_h */
