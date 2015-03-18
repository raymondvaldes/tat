//
//  conversions.h
//  tat
//
//  Created by Raymond Valdes_New on 3/18/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_conversions_h
#define tat_conversions_h

#include <string>

#include "units/quantity.h"

namespace units{

template< typename UnitType, typename UnitDimension>
auto string_to_quantity( std::string const input, UnitDimension const & myDim )
{
  using std::stod;
  
  auto const myDouble = stod( input );
  auto const myQuantity = quantity< UnitType > ( myDouble * myDim ) ;

  return myQuantity;
}
  
template< typename UnitType , typename Val_type >
auto string_to_quantity( std::string const input )
{
  using std::stod;
  
  auto const myDouble = stod( input );
  auto const myQuantity = quantity< UnitType, Val_type > ( myDouble ) ;

  return myQuantity;
}
  
  
} // namespace units


#endif
