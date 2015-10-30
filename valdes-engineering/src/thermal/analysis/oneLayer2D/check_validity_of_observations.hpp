//
//  check_validity_of_observations.hpp
//  tat
//
//  Created by Raymond Valdes on 10/27/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef check_validity_of_observations_hpp
#define check_validity_of_observations_hpp

#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/model/complex/temperatures.h"

namespace thermal{
namespace analysis{
namespace oneLayer2D{


class Frequencies_empty: public std::exception
{
  virtual const char* what() const throw()
  {
    return "No available modulation frequencies.";
  }
};

class Frequencies_invalid_values: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Modulation frequency values are invalid.";
  }
};

class Observations_empty: public std::exception
{
  virtual const char* what() const throw()
  {
    return "No available experimental phases/amplitudes.";
  }
};

class Observations_invalid_values: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Experimental phase/amplitude values are invalid.";
  }
};

class Frequencies_not_match_observations: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Number of experimental observations do not match frequencies.";
  }
};



auto check_validity_of_observations(
  equipment::laser::Modulation_frequencies const & frequencies,
  model::complex::Temperatures const & temperatures
 ) -> void;

}}}

#endif /* check_validity_of_observations_hpp */
