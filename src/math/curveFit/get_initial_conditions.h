//
//  get_initial_conditions.h
//  tat
//
//  Created by Raymond Valdes on 3/22/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_get_initial_conditions_h
#define tat_get_initial_conditions_h

#include <utility>
#include "math/functions/periodicData.h"
#include "math/functions/PeriodicProperties.h"

namespace math {
  
namespace curveFit {

template< typename T >
auto get_initial_conditions
(
  std::pair<
    std::vector< units::quantity< units::si::time > >,
    std::vector< units::quantity< T > > > const & data,
  units::quantity< units::si::angular_frequency > const omega
)
{
  using math::functions::PeriodicData;
  using math::functions::PeriodicProperties;
  using namespace units;
  
  auto const periodic_data = PeriodicData< T >( data ) ;
  auto const initial =  PeriodicProperties< T >
  {
    periodic_data.initialEstimateOffset(),
    periodic_data.initialEstimateAmplitude(),
    omega,
    quantity< plane_angle >{ -.1 * radians }
  } ;
  
  return initial;
};

  
} // namespace curveFit
  
} // namespace math

#endif
