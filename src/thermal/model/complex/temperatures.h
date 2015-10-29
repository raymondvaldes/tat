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
#include <utility>

#include "thermal/model/complex/temperature.h"
#include "math/complex/properties.h"
#include "thermal/equipment/laser/modulation_cutoff_frequencies.h"
#include "thermal/equipment/laser/modulation_frequencies.h"

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

  auto filter_using_cutoff_frequencies
  (
    thermal::equipment::laser::Modulation_frequencies const & frequencies,
    thermal::equipment::laser::Modulation_cutoff_frequencies const & cutoff
  )
  const noexcept ->
  std::pair< thermal::equipment::laser::Modulation_frequencies, Temperatures>;
  };


} // namespace complex
} // namespace model
} // naemsapce thermal

#endif /* Complex_temperatures_h */
