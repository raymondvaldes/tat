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
//    2 * hertz,
//    2.828 * hertz,
//    4 * hertz,
//    5.657 * hertz,
//
//    8 * hertz,
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
    724.077 * hertz,
    1024 * hertz,

//    1448.155 * hertz,
//    2048 * hertz
  });


//// Sample D
auto const L = quantity< length > ( 10.13 * millimeters  ); //sample D
auto const experimental_phases = vector< quantity< plane_angle > >( {

//0.638 * radians, //  1 Hz
//0.645 * radians, //  1.414     Hz
//0.647 * radians, //  2  Hz
//0.632 * radians, //  2.828    Hz
//0.626 * radians, //  4  Hz

//0.607 * radians, //  5.657 Hz
//0.603 * radians, //  8     Hz
0.611 * radians, //  11.314  Hz
0.641 * radians, //  16.0    Hz
0.669 * radians, //  22.627  Hz
0.693 * radians, //  32.0    Hz

0.714 * radians, //  45.255  Hz
0.728 * radians, //  64.0    Hz
0.744 * radians, //  90.510  Hz

0.755 * radians,  // 128      Hz
0.761 * radians,   // 181.019  Hz
0.767 * radians, // 256      Hz

0.770 * radians, // 362.039  Hz
0.773 * radians, // 512      Hz

0.774 * radians,  // 724.077
0.778 * radians,  // 1024
//0.782 * radians,  // 1448 Hz
//0.789 * radians,  //  2048 Hz
//0.800 * radians, // 2896.3  Hz
//
//0.816 * radians, // 4096      Hz
//.842 * radians,  // 5792.6
//.877 * radians,  // 8192
//0.928 * radians,  // 11585 Hz
  } );

  
  initial_slab.characteristic_length = L ;

  auto const beam_radius = quantity< length >( 2.0 * millimeters );
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
