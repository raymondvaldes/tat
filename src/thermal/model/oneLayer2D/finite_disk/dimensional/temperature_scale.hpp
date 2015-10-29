//
//  temperature_scale.hpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef temperature_scale_hpp_102615
#define temperature_scale_hpp_102615

#include "units.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace dimensional{

using Temperature_scale = units::quantity< units::si::temperature >;

} // dimensional
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* temperature_scale_hpp */
