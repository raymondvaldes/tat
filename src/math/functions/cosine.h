//
//  cosine.h
//  tat
//
//  Created by Raymond Valdes on 1/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_cosine_h
#define tat_cosine_h

#include "math/functions/periodic.h"

namespace math {
  
namespace functions {

template< typename T >
class Cosine: public Periodic<T>
{
public:
  auto evaluate( const units::quantity<units::si::time> time )
  const noexcept
  -> units::quantity<T>
  {
    using std::cos;
  
    auto const angle = this->omega * time + this->phase ;
    return this->offset + this->amplitude * cos( angle.value() ) ;
  }
  
public:
  explicit Cosine(
    const PeriodicProperties<T> inputProperties
  ) noexcept
  : Periodic<T>( inputProperties )
  {}
};

} // namespace functions

} // namespace math

#endif
