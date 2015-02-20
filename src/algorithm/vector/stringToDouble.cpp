//
//  stringToDouble.cpp
//  tat
//
//  Created by Raymond Valdes_New on 2/17/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <algorithm>

#include "algorithm/vector/stringToDouble.h"

namespace algorithm {

namespace vector {

auto stringToDouble( std::vector<std::string> const &  input ) noexcept -> std::vector<double>
{
  using std::string;
  using std::transform;
  using std::stod;
  using std::begin;
  using std::end;

  auto const N = input.size() ;
  
  auto output = std::vector<double>( N ) ;

  transform( begin( input ), end( input ), begin( output ),
  []( const auto& E)
  {
    return stod( E )  ;
  }  ) ;
  
  return output;
}






} // namespace vector
  
} // namespace algorithm

