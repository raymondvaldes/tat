//
//  periodicData.h
//  tat
//
//  Created by Raymond Valdes on 1/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_periodicData_h
#define tat_periodicData_h
#include <utility>
#include <algorithm>    // std::minmax_element
#include <numeric>      // std::accumulate
#include <vector>       // std::vector
#include <cassert>      // assert

#include "algorithm.h"
#include "units.h"  // units::quantity

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
    std::pair< std::vector< units::quantity<units::si::time> >,
    std::vector< units::quantity< T > > > const & input ) noexcept
    : PeriodicData{ input.first, input.second }  {}

  explicit PeriodicData(
    const std::vector< units::quantity<units::si::time> > timeIn,
    const std::vector< units::quantity< T > > signalsIn
  ) noexcept
  : timeVector( timeIn ), dataVector( signalsIn )
  {
    assert( !timeVector.empty() ) ;
    assert( !dataVector.empty() ) ;
    assert( timeVector.size() == dataVector.size() );
  }
  
  auto initialEstimateAmplitude() const
  noexcept -> units::quantity< T >
  {
    using units::quantity;
    using units::si::dimensionless;
    using std::minmax_element;
    
    auto const result = minmax_element ( dataVector.begin(), dataVector.end() ) ;
    
    auto const min = *result.first;
    auto const max = *result.second;

    return ( max - min ) / quantity< dimensionless >( 2 );
  };
  
  auto initialEstimateOffset() const
  noexcept -> units::quantity< T >
  {
    using units::quantity;
    using algorithm::accumulate;
    using units::si::dimensionless;
    
    auto const sum = accumulate( dataVector, quantity< T >::from_value( 0 ) );
    auto const count = quantity< dimensionless >( dataVector.size() );
    auto const average = sum / count ;

    return average;
  }
  
};

} // namespace functions

} // namespace math

#endif
