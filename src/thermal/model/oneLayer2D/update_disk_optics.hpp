//
//  update_disk_optics.hpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef update_disk_optics_hpp_102515
#define update_disk_optics_hpp_102515

#include "parameter_list.hpp"
#include "map_parameter_values.hpp"
#include "disk.hpp"
#include "thermal/model/optics/optics.h"
#include <utility>

namespace thermal{
namespace model{
namespace oneLayer2D{

auto update_disk_optics
(
  Map_parameter_values const & parameter_values,
  Disk const & disk,
  Optics const & optics
) noexcept -> std::pair< Disk, Optics >;


}}}

#endif /* update_disk_optics_hpp */
