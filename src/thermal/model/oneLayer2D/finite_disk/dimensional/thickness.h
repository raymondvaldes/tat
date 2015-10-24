//
//  thickness.h
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef thickness_h_101615
#define thickness_h_101615


#include "units.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace disk{

using thickness = units::quantity< units::si::length >;


} // disk
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* thickness_h */
