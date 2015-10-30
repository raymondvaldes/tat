//
//  PeriodicProperties_update_phases.h
//  tat
//
//  Created by Raymond Valdes on 10/5/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef PeriodicProperties_update_phases_h
#define PeriodicProperties_update_phases_h

#include <vector>
#include <cassert>
#include "algorithm/algorithm.h"
#include "PeriodicProperties.h"
#include "units.h"

namespace math{
namespace functions{

template< typename T >
auto PeriodicProperties_update_phases
(
  std::vector< math::functions::PeriodicProperties< T  > > const & periodicproperties_list,
  std::vector< units::quantity< units::si::plane_angle > > const & phases
) noexcept -> std::vector< math::functions::PeriodicProperties< T > >
{
  using algorithm::transform;
  using std::vector;
  using math::functions::PeriodicProperties;
  using namespace units;
  
  assert( !phases.empty() );
  assert( !periodicproperties_list.empty() );
  assert( periodicproperties_list.size() == phases.size() );
  
  auto updated_properties_list = periodicproperties_list;
  
  transform( periodicproperties_list,  phases, begin( updated_properties_list ),
  [] ( auto const property, auto const phase ) noexcept
  {
    auto const amplitude = property.get_amplitude();
    auto const offset = property.get_offset();
    auto const frequency = property.get_temporalFrequency();
  
    auto const updated_property =
      PeriodicProperties< T >( offset , amplitude, frequency, phase  );
    
    return updated_property;
  } );

  assert( updated_properties_list.front().phase == phases.front() );
  assert( updated_properties_list.back().phase == phases.back() );
  

  return updated_properties_list;
}

} // namespace functions
} // namespace math

#endif /* PeriodicProperties_update_phases_h */
