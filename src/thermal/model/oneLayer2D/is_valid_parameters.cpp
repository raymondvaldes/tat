//
//  is_valid_parameters.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "is_valid_parameters.hpp"
#include "algorithm/algorithm.h"

namespace thermal{
namespace model{
namespace oneLayer2D{

auto is_valid_parameters(
  Parameters const & parameters,
  Parameters const & valid_parameters
) noexcept -> bool
{
  auto const list_is_not_empty = parameters.empty();
  
  auto const each_are_valid =
  algorithm::any_of( parameters, [&valid_parameters]( auto const p ) noexcept
  {
    auto const p_is_valid = algorithm::binary_search( valid_parameters, p );

    return !p_is_valid;

  });
  
  
  auto p_sorted = algorithm::sort( parameters );
  auto last = std::unique( p_sorted.begin(), p_sorted.end() );
  p_sorted.erase( last , end( p_sorted ) ) ;
  
  auto const no_dupicates = p_sorted.size()  == parameters.size();

  
  auto const is_valid = each_are_valid && list_is_not_empty && no_dupicates;

  return is_valid;  
}

} // namespace oneLayer2D
} // namespace model
} // namespace thermal

