//
//  stringToQuantity.h
//  tat
//
//  Created by Raymond Valdes_New on 2/17/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_stringToQuantity_h
#define tat_stringToQuantity_h

#include <vector>
#include "units.h"

#include "algorithm/vector/stringToDouble.h"
#include "algorithm/vector/doubleToQuantity.h"

namespace algorithm {

namespace vector {

template< typename UnitType, typename UnitDimension>
auto stringToQuantity( std::vector< std::string > const & input, UnitDimension const & myDim  )
noexcept -> std::vector< units::quantity< UnitType > >
{
  auto const doubles = stringToDouble( input ) ;
  auto const quantities = doubleToQuantity< UnitType >( doubles, myDim ) ;

  return quantities;
}

  
} // namespace vector
  
} // namespace algorithm

#endif
