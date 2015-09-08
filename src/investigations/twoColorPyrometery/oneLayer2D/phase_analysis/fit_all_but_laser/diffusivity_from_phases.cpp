//
//  diffusivity_from_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_laser/diffusivity_from_phases.h"
#include "units.h"
#include "thermal/pyrometry/twoColor/calibrate_wavelength.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_laser/diffusivity_from_phases.h"
#include "thermal/model/slab/import_slab.h"

using namespace units;
using thermal::model::slab::import ;
using std::vector;
using thermal::pyrometry::twoColor::calibrate_wavelength;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace phase_analysis{
namespace fit_all_but_laser{

using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_all_but_laser::diffusivity_from_phases;


auto diffusivity_from_phases( filesystem::directory const & dir ) -> void
{
  auto initial_slab = thermal::model::slab::import( dir, "initial_slab.xml" ) ;
  
  auto const frequencies = vector< quantity< frequency > >({

//    1.414 * hertz,
    2 * hertz,
    2.828 * hertz,
    4 * hertz,
    5.657 * hertz,

    8 * hertz,
    11.314 * hertz,
    16 * hertz,
    22.627 * hertz,
    32 * hertz,
    
    45.255 * hertz,
    64 * hertz,
    90.51 * hertz,
    128 * hertz,
    181.019 * hertz,
    256 * hertz,
    362.039 * hertz,
    512 * hertz,
//    724.077 * hertz,
//    1024 * hertz,

//    1448.155 * hertz,
//    2048 * hertz
  });

//T = 78 deg C
// Sample F
auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
auto const experimental_phases = vector< quantity< plane_angle > >( {

//1.138 * radians, //  1  Hz
//1.186 * radians, //  1.414  Hz
1.222 * radians, //  2.0  Hz
1.251 * radians, //  2.828    Hz
1.262 * radians, // 4.0  Hz
1.254 * radians, //  5.657 Hz

1.221 * radians, //  8     Hz
1.166 * radians, //  11.314  Hz
1.078 * radians, //  16.0    Hz
0.974 * radians, //  22.627  Hz
0.873 * radians, //  32.0    Hz

0.796 * radians, //  45.255  Hz
0.756 * radians, //  64.0    Hz
0.750 * radians, //  90.510  Hz

0.770 * radians,  // 128      Hz
0.783 * radians,   // 181.019  Hz
0.787 * radians, // 256      Hz

0.786 * radians, // 362.039  Hz
0.787 * radians, // 512      Hz

//0.787 * radians,  // 724.077
//0.789 * radians,  // 1024
//0.796 * radians,  // 1448 Hz
//0.801 * radians,  //  2048 Hz
//0.811 * radians, // 2896.3  Hz
//
//0.825 * radians, // 4096      Hz
//0.847 * radians,  // 5792.6
//0.873 * radians,  // 8192
//0.912 * radians,  // 11585 Hz
  } );

  
  initial_slab.characteristic_length = L ;

  auto const beam_radius = quantity< length >( 4.4 * millimeters );
  auto const detector_view_radius = quantity< length>( 0.15 * millimeters  ) ; // initial value

  auto const bestFit_results = diffusivity_from_phases(
    frequencies, experimental_phases , initial_slab, beam_radius, detector_view_radius
    ) ;
  
  bestFit_results.plot_model_phases_against( experimental_phases );

}

} // namespace
} // namespace
} // namespace
} // namespace
} // namespace
