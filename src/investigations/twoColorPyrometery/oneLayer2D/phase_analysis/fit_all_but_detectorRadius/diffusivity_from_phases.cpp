//
//  diffusivity_from_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 5/7/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_detectorRadius/diffusivity_from_phases.h"
#include "units.h"
#include "thermal/pyrometry/twoColor/calibrate_wavelength.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_detectorRadius/diffusivity_from_phases.h"
#include "thermal/model/slab/import_slab.h"

using namespace units;
using thermal::model::slab::import ;
using std::vector;
using thermal::pyrometry::twoColor::calibrate_wavelength;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace phase_analysis{
namespace fit_all_but_detectorRadius{

using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_all_but_detectorRadius::diffusivity_from_phases;

auto diffusivity_from_phases( filesystem::directory const & dir ) -> void
{
  auto const initial_slab = thermal::model::slab::import( dir, "initial_slab.xml" ) ;
  
  auto const frequencies = vector< quantity< frequency > >({
    1.414 * hertz,
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
    724.077 * hertz,
    1024 * hertz,
    1448.155 * hertz,
    2048 * hertz
  });
////poco_adiabatic_may12_25mm_no_monochrometer_5_5_190_wav
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//1.186* radians,
//1.234* radians,
//1.252* radians,
//1.279* radians,
//1.257* radians,
//1.231* radians,
//1.178* radians,
//1.113* radians,
//1.003* radians,
//0.877 * radians,
//
//    0.784 * radians,
//    0.710 * radians,
//    0.687 * radians,
//    0.758 * radians,
//    
//    0.769 * radians,
//    0.781 * radians,
//    0.783 * radians,
//    0.778 * radians,
//    0.772 * radians,
//    0.766 * radians,
//    0.759 * radians,
//    0.747 * radians
//  } );
  
//  //may 22
  auto const experimental_phases = vector< quantity< plane_angle > >( {
0.673 * radians, // 1.414 Hz
0.733 * radians, // 2.0 Hz
0.791 * radians, //  2.828 Hz
0.846 * radians, //  4.0   Hz
0.897 * radians, //  5.657 Hz

0.944 * radians, //  8     Hz
0.970 * radians, //  11.314  Hz
0.984 * radians, //  16.0    Hz
0.968 * radians, //  22.627  Hz
0.934 * radians, //  32.0    Hz

0.874 * radians, //  45.255  Hz
0.797 * radians, //  64.0    Hz
0.739 * radians, //  90.510  Hz

0.688 * radians,  // 128      Hz
0.674 * radians,   // 181.019  Hz
0.682 * radians, // 256      Hz
0.692 * radians, // 362.039  Hz
0.695 * radians, // 512      Hz
0.691 * radians,  //
0.687 * radians,  //
0.682 * radians,  //
0.680 * radians  //  2000 Hz
  } );

//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//  0.9879 * radians,
//1.0455 * radians,
//1.085 * radians,
//1.1055 * radians,
//1.1105 * radians,
//1.106 * radians,
//1.064 * radians,
//1.0025 * radians,
//0.912 * radians,
//0.808 * radians,
////    0.7405715 * radians,
////    0.668 * radians,
////    0.6465 * radians,
////    0.65 * radians,
////    0.6495 * radians,
////    0.639 * radians,
////    0.623 * radians,
////    0.5975 * radians,
////    0.5755 * radians,
////    0.549 * radians,
////    0.525 * radians,
////    0.491 * radians
//  } );
  
  auto const beam_radius = quantity< length >( 1.54 * millimeters );
  auto const detector_view_radius = quantity< length>( .1 * millimeters  ) ; // initial value

  auto const bestFit_results = diffusivity_from_phases(
    frequencies, experimental_phases , initial_slab, beam_radius, detector_view_radius ) ;
  
  bestFit_results.plot_model_phases_against( experimental_phases );
  
}

} // namespace
} // namespace
} // namespace
} // namespace
} // namespace
