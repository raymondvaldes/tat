//
//  beam_power.h
//  tat
//
//  Created by Raymond Valdes on 10/15/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef beam_power_h_101515
#define beam_power_h_101515

#include "units.h"

namespace thermal{
namespace equipment{
namespace laser{

using Beam_power = units::quantity< units::si::power >;

} // namespace laser
} // namespace equipment
} // namespace thermal

#endif /* beam_power_h */
