//
//  A1_rear_100degC.h
//  tat
//
//  Created by Raymond Valdes on 9/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef A1_rear_100degC_h
#define A1_rear_100degC_h

#include "thermal/model/slab/slab.h"
#include <vector>
#include "units.h"
#include "thermal/experimental/observations/slab/slab.hpp"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace adiabatic_rear{
namespace poco_edm3{
namespace sept28{

inline auto A1_rear_100degC( void )
noexcept -> thermal::experimental::observations::Slab
{
  using std::vector;
  using namespace units;
  using thermal::experimental::observations::Slab;

  auto const frequencies = vector< quantity< frequency > >({
//    .088 * hertz,
//    .125 * hertz,
//    .177 * hertz,
//    .250 * hertz,
//    .354 * hertz,
//    .500 * hertz,
//    .707 * hertz,
//
//    1.0 * hertz,
//    1.414213623 * hertz,
//    2.0 * hertz,
//    2.828427246 * hertz,
//    4 * hertz,
//
//    5.656854492 * hertz,
//    8 * hertz,
//    11.31370898 * hertz,
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
    512 * hertz,

    724.077375 * hertz,
    1024 * hertz,

    1448.15475 * hertz,
    2048 * hertz,

    2896.3095 * hertz,
    4096 * hertz,
    5792.619 * hertz,
//    8192 * hertz,
//    11585.238 * hertz

  });
  

  auto const experimental_phases = vector< quantity< plane_angle > >( {
//   * radians, //  .088  Hz
//   * radians, //  .125  Hz
//   * radians, //  .177  Hz
//  1.022 * radians, //  .250    Hz
//  0.981 * radians, // .354  Hz
//  .974 * radians, //  .500 Hz
//  1.012 * radians, //  .707 Hz
//    
//  1.060 * radians, //  1  Hz
//  1.114 * radians, //  1.414  Hz
//  1.158 * radians, //  2.0  Hz
//  1.193 * radians, //  2.828    Hz
//  1.206 * radians, // 4.0  Hz
//  1.195 * radians, //  5.657 Hz

//  1.156 * radians, //  8     Hz
//  1.092 * radians, //  11.314  Hz
  .999 * radians, //  16.0    Hz
  .900 * radians, //  22.627  Hz
  .809 * radians, //  32.0    Hz

  .755 * radians, //  45.255  Hz
  .727 * radians, //  64.0    Hz
  .733 * radians, //  90.510  Hz

  .755 * radians,  // 128      Hz
  .759 * radians,   // 181.019  Hz
  .758 * radians, // 256      Hz

  .755 * radians, // 362.039  Hz
  .752 * radians, // 512      Hz

  .747 * radians,  // 724.077
  .744 * radians,  // 1024
  .743 * radians,  // 1448 Hz
  .746 * radians,  //  2048 Hz
  .751 * radians, // 2896.3  Hz

  .762 * radians, // 4096      Hz
  .792 * radians,  // 5792.6
//  0.868 * radians,  // 8192
//  0.902 * radians,  // 11585 Hz
    } );
  
  // predicted steady state = 490.881 K
  //  T_steady_state = 218 deg C.
  
  auto const L = quantity< length > ( .984 * millimeters  );
  auto const diffusivity = quantity<thermal_diffusivity>( 100 * square_millimeters / second);
  auto const conductivity_dummey =
    quantity< thermal_conductivity >( 200 * watts / meter / si::kelvin );
  

  auto const initial_slab =
  thermal::model::slab::Slab( L, diffusivity, conductivity_dummey );
  auto const beam_radius = quantity< length >( 4.4 * millimeters );

  auto const specimen =
  Slab( initial_slab, frequencies, experimental_phases, beam_radius );
  
  return specimen;
};



} // namespace sept28
} // namespace poco_edm3
} // namesapce adiabatic_rear
} // namespace beamExpander
} // namespace bulkDiffusivityMeasurements2015
} // namespace investigations


#endif /* A1_rear_100degC_h */
