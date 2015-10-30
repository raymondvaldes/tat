//
//  signal.h
//  tat
//
//  Created by Raymond Valdes on 10/4/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef signal_h_10415
#define signal_h_10415

#include "units.h"

namespace thermal{
namespace equipment{
namespace detector{

using Signal = units::quantity< units::si::electric_potential >;

} // namespace detector
} // namespace equipment
} // namespace thermal

#endif /* signal_h */
