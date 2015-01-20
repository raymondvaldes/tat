//
//  Header.h
//  tat
//
//  Created by Raymond Valdes on 1/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_Header_h
#define tat_Header_h


#include "math/functions/PeriodicProperties.h"

namespace math {
  
namespace functions {
 
template< typename T >
class Periodic: public PeriodicProperties<T>
{
private:
  virtual auto evaluate( const units::quantity<units::si::time> time ) const
  noexcept  -> units::quantity<T> = 0;
  
public:
  explicit Periodic(
    const PeriodicProperties<T> inputProperties
  ) noexcept
  : PeriodicProperties<T>( inputProperties )
  {}
  
  auto operator()( const units::quantity<units::si::time> inputTime  ) const
  -> units::quantity<T>
  {
    return evaluate( inputTime ) ;
  }
  
};
  
} // namespace functions
  
} // namespace math

#endif
