//
//  doubleToString.cpp
//  tat
//
//  Created by Raymond Valdes_New on 2/17/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <algorithm>
#include <string>
#include <iterator>

#include "algorithm/vector/doubleToString.h"

namespace algorithm {

namespace vector {

auto doubleToString( std::vector<double> const &  input ) noexcept -> std::vector<std::string>
{
  using std::vector;
  using std::string;
  using std::transform;
  using std::to_string;
  using std::begin;
  using std::end;

  auto const N = input.size() ;
  
  auto output = vector< string >( N ) ;

  transform( begin( input ), end( input ), begin( output ),
  []( auto const& E)
  {
    return to_string( E )  ;
  }  ) ;
  
  return output;
}

} // namespace vector
  
} // namespace algorithm
