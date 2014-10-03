//
//  calibrationCoefficient.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__calibrationCoefficient__
#define __tat__calibrationCoefficient__

#include "thermal/emission/signal.h"
#include "units/si/si.h"
#include "thermal/emission/signalRatio.h"

namespace thermal {
namespace pyrometry {
namespace twoColor {

template< class signalType >
auto calibrationCoefficient(
  const emission::Signal< signalType > first,
  const emission::Signal< signalType > second,
  const units::quantity< units::si::temperature> Temp ) -> double
{


  auto input = signalRatio( first, second ) ;
  
  
  
  auto
  output = signalRatio( first, second ) ;
  

  return Temp.value();
};


}}}

#endif /* defined(__tat__calibrationCoefficient__) */
