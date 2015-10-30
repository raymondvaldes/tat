//
//  string_to_double.h
//  tat
//
//  Created by Raymond Valdes on 10/29/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef string_to_doqble_h
#define string_to_doqble_h

#include "double_to_quantity.h"
#include "algorithm/vector/stringToDouble.h"

namespace units{
namespace container{

template< typename UnitType, typename UnitDimension>
auto string_to_quantity( std::vector< std::string > const & input, UnitDimension const & myDim  )
noexcept -> std::vector< units::quantity< UnitType > >
{
  auto const doubles = algorithm::vector::stringToDouble( input ) ;
  auto const quantities = double_to_quantity< UnitType >( doubles, myDim ) ;

  return quantities;
}

}} // namespace

#endif /* string_to_double_h */
