//
//  biot.cpp
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "biot.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace dimensionless{

auto biot(
  dimensional::Heat_transfer_coefficient const h,
  dimensional::Characteristic_length const L,
  disk::thermal_conductivity const k
) noexcept -> Biot
{
//  auto const hL = ;

  auto const biot_number = h * L  / k ;
  return biot_number;
}
  
} // dimensionless
} // finite_disk
} // oneLayer2d
} // model
} // thermal
