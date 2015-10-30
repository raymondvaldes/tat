//
//  characteristic_length.h
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef characteristic_length_h_101615
#define characteristic_length_h_101615

#include "units.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace dimensional{

using Characteristic_length = units::quantity< units::si::length >;

} // dimensional
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* characteristic_length_h */
