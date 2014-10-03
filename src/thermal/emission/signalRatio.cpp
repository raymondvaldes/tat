//
//  signalRatio.cpp
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "thermal/emission/signalRatio.h"


namespace thermal {
  namespace emission {


  
auto signalRatio( const Signal first, const Signal second ) ->
  units::quantity< units::si::dimensionless > {
  
  return second.getIntensity() / first.getIntensity() ;

}


  
}}