//
//  SystemProperties.h
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_thermal_model_tbc2009_ThermalProperties_h
#define tat_thermal_model_tbc2009_ThermalProperties_h

#include "units.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

struct ThermalProperties
{
  units::quantity< units::si::dimensionless > gamma;
  units::quantity< units::si::dimensionless > a_sub;
  units::quantity< units::si::dimensionless > c_coat;

  explicit ThermalProperties
  (
    units::quantity< units::si::dimensionless > gamma_,
    units::quantity< units::si::dimensionless > a_sub_,
    units::quantity< units::si::dimensionless > c_coat_
  ) noexcept;
};
  
} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif
