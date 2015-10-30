//
//  extract_frequency.h
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_gTBC_gTBD__extract_frequency__
#define __tat_gTBC_gTBD__extract_frequency__

#include <vector>
#include "units.h"

namespace gTBC{
namespace gMeasure{

auto extract_frequency
(

)
noexcept -> std::vector< units::quantity< units::si::frequency> >;

} // namespace gMeasure
} // namespace gTBC

#endif /* defined(__tat__extract_frequency__) */
