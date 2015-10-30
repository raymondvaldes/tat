//
//  phase.h
//  tat
//
//  Created by Raymond Valdes on 10/15/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef phase_h_101515_1234152345
#define phase_h_101515_1234152345

#include "units.h"
#include <vector>

namespace thermal{
namespace model{
namespace complex{

using Phase  = units::quantity< units::si::plane_angle >;
using Phases = std::vector< Phase >;

} // namespace complex
} // namespace model
} // namespace thermal


#endif /* phase_h */
