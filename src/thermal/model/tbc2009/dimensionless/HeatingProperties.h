//
//  OpticalProperties.h
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_thermal_model_tbc2009_OpticalProperties_h
#define tat_thermal_model_tbc2009_OpticalProperties_h

#include "units.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

struct HeatingProperties
{
  units::quantity< units::si::dimensionless > Lambda;
  units::quantity< units::si::dimensionless > R0;
  units::quantity< units::si::dimensionless > R1;
  units::quantity< units::si::dimensionless > b;
  
  explicit HeatingProperties(
  units::quantity< units::si::dimensionless > const Lambda_,
  units::quantity< units::si::dimensionless > const R0_,
  units::quantity< units::si::dimensionless > const R1_,
  units::quantity< units::si::dimensionless > const b_ ) noexcept;

};

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal

#endif
