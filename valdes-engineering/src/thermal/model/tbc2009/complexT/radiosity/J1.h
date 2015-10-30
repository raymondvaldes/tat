//
//  J1.h
//  tat
//
//  Created by Raymond Valdes on 3/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_tbc2009_model_J1__
#define __tat_tbc2009_model_J1__

#include "units.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace complexT{
namespace radiosity{

auto J1
(
  units::quantity< units::si::dimensionless > const R0,
  units::quantity< units::si::dimensionless > const R1,
  units::quantity< units::si::dimensionless > const Lambda
) noexcept -> units::quantity< units::si::dimensionless >;

} // namespace radiosity
} // namespace complexT
} // namespace tbc2009
} // namespace model
} // namespace thermal


#endif /* defined(__tat_tbc2009_model_J1__) */
