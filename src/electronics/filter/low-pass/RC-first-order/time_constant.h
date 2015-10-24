//
//  time_constant.h
//  tat
//
//  Created by Raymond Valdes on 10/19/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef time_constant_hh_101915
#define time_constant_hh_101915

#include "units.h"

namespace electronics { namespace filter { namespace low_pass { namespace RC_first_order{

using Time_constant = units::quantity< units::si::electrical_time_constant >;

} } } } // namespace

#endif /* time_constant_h */
