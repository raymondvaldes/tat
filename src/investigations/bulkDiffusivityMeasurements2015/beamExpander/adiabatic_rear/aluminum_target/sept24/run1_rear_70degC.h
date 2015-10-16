//
//  run1_rear_70degC.h
//  tat
//
//  Created by Raymond Valdes on 9/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef run1_rear_70degC_h
#define run1_rear_70degC_h

#include "thermal/model/slab/slab.h"
#include <vector>
#include "units.h"
#include "thermal/experimental/observations/slab/slab.hpp"

namespace investigations{
namespace bulkDiffusivityMeasurements2015{
namespace beamExpander{
namespace adiabatic_rear{
namespace aluminum_target{
namespace sept24{

inline auto run1_rear_70degC( void )
noexcept -> thermal::experimental::observations::Slab
{
  using std::vector;
  using namespace units;
  using thermal::experimental::observations::Slab;

  auto const frequencies = vector< quantity< frequency > >({
    .088 * hertz,
    .125 * hertz,
    .177 * hertz,
    .250 * hertz,
    .354 * hertz,
    .500 * hertz,
    .707 * hertz,

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
    512 * hertz,

    724.077375 * hertz,
    1024 * hertz,

    1448.15475 * hertz,
    2048 * hertz,

    2896.3095 * hertz,
    4096 * hertz,
    5792.619 * hertz,
    8192 * hertz,
    11585.238 * hertz

  });
  

  auto const experimental_phases = vector< quantity< plane_angle > >( {
  .322 * radians, //  .088  Hz
  .273 * radians, //  .125  Hz
  .238 * radians, //  .177  Hz
  .222 * radians, //  .250    Hz
  .211 * radians, // .354  Hz
  .202 * radians, //  .500 Hz
  .191 * radians, //  .707 Hz
    
  .175 * radians, //  1  Hz
  .155 * radians, //  1.414  Hz
  .136 * radians, //  2.0  Hz
  .122 * radians, //  2.828    Hz
  .112 * radians, // 4.0  Hz
  .110 * radians, //  5.657 Hz

  .115 * radians, //  8     Hz
  .125 * radians, //  11.314  Hz
  .139 * radians, //  16.0    Hz
  .160 * radians, //  22.627  Hz
  .188 * radians, //  32.0    Hz

  .227 * radians, //  45.255  Hz
  .278 * radians, //  64.0    Hz
  .340 * radians, //  90.510  Hz

  .416 * radians,  // 128      Hz
  .505 * radians,   // 181.019  Hz
  .602 * radians, // 256      Hz

  .701 * radians, // 362.039  Hz
  .790 * radians, // 512      Hz

  .863 * radians,  // 724.077
  .915 * radians,  // 1024
  .947 * radians,  // 1448 Hz
  .967 * radians,  //  2048 Hz
  .980 * radians, // 2896.3  Hz

  .994 * radians, // 4096      Hz
  1.016 * radians,  // 5792.6
  1.050 * radians,  // 8192
  1.103 * radians,  // 11585 Hz
    } );
  
  auto const L = quantity< length > ( 3.175 * millimeters  );
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



} // namespace sept24
} // namespace aluminum_target
} // namesapce adiabatic_rear
} // namespace beamExpander
} // namespace bulkDiffusivityMeasurements2015
} // namespace investigations


#endif /* run1_rear_70degC_h */
