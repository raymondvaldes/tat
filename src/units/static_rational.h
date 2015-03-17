//
//  static_rational.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_static_rational_h
#define tat_static_rational_h

#include <boost/units/static_rational.hpp>

namespace units {

typedef boost::units::integer_type integer_type;

template<integer_type N, integer_type D = 1>
  using static_rational = boost::units::static_rational< N >;
  
} // namespace units

#endif
