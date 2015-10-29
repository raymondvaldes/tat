//
//  thermal_conductivity.h
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef thermal_conductivity_h_101615
#define thermal_conductivity_h_101615

#include "units.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace disk{

using Thermal_conductivity = units::quantity< units::si::thermal_conductivity >;

} // disk
} // finite_disk
} // oneLayer2d
} // model
} // thermal


#endif /* thermal_conductivity_h */
