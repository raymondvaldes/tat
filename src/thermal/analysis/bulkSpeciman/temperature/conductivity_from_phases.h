//
//  conductivity_from_phases.h
//  tat
//
//  Created by Raymond Valdes_New on 3/10/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__conductivity_from_phases__
#define __tat__conductivity_from_phases__

#include <vector>
#include <utility>

#include "thermal/model/slab/slab.h"
#include "units.h"

namespace thermal {

namespace analysis {

namespace bulkSpeciman {

namespace temperature {

struct fitting_result{
  thermal::model::slab::Slab initial_slab;
  thermal::model::slab::Slab fitted_slab;
  //  std::vector< units::quantity< units::si::dimensionless > > thermal_penetrations;

  std::vector< units::quantity< units::si::plane_angle > > experimenta_phases;
  std::vector< units::quantity< units::si::plane_angle > > bestFit_phases;
  

  fitting_result
  (
    thermal::model::slab::Slab const & initial_slab_,
    thermal::model::slab::Slab const & fitted_slab_,
   
   // std::vector< units::quantity< units::si::dimensionless > > thermal_penetrations_,

    std::vector< units::quantity< units::si::plane_angle > > const & experimenta_phases_,
    std::vector< units::quantity< units::si::plane_angle > > const & bestFit_phases_
  );

};



auto
diffusivity_from_phases
(
  std::vector< units::quantity< units::si::angular_frequency > > const & omegas,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const & slab_initial
)
-> fitting_result;

auto
diffusivity_from_phases
(
  std::pair< std::vector< units::quantity< units::si::angular_frequency > >,
  std::vector< units::quantity< units::si::plane_angle > > > const & observations,
  thermal::model::slab::Slab const & slab_initial
)
-> fitting_result;

} // namespace temperature

} // namespace bulkSpeciman
  
} // namespace analysis

} // namespce thermal

#endif /* defined(__tat__conductivity_from_phases__) */
