//
//  residuals_square.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_residuals_square_h
#define tat_residuals_square_h

namespace statistics {

namespace signal_processing {

#include <vector>
#include <cassert>

#include "statistics/signal_processing/average.h"

#include "algorithm/algorithm.h"
#include "units.h"

template< typename T >

auto residuals_square( std::vector< units::quantity<T> > const & signals )
{
  using std::vector;
  using units::quantity;
  using algorithm::transform;
  
  auto const mean = average( signals );
  
  typedef typename units::power_typeof_helper< units::quantity<T> , units::static_rational<2> >::type unit2;
  
  auto const empty = units::power_typeof_helper< units::quantity<T> , units::static_rational<2> >::value( 0 ) ;
  auto const count = signals.size();
  auto residuals = std::vector< unit2 >( count , empty );
  
  transform( signals.begin(), signals.end(), residuals.begin(),
  [ &mean ]( auto const signal ) noexcept
  {
    return units::pow< 2 >( signal  - mean );
  } ) ;
  

  return residuals;
}
  
} // namespace signal_processing
  
} // namespace statistics

#endif
