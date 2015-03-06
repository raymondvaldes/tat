//
//  measurement.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__measurement__
#define __tat__measurement__

#include "units.h"

namespace thermal {

namespace equipment {

namespace detector {

struct Measurement {

  units::quantity< units::si::time > reference_time;
  units::quantity< units::si::electric_potential > signal;
  
  Measurement(){};
  
  Measurement( units::quantity< units::si::time > const & timestamp_In,
               units::quantity< units::si::electric_potential > const & signal_In );
};

} // namespace detector

} // namespace equipment

} // namespace thermal

#endif /* defined(__tat__measurement__) */
