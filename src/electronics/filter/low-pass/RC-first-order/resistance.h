//
//  resistance.h
//  tat
//
//  Created by Raymond Valdes on 10/19/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef resistance_h_101915
#define resistance_h_101915

#include "units.h"

namespace electronics { namespace filter { namespace low_pass { namespace RC_first_order{

using Resistance = units::quantity< units::si::electrical_resistance >;

} } } } // namespace

#endif /* resistance_h */
