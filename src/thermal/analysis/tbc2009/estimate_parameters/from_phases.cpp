//
//  estimate_properties.cpp
//  tat
//
//  Created by Raymond Valdes on 3/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/analysis/tbc2009/estimate_parameters/from_phases.h"
#include "thermal/model/tbc2009/dimensionless/coating_from_dimensionless.h"
#include "thermal/define/lthermal.h"

namespace thermal {
namespace analysis {
namespace tbc2009 {
namespace estimate_parameters{

using model::tbc2009::dimensionless::coating_from_dimensionless;
using thermal::define::thermalPenetrations_from_frequencies;

Best_fit::Best_fit
(
  units::quantity< units::si::length > const L_coat_,
  units::quantity< units::si::dimensionless > const view_radius_,
  thermal::model::slab::Slab const substrate_slab,
  model::tbc2009::dimensionless::HeatingProperties const hp_,
  model::tbc2009::dimensionless::ThermalProperties const tp_,
 
  std::vector< units::quantity<units::si::frequency> > const  frequencies_,
  std::vector< units::quantity< units::si::plane_angle > > const model_phases_
) noexcept :
  view_radius( view_radius_ * L_coat_ ),
  hp( hp_ ),
  tp( tp_ ),
  coating_slab( coating_from_dimensionless( L_coat_, tp, substrate_slab ) ),
  frequencies( frequencies_ ),
  ls( thermalPenetrations_from_frequencies(
        frequencies_, coating_slab.get_diffusivity() , L_coat_ ) ),
  model_phases( model_phases_ )
{}

} // namespace estimate_parameters
} // namespace tbc2009
} // namespace analysis
} // namespace thermal
