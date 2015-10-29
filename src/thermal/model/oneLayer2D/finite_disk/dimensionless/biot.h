//
//  biot.h
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef biot_h_1016165
#define biot_h_1016165

#include "units.h"
#include "thermal/model/oneLayer2D/finite_disk/dimensional/heat_transfer_coefficient.h"
#include "thermal/model/oneLayer2D/finite_disk/disk/thermal_conductivity.h"
#include "thermal/model/oneLayer2D/finite_disk/dimensional/characteristic_length.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace dimensionless{

using Biot = units::quantity< units::si::dimensionless >;

auto biot(
  dimensional::Heat_transfer_coefficient const h,
  dimensional::Characteristic_length const L,
  disk::Thermal_conductivity const k
  ) noexcept -> Biot;
  

} // dimensionless
} // finite_disk
} // oneLayer2d
} // model
} // thermal


#endif /* biot_h */
