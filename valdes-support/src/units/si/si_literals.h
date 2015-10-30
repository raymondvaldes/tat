//
//  si_literals.h
//  tat
//
//  Created by Raymond Valdes on 4/1/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_si_literals_h
#define tat_si_literals_h

#include "units/quantity.h"
#include "units/si/predefined.h"

namespace units{
inline namespace si{

inline
auto
operator"" _nd ( long double const n )
noexcept -> quantity< dimensionless >
{
    return quantity< dimensionless >(n);
}

} // namespace si
} // namespace units
#endif
