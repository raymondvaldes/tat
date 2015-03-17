//
//  scale.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_scale_h
#define tat_scale_h

#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/scale.hpp>

#include "units/static_rational.h"

namespace units {


template<long Base, typename Exponent>
  using scale = boost::units::scale< Base, Exponent > ;

template<class Unit,class Y = double>
  using make_scaled_unit = boost::units::make_scaled_unit<Unit, Y>;




}

#endif
