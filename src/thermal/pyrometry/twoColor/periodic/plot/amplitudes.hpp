//
//  amplitudes.hpp
//  tat
//
//  Created by Raymond Valdes on 10/7/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef amplitudes_hpp_10715
#define amplitudes_hpp_10715

#include <string>
#include "filesystem/path.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "thermal/pyrometry/twoColor/periodic/temperatures.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {
namespace plot {

auto amplitudes_to_file_log_linear(
  thermal::equipment::laser::Modulation_frequencies const & frequencies,
  Temperature_amplitudes const & amplitudes,
  filesystem::path const & print_directory,
  std::string const & filename  
) noexcept -> void;

auto amplitudes_to_file_log_log(
  thermal::equipment::laser::Modulation_frequencies const & frequencies,
  Temperature_amplitudes const & amplitudes,
  filesystem::path const & print_directory,
  std::string const & filename  
) noexcept -> void;

} // namespace plot
} // namespace periodic
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal
 
#endif /* amplitudes_hpp */
