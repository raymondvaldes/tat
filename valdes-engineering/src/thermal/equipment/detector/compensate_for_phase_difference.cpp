//
//  compensate_for_phase_difference.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/21/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "compensate_for_phase_difference.h"
#include "math/curveFit/cosine.h"
#include "math/functions/periodicData.h"
#include "physics/classical_mechanics/kinematics.h"
#include "thermal/equipment/detector/fitted_measurements.h"
#include "statistics/signal_processing/average.h"
#include "algorithm/algorithm.h"

namespace thermal {

namespace equipment {

namespace detector {

using std::make_pair;
using algorithm::for_each;
using thermal::equipment::detector::fitted_measurements;
using statistics::signal_processing::average;
using physics::classical_mechanics::get_delta_time_from_phase;
using namespace units;

auto phase_difference
(
  std::pair< Measurements, Measurements > const & m,
  units::quantity< units::si::frequency > const freq
) -> units::quantity< units::si::plane_angle >
{
  auto const fitted_first = fitted_measurements( m.first, freq );
  auto const fitted_second = fitted_measurements( m.second, freq );

  auto const phase_shift = abs( fitted_first.phase - fitted_second.phase ) ;
  return phase_shift;
}

auto compensate_for_phase_difference
(
  std::pair< Measurements, Measurements > const & m,
  units::quantity< units::si::frequency > const freq
) -> std::pair< Measurements, Measurements >
{
  auto const first = fitted_measurements( m.first, freq );
  auto const second = fitted_measurements( m.second, freq );

  auto const phase_error = abs( first.phase - second.phase ) ;
  
  auto const average_phase =
  average( { first.phase, second.phase } );
  
  auto const delta_time = get_delta_time_from_phase( phase_error, freq );
  auto const time_error = delta_time / quantity<dimensionless>{ 2. };
  
  //Recreate measurement vector by sampling at new times from the fitted.
  auto const count = m.first.size();
  auto const times = m.first.referenceTimes();
  
  auto times_1 = std::vector< quantity< si::time > >{};
  times_1.reserve( count ) ;
  
  auto times_2 = std::vector< quantity< si::time > >{};
  times_2.reserve( count ) ;

  auto signal_1 = std::vector< quantity< electric_potential> >{};
  signal_1.reserve( count );
  
  auto signal_2 = std::vector< quantity< electric_potential> >{};
  signal_2.reserve( count );
  
  for_each( times, [&]( auto const time ) noexcept
  {
    auto t1 = time;
    auto t2 = time;
    
    if( first.phase > average_phase )
    {
      t1 -= time_error;
      t2 += time_error;
    }
    else if( first.phase < average_phase )
    {
      t1 += time_error;
      t2 -= time_error;
    }
    
    times_1.push_back( time );
    times_2.push_back( time );
    signal_1.push_back( first.evaluate( t1 ) ) ;
    signal_2.push_back( second.evaluate( t2 ) );
  } ) ;
  
  auto const m1_updated = Measurements( m.first.wavelength, times_1, signal_1  );
  auto const m2_updated = Measurements( m.second.wavelength, times_2, signal_2 );
  
  auto const m_updated = make_pair( m1_updated, m2_updated ) ;


  return m_updated;
}


} // namespace detector

} // namespace equipment

} // namespace thermal
