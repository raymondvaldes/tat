//
//  beam_intensity.h
//  tat
//
//  Created by Raymond Valdes on 10/15/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef beam_intensity_h_101515
#define beam_intensity_h_101515

#include "units.h"

namespace thermal{
namespace equipment{
namespace laser{

using Beam_intensity = units::quantity< units::si::heat_flux >;

} // namespace laser
} // namespace equipment
} // namespace thermal

#endif /* beam_intensity_h */
