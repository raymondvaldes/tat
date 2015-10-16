//
//  B1_rear_179degC.h
//  tat
//
//  Created by Raymond Valdes on 9/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef B1_rear_179degC_h
#define B1_rear_179degC_h

// T_rear = 190 deg C
// V_4.1 = 3.0687
// V_4.1_block = 2.3441
// V_4.1_cal = .7246

// V_5.2_ = 4.4040
// V_5.2_block =  3.0301
// V_5.2_cal = 1.3739

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

inline auto B1_rear_179degC( void )
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
//  1.214 * radians, //  .088  Hz
//  1.155 * radians, //  .125  Hz
//  1.089 * radians, //  .177  Hz
//  1.022 * radians, //  .250    Hz
//  0.981 * radians, // .354  Hz
//  0.974 * radians, //  .500 Hz
  .997 * radians, //  .707 Hz
    
  1.027 * radians, //  1  Hz
  1.046 * radians, //  1.414  Hz
  1.040 * radians, //  2.0  Hz
  1.007* radians, //  2.828    Hz
  .946 * radians, // 4.0  Hz
  .873 * radians, //  5.657 Hz

  .802 * radians, //  8     Hz
  .756 * radians, //  11.314  Hz
  0.737 * radians, //  16.0    Hz
  0.744 * radians, //  22.627  Hz
  0.758 * radians, //  32.0    Hz

  0.770 * radians, //  45.255  Hz
  0.772 * radians, //  64.0    Hz
  0.777 * radians, //  90.510  Hz

  0.783 * radians,  // 128      Hz
  0.783 * radians,   // 181.019  Hz
  0.784 * radians, // 256      Hz

  0.785 * radians, // 362.039  Hz
  0.784 * radians, // 512      Hz

  0.789 * radians,  // 724.077
  0.786 * radians,  // 1024
  0.789 * radians,  // 1448 Hz
  0.790 * radians,  //  2048 Hz
  0.796 * radians, // 2896.3  Hz

  0.808 * radians, // 4096      Hz
  0.827 * radians,  // 5792.6
  0.853 * radians,  // 8192
  .891 * radians,  // 11585 Hz
    } );
  

  
  auto const L = quantity< length > ( 1.787 * millimeters  );
  auto const diffusivity = quantity<thermal_diffusivity>( 100 * square_millimeters / second);
  auto const conductivity_dummey =
    quantity< thermal_conductivity >( 200 * watts / meter / si::kelvin );
  

  auto const initial_slab =
  thermal::model::slab::Slab( L, diffusivity, conductivity_dummey );
  auto const beam_radius = quantity< length >( 5.5 * millimeters );

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

#endif /* B1_rear_179degC_h */
