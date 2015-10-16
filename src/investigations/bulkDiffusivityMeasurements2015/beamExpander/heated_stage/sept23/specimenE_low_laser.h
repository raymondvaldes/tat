//
//  Header.h
//  tat
//
//  Created by Raymond Valdes on 9/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef specimenE_h_0923152334523423
#define specimenE_h_0923152334523423

#include "thermal/model/slab/slab.h"
#include <vector>
#include "units.h"
#include "thermal/experimental/observations/slab/slab.hpp"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace heated_stage{
namespace sept23{

inline auto specimenE_low_laser( void )
noexcept -> thermal::experimental::observations::Slab
{
  using std::vector;
  using namespace units;
  using thermal::experimental::observations::Slab;

  auto const frequencies = vector< quantity< frequency > >({
    1.0 * hertz,
    1.414213623 * hertz,
    2.0 * hertz,
    2.828427246 * hertz,
    4 * hertz,

    5.656854492 * hertz,
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
  1.191 * radians, //  1  Hz
  1.235 * radians, //  1.414  Hz
  1.264 * radians, //  2.0  Hz
  1.280 * radians, //  2.828    Hz
  1.276 * radians, // 4.0  Hz
  1.241 * radians, //  5.657 Hz

  1.184 * radians, //  8     Hz
  1.097 * radians, //  11.314  Hz
  0.991 * radians, //  16.0    Hz
  0.889 * radians, //  22.627  Hz
  0.799 * radians, //  32.0    Hz

  0.738 * radians, //  45.255  Hz
  0.723 * radians, //  64.0    Hz
  0.714 * radians, //  90.510  Hz

  0.775 * radians,  // 128      Hz
  0.781 * radians,   // 181.019  Hz
  0.779 * radians, // 256      Hz

  0.781 * radians, // 362.039  Hz
  0.778 * radians, // 512      Hz
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

#endif /* Header_h */
