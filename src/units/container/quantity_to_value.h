//
//  quantity_to_double.h
//  tat
//
//  Created by Raymond Valdes on 10/29/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef quantity_to_double_h
#define quantity_to_double_h

#include <vector>
#include <algorithm>
#include <cassert>

#include "units.h"

namespace units{
namespace container {

template< typename UnitType >
auto quantity_to_double( std::vector< units::quantity< UnitType > > const & input )
noexcept -> std::vector< double >
{
  using std::vector;
  using std::transform;
  using std::begin;
  using std::end;
  assert( input.size() > 0 );

  vector<double> output( input.size() ) ;

  transform( begin( input ), end( input ), begin( output ),
  []( auto const& val )
  {
    return val.value();
  } );
  
  return output;
}
  
} // namespace container
} // namespace units

#endif /* quantity_to_double_h */
