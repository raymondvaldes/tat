//
//  Complex_temperatures.h
//  tat
//
//  Created by Raymond Valdes on 10/15/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef Complex_temperatures_h_101515
#define Complex_temperatures_h_101515

#include <vector>
#include <cstddef>
#include "thermal/model/complex/temperature.h"
#include "math/complex/properties.h"

namespace thermal{
namespace model{
namespace complex{

class Temperatures{

  private:
  std::vector< Temperature > values;

  public:
  Temperatures(
    std::vector< Temperature > const & values
  );
  Temperatures(){};

  auto phases() const noexcept -> Phases;
  auto amplitudes() const noexcept -> Amplitudes;
  auto size() const noexcept -> size_t;
  auto empty() const noexcept -> bool;
};


} // namespace complex
} // namespace model
} // naemsapce thermal

#endif /* Complex_temperatures_h */
