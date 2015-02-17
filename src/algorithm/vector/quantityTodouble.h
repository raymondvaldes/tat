//
//  quantityTodouble.h
//  tat
//
//  Created by Raymond Valdes_New on 2/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__quantityTodouble__
#define __tat__quantityTodouble__

#include <vector>
#include <algorithm>

#include "units.h"
namespace algorithm {

namespace vector {

template< typename UnitType >
auto quantityTodouble( const std::vector< units::quantity< UnitType > >  &input )
noexcept -> std::vector< double >
{
  using std::vector;
  using std::transform;
  using std::begin;
  using std::end;

  vector<double> output( input.size() ) ;

  transform( begin( input ), end( input ), begin( output ), []( const auto& val )
  {
    return val.value();
  } );
  
  return output;
}

template< typename UnitType >
auto doubleToQuantity( const std::vector< double >  &input )
noexcept -> std::vector< units::quantity< UnitType > >
{
  using std::vector;
  using std::transform;
  using std::begin;
  using std::end;

  vector< units::quantity< UnitType > > output( input.size() ) ;

  transform( begin( input ), end( input ), begin( output ), []( const auto& val )
  {
    return units::quantity< UnitType >::from_value( val )  ;
  } );
  
  return output;
}
  
} // namespace vector
  
} // namespace algorithm

#endif /* defined(__tat__quantityTodouble__) */
