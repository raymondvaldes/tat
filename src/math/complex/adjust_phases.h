//
//  adjust_phases.h
//  tat
//
//  Created by Raymond Valdes on 9/2/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef adjust_phases_h
#define adjust_phases_h

#include "math/complex/adjust_phase.h"
#include <vector>
#include "units.h"
#include "algorithm.h"

namespace math{
namespace complex{

template< typename T>
auto adjust_phases
(
  std::vector< properties<T> > const & complex_quantities,
  std::vector< units::quantity< units::si::plane_angle> > const & phase_offsets
)
{
  // establish preconditions
  using std::isfinite;
  using algorithm::for_each;
  assert( !complex_quantities.empty() );
  assert( !phase_offsets.empty() );
  assert( complex_quantities.size() == phase_offsets.size() );
  for_each( phase_offsets, []( auto const p ){
    assert( isfinite( p.value() ) );
  } );
  
  
  using namespace units;
  using std::vector;
  using algorithm::transform;
  
  auto calibrated_phases =
    vector< properties<T> >( phase_offsets.size());

  transform( complex_quantities, phase_offsets, calibrated_phases.begin(),
  []( auto const complex_quantity, auto const offset ) noexcept
  {
    return adjust_phase( complex_quantity, offset ) ;
  }
   );

  return calibrated_phases;
}

}
}

#endif /* adjust_phases_h */
