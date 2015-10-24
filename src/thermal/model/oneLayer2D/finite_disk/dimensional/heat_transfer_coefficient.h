//
//  heat_transfer_coefficient.h
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef heat_transfer_coefficient_h_101615
#define heat_transfer_coefficient_h_101615

#include "units.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace dimensional{

using Heat_transfer_coefficient =
  units::quantity< units::si::heat_transfer_coefficient >;

} // dimensional
} // finite_disk
} // oneLayer2d
} // model
} // thermal


#endif /* heat_transfer_coefficient_h */
