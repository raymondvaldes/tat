//
//  amplitude.h
//  tat
//
//  Created by Raymond Valdes on 10/15/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef amplitude_h_101515
#define amplitude_h_101515

#include "units.h"
#include <vector>

namespace thermal{
namespace model{
namespace complex{

using Amplitude  = units::quantity< units::si::temperature >;
using Amplitudes = std::vector< Amplitude >;

} // namespace complex
} // namespace model
} // namespace thermal

#endif /* amplitude_h */
