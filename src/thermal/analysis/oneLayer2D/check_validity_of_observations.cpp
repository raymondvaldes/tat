//
//  check_validity_of_observations.cpp
//  tat
//
//  Created by Raymond Valdes on 10/27/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "check_validity_of_observations.hpp"
#include <exception>

namespace thermal{
namespace analysis{
namespace oneLayer2D{

auto check_validity_of_observations(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures
 ) -> void
{
  if( frequencies.size() != temperatures.size() ) {
    throw Frequencies_not_match_observations();
  }
  if( frequencies.empty() ) {
    throw Frequencies_empty();
  }

  if( temperatures.empty() ) {
    throw Observations_empty();
  }
  
//  
//  if() {
//    throw Frequencies_invalid_values();
//  }
//  if() {
//    throw Observations_invalid_values();
//  }

}

}}}

