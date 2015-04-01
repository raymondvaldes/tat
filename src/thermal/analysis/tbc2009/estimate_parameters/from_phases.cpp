//
//  estimate_properties.cpp
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "estimate_properties.h"

namespace thermal {
namespace analysis {
namespace tbc2009 {
namespace estimate_parameters{

Best_fit::Best_fit
(
  units::quantity< units::si::length > const L_coat_,
  units::quantity< units::si::dimensionless > const view_radius_,
  thermal::model::slab::Slab const substrate_slab_,
  dimensionless::HeatingProperties const hp_,
  dimensionless::ThermalProperties const tp_,
  std::vector< units::quantity<units::si::frequency> > const  frequencies_,
  std::vector< units::quantity< units::si::plane_angle > > const model_phases_
) noexcept :
  view_radius( view_radius_ * L_coat_ ),
  hp( hp_ ),
  tp( tp_ ),
  coating_slab(  )
  frequencies( frequencies_ ),
  ls(),
  model_phases( model_phases_ )
{
/*

  // nondimentional system properties
  units::quantity< units::si::length > view_radius;
  dimensionless::HeatingProperties hp;
  dimensionless::ThermalProperties tp;
  
  // modeled elements (reconstructed from non-dimensional parameters)
  thermal::model::slab::Slab coating_slab;  
  
  // modulation frequency/thermal penetration
  std::vector< units::quantity< units::si::frequency > > frequencies;
  std::vector< units::quantity< units::si::dimensionless > > ls;

  // model predictions
  std::vector< units::quantity< units::si::plane_angle > > model_phases;

*/

}

} // namespace estimate_parameters
} // namespace tbc2009
} // namespace analysis
} // namespace thermal
