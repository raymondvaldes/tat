//
//  periodicData.h
//  tat
//
//  Created by Raymond Valdes on 1/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_periodicData_h
#define tat_periodicData_h

#include <vector>
#include "units/units.h"
#include "math/functions/periodic.h"
#include <algorithm>    // std::minmax_element  


namespace math {
  
namespace functions {

template< typename T >
class PeriodicData
{
private:
  const std::vector< units::quantity<units::si::time> > time;
  const std::vector< units::quantity<T>> signals;
  
public:
  explicit PeriodicData(
    const std::vector< units::quantity<units::si::time> > timeIn,
    const std::vector< units::quantity< T > > signalsIn
  ) noexcept
  : time( timeIn ), signals( signalsIn )
  {}
  
  auto initialEstimateAmplitude()-> units::quantity< T >
  {
    using std::minmax_element;
    auto result = minmax_element ( signals.begin(), signals.end() ) ;
    const auto min = *result.first;
    const auto max = *result.second;

    return (max - min) / units::quantity<units::si::dimensionless>( 2 );
  };
  
  auto initialEstimateOffset() -> units::quantity< T >
  {
    auto sum = units::quantity< T >::from_value( 0 ) ;
    for( auto &val : signals )
    {    sum += val; }

    auto average =
    sum / units::quantity< units::si::dimensionless >( signals.size() );

    return average;
  }
  
  

  
};

  
} // namespace functions

} // namespace math

#endif
