//
//  cosine.h
//  tat
//
//  Created by Raymond Valdes on 1/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_cosine_h_1241253
#define tat_cosine_h_1241253

#include <vector>
#include <cstddef>
#include <utility>
#include <cmath>

#include "math/functions/periodic.h"
#include "math/construct/periodic_time_distribution.h"
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
    assert( !time_evals.empty() );
    for( auto t : time_evals )  {
      assert( std::isfinite(t.value()) );
    }
  
    auto evaluations = std::vector< units::quantity<T> >( time_evals.size() );
    using algorithm::transform;
    
    transform( time_evals, evaluations.begin(), [&]( auto const time ) noexcept
    {
      return evaluate( time );
    } );
    
    return evaluations;
  }
  
  auto evaluate_for_n_periods( size_t N_periods, size_t N_values ) const noexcept
  -> std::pair<
    std::vector< units::quantity< units::si::time > > ,
    std::vector< units::quantity< T > >
  >
  {
    assert( N_periods > 0 );
    assert( N_values > 0 );
    
    using std::make_pair;
    using math::construct::periodic_time_distribution;
    
    //create time distribution
    auto const frequency = this->get_temporalFrequency() ;
    auto const cycles = N_periods;
    auto const count = N_values;
    
    auto const time_distribution =
      periodic_time_distribution( frequency, cycles, count  );
    
    
    //call evaluate on distribution
    auto const signal_evaluations = evaluate( time_distribution );
    
    auto const evaluations = make_pair(time_distribution,  signal_evaluations );
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
