//
//  double_to_quantity.h
//  tat
//
//  Created by Raymond Valdes on 10/29/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef double_to_quantity_h_102915
#define double_to_quantity_h_102915


#include <vector>
#include <algorithm>

#include "units.h"

namespace units {
namespace container {

template< typename UnitType, typename UnitDimension>
auto double_to_quantity( std::vector< double > const & input, UnitDimension const & myDim  )
noexcept -> std::vector< units::quantity< UnitType > >
{
  using std::vector;
  using std::transform;
  using std::begin;
  using std::end;

  auto output = vector< units::quantity< UnitType > >( input.size() ) ;

  transform( begin( input ), end( input ), begin( output ),
  [&]( auto const& val ) noexcept
  {
    auto const val_Dimensioned = units::quantity< UnitType > ( val * myDim ) ;
    return val_Dimensioned  ;
  } );
  
  return output;
}

}} // namespace

#endif /* double_to_quantity_h */
