//
//  si.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_si_h
#define tat_si_h

#include "units/quantity.h"
#include "units/si/predefined.h"


namespace units {

namespace si{

  template< class T>
  constexpr auto
  scale_by_nondimensional( const quantity<T> &input , const double multiplier )
  {
    return input * quantity< dimensionless >( multiplier );
  }

} // namespace si

} // namespace units

#endif
