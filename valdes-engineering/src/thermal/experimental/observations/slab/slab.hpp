//
//  slab.hpp
//  tat
//
//  Created by Raymond Valdes on 9/8/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef slab_cpp_experimental_observations_phase
#define slab_cpp_experimental_observations_phase

#include "thermal/model/slab/slab.h"
#include <vector>
#include "units.h"

namespace thermal {
namespace experimental {
namespace observations {

struct Slab{

  thermal::model::slab::Slab disk;
  std::vector< units::quantity< units::si::frequency > > frequencies;
  std::vector< units::quantity< units::si::plane_angle > > phases;
  units::quantity< units::si::length > beam_radius;
  
  explicit Slab
  (
    thermal::model::slab::Slab disk_,
    std::vector< units::quantity< units::si::frequency > > frequencies_,
    std::vector< units::quantity< units::si::plane_angle > > phases_,
    units::quantity< units::si::length > beam_radius_
  ):
  disk( disk_ ), frequencies( frequencies_ ), phases( phases_ ),
  beam_radius( beam_radius_) {};
  
};


} // namespace observations
} // namespace experimental
} // namespace thermal

#endif /* slab_cpp */
