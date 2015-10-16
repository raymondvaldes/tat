//
//  specimenE_low_laser_high_stage.h
//  tat
//
//  Created by Raymond Valdes on 9/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef specimenE_low_laser_high_sta1234123ge_h
#define specimenE_low_laser_high_sta1234123ge_h

#include "thermal/model/slab/slab.h"
#include <vector>
#include "units.h"
#include "thermal/experimental/observations/slab/slab.hpp"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace heated_stage{
namespace sept23{

inline auto specimenE_low_laser_high_stage( void )
noexcept -> thermal::experimental::observations::Slab
{
  using std::vector;
  using namespace units;
  using thermal::experimental::observations::Slab;

  auto const frequencies = vector< quantity< frequency > >({
    8 * hertz,
    11.31370898 * hertz,
    16 * hertz,
    22.62741797 * hertz,
    32 * hertz,
    
    45.25483594 * hertz,
    64 * hertz,
    90.50967188 * hertz,
    
    128 * hertz,
    181.0193438 * hertz,
    256 * hertz,

    362.0386875 * hertz,
    512 * hertz
  });


  auto const experimental_phases = vector< quantity< plane_angle > >( {
  1.151 * radians, //  8     Hz
  1.058 * radians, //  11.314  Hz
  0.950 * radians, //  16.0    Hz
  0.849 * radians, //  22.627  Hz
  0.779 * radians, //  32.0    Hz

  0.749 * radians, //  45.255  Hz
  0.763 * radians, //  64.0    Hz
  .766 * radians, //  90.510  Hz

  0.786 * radians,  // 128      Hz
  0.787 * radians,   // 181.019  Hz
  0.788 * radians, // 256      Hz

  0.789 * radians, // 362.039  Hz
  .787 * radians, // 512      Hz
    } );
  
  auto const L = quantity< length > ( 0.800 * millimeters  );// sample E
  auto const diffusivity = quantity<thermal_diffusivity>( 50 * square_millimeters / second);
  auto const conductivity_dummey =
    quantity< thermal_conductivity >( 100 * watts / meter / si::kelvin );
  

  auto const initial_slab =
  thermal::model::slab::Slab( L, diffusivity, conductivity_dummey );
  auto const beam_radius = quantity< length >( 4.4 * millimeters );

  auto const specimen =
  Slab( initial_slab, frequencies, experimental_phases, beam_radius );
  
  return specimen;
};

} // namespace sept22
} // namespace heat_stage
} // namespace beamExpander
} // namespace bulkDiffusivityMeasurements2015
} // namespace investigations

#endif /* specimenE_low_laser_high_stage_h */
