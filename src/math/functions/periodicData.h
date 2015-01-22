//
//  periodicData.h
//  tat
//
//  Created by Raymond Valdes on 1/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_periodicData_h
#define tat_periodicData_h

#include <algorithm>    // std::minmax_element
#include <numeric>      // std::accumulate
#include <vector>       // std::vector
#include <cassert>      // assert

#include "units/units.h"  // units::quantity

namespace math {
  
namespace functions {

template< typename T >
class PeriodicData
{
private:
  const std::vector< units::quantity<units::si::time> > timeVector;
  const std::vector< units::quantity<T>> dataVector;
  
public:
  explicit PeriodicData(
    const std::vector< units::quantity<units::si::time> > timeIn,
    const std::vector< units::quantity< T > > signalsIn
  ) noexcept
  : timeVector( timeIn ), dataVector( signalsIn )
  {
    const auto timeVectorSize = timeVector.size();
    const auto dataVectorSize = dataVector.size();
    assert( timeVectorSize > 0 ) ;
    assert( dataVectorSize > 0 ) ;
    assert( timeVectorSize == dataVectorSize );
  }
  
  auto initialEstimateAmplitude() noexcept
  -> units::quantity< T >
  {
    using units::quantity;
    using units::si::dimensionless;
    using std::minmax_element;
    
    const auto result = minmax_element ( dataVector.begin(), dataVector.end() ) ;
    
    const auto min = *result.first;
    const auto max = *result.second;

    return ( max - min ) / quantity< dimensionless >( 2 );
  };
  
  auto initialEstimateOffset() noexcept
  -> units::quantity< T >
  {
    using units::quantity;
    using std::accumulate;
    using units::si::dimensionless;
    
    const auto sum =
    accumulate( dataVector.begin(), dataVector.end(),
    quantity< T >::from_value( 0 ) );

    auto average = sum / quantity< dimensionless >( dataVector.size() );

    return average;
  }
  
};

} // namespace functions

} // namespace math

#endif
