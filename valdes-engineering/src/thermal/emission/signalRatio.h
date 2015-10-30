//
//  signalRatio.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__signalRatio_1341234534_
#define __tat__signalRatio_1341234534_

#include <cassert>

#include "thermal/emission/signal.h"
#include "units/si/si.h"

namespace thermal {

namespace emission {
  
template< class signal_type >
auto signalRatio( Signal< signal_type > const & first,
                  Signal< signal_type > const & second )
noexcept -> units::quantity< units::si::dimensionless >
{
  assert( first < second );

  return second.getIntensity() / first.getIntensity() ;
}
  
} // namespace emission

} // namespace thermal

#endif /* defined(__tat__signalRatio__) */
