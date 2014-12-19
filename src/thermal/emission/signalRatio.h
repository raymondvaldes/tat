//
//  signalRatio.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__signalRatio__
#define __tat__signalRatio__

#include "thermal/emission/signal.h"
#include "units/si/si.h"

namespace thermal {
namespace emission {
  
template< class signalType >
auto signalRatio( const Signal<signalType> first,
                  const Signal<signalType> second )
  -> units::quantity< units::si::dimensionless >
{
  return first.getIntensity() / second.getIntensity() ;
}
  
}}
#endif /* defined(__tat__signalRatio__) */
