//
//  cosine.h
//  tat
//
//  Created by Raymond Valdes on 1/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_cosine_h
#define tat_cosine_h

#include <vector>
#include "math/functions/periodic.h"
#include "algorithm/algorithm.h"
#include "units.h"

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
    using units::cos;
    
    auto const angle = this->omega * time + this->phase ;
    return this->offset + this->amplitude * cos( angle.value() ) ;
  }
  
  auto evaluate( std::vector< units::quantity< units::si::time > > const & time_evals) const noexcept
  -> std::vector< units::quantity< T > >
  {
    auto evaluations = std::vector< units::quantity<T> >( time_evals.size() );
    using algorithm::transform;
    
    transform( time_evals, evaluations.begin(), [&]( auto const time ) noexcept
    {
      return evaluate( time );
    } );
    
    return evaluations;
  }
  
  explicit Cosine(
    const PeriodicProperties<T> inputProperties
  ) noexcept
  : Periodic<T>( inputProperties )
  {}
};

} // namespace functions

} // namespace math

#endif
