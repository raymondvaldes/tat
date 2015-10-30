//
//  coating_from_dimensionless.h
//  tat
//
//  Created by Raymond Valdes on 3/31/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_tbc2009_dimenionless_coating_from_dimensionless__
#define __tat_thermal_model_tbc2009_dimenionless_coating_from_dimensionless__

#include "units.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/tbc2009/dimensionless/ThermalProperties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

auto coating_from_dimensionless
(
  units::quantity< units::si::length > const L_coat,
  ThermalProperties const tp,
  slab::Slab substrate
) noexcept -> slab::Slab;

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif /* defined(__tat__coating_from_dimensionless__) */
