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
  auto initial_slab = thermal::model::slab::import( dir, "initial_slab.xml" ) ;
  
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

  
////  //may 22
//auto const L = quantity< length > ( 0.661 * millimeters  );// sample E
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//0.673 * radians, // 1.414 Hz
//0.733 * radians, // 2.0 Hz
//0.791 * radians, //  2.828 Hz
//0.846 * radians, //  4.0   Hz
//0.897 * radians, //  5.657 Hz
//
//0.944 * radians, //  8     Hz
//0.970 * radians, //  11.314  Hz
//0.984 * radians, //  16.0    Hz
//0.968 * radians, //  22.627  Hz
//0.934 * radians, //  32.0    Hz
//
//0.874 * radians, //  45.255  Hz
//0.797 * radians, //  64.0    Hz
//0.739 * radians, //  90.510  Hz
//
//0.688 * radians,  // 128      Hz
//0.674 * radians,   // 181.019  Hz
//0.682 * radians, // 256      Hz
//0.692 * radians, // 362.039  Hz
//0.695 * radians, // 512      Hz
//0.691 * radians,  //
//0.687 * radians,  //
//0.682 * radians,  //
//0.680 * radians  //  2000 Hz
//  } );


auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
auto const experimental_phases = vector< quantity< plane_angle > >( {

.895 * radians, //  2.0  Hz
.937 * radians, //  2.828    Hz
.977 * radians, // 4.0  Hz
1.001 * radians, //  5.657 Hz

1.008 * radians, //  8     Hz
.994 * radians, //  11.314  Hz
.955 * radians, //  16.0    Hz
.889 * radians, //  22.627  Hz
.824 * radians, //  32.0    Hz

.771 * radians, //  45.255  Hz
.738 * radians, //  64.0    Hz
.736 * radians, //  90.510  Hz

//(.756 - .00133) * radians,  // 128      Hz
//(.772 - .0024) * radians,   // 181.019  Hz
//(.779 - .0026) * radians, // 256      Hz
//
//(.782 - .0036) * radians, // 362.039  Hz
//(.783 - .0051) * radians, // 512      Hz
//
//(0.785 - .0073) * radians,  // 724.077
//(0.788 - .0103) * radians,  // 1024
//
//(.792) * radians,  // 1448 Hz
//(.798) * radians  //  2048 Hz
  } );


  auto const beam_radius = quantity< length >( 2.0 * millimeters );
  auto const detector_view_radius = quantity< length>( 0.1 * millimeters  ) ;
  auto const alpha = quantity<thermal_diffusivity>( 50 * square_millimeters / second);
  
  initial_slab.set_thickness(L);
  initial_slab.set_diffusivity_update_k_hold_rhoCp( alpha );


  

  diffusivity_from_phases(
    frequencies, experimental_phases , initial_slab, beam_radius, detector_view_radius ) ;
  
//  bestFit_results.plot_model_phases_against( experimental_phases );
  
}

} // namespace
} // namespace
} // namespace
} // namespace
} // namespace
