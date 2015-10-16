//
//  phases.hpp
//  tat
//
//  Created by Raymond Valdes on 10/7/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef phases_hpp_10715
#define phases_hpp_10715

#include <string>

#include "thermal/emission/phases.h"
#include "thermal/equipment/laser/modulation_frequencies.h"
#include "filesystem/path.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {
namespace plot {

auto phases_to_file(
  thermal::equipment::laser::Modulation_frequencies const & frequencies,
  thermal::emission::Phases const & phases,
  filesystem::path const & print_directory,
  std::string const & filename  
) noexcept -> void;

} // namespace plot
} // namespace periodic
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal

#endif /* phases_hpp */
