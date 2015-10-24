//
//  update_disk_optics.hpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef update_disk_optics_hpp_102315
#define update_disk_optics_hpp_102315

#include "parameter_list.hpp"
#include "map_parameter_values.hpp"
#include "disk.hpp"
#include "optics.hpp"
#include <utility>

namespace thermal { 
namespace model {
namespace oneLayer2D { 
namespace finite_disk {

auto update_disk_optics
(
  Map_parameter_values const & parameter_values,
  Disk const & disk,
  Optics const & optics
) noexcept -> std::pair< Disk, Optics >;



} } } }

#endif /* update_disk_optics_hpp */
