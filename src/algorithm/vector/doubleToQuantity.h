//
//  doubleToQuantity.h
//  tat
//
//  Created by Raymond Valdes_New on 2/17/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_doubleToQuantity_h
#define tat_doubleToQuantity_h

#include <vector>
#include <algorithm>

#include "units.h"

namespace algorithm {

namespace vector {

template< typename UnitType, typename UnitDimension>
auto doubleToQuantity( std::vector< double > const & input, UnitDimension const & myDim  )
noexcept -> std::vector< units::quantity< UnitType > >
{
  using std::vector;
  using std::transform;
  using std::begin;
  using std::end;

  auto output = vector< units::quantity< UnitType > >( input.size() ) ;

  transform( begin( input ), end( input ), begin( output ),
  [&]( const auto& val ) noexcept
  {
    auto const val_Dimensioned = units::quantity< UnitType > ( val * myDim ) ;
    return val_Dimensioned  ;
  } );
  
  return output;
}
  
} // namespace vector
  
} // namespace algorithm

#endif
