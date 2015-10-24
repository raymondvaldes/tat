//
//  radial_coordinate.h
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef radial_coordinate_h_101615
#define radial_coordinate_h_101615

#include "units.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace dimensional{

using Radial_coordinate = units::quantity< units::si::length >;

} // dimensional
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* radial_coordinate_h */
