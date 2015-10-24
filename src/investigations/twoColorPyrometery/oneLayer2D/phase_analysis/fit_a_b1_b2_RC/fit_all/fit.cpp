//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 9/1/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit.hpp"
#include <iostream>

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_a_b1_b2_RC/fit_all/fit.hpp"
#include "thermal/pyrometry/twoColor/calibrate_wavelength.h"
#include "thermal/model/slab/import_slab.h"
#include "units.h"

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace phase_analysis{
namespace fit_a_b1_b2_RC{
namespace fit_all{

using namespace units;
using std::vector;
using std::cout;

namespace slab = thermal::model::slab;
namespace estimate_parameters =
  thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_a_b1_b2_RC;


auto fit( filesystem::directory const & dir ) -> void
{

  auto initial_slab = slab::import( dir, "initial_slab.xml" ) ;

  auto const frequencies = vector< quantity< frequency > >({
//    1.0 * hertz,
//    1.414213623 * hertz,
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

0.787 * radians,  // 724.077
0.789 * radians,  // 1024
0.796 * radians,  // 1448 Hz
0.801 * radians,  //  2048 Hz
0.811 * radians, // 2896.3  Hz

0.825 * radians, // 4096      Hz
0.847 * radians,  // 5792.6
0.873 * radians,  // 8192
0.912 * radians,  // 11585 Hz
  } );

////T = 58 deg C
//// Sample F
//auto const L = quantity< length > ( 1.2 * millimeters  );// sample F
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////.670 * radians, //  1  Hz
////.700 * radians, //  1.414  Hz
////.726 * radians, //  2.0  Hz
////.730 * radians, //  2.828    Hz
////.736 * radians, // 4.0  Hz
////.719 * radians, //  5.657 Hz
////
////0.706 * radians, //  8     Hz
//0.687 * radians, //  11.314  Hz
//0.665 * radians, //  16.0    Hz
//0.663 * radians, //  22.627  Hz
//0.674 * radians, //  32.0    Hz
//
//0.698 * radians, //  45.255  Hz
//0.725 * radians, //  64.0    Hz
//0.741 * radians, //  90.510  Hz
//
//0.758 * radians,  // 128      Hz
//0.765 * radians,   // 181.019  Hz
//0.770 * radians, // 256      Hz
//
//0.774 * radians, // 362.039  Hz
//.776 * radians, // 512      Hz
//
////0.787 * radians,  // 724.077
////.791 * radians,  // 1024
////0.78539816339 * radians,  // 1448 Hz
////0.78539816339 * radians,  //  2048 Hz
////0.78539816339 * radians, // 2896.3  Hz
////
////0.78539816339 * radians, // 4096      Hz
////0.78539816339 * radians,  // 5792.6
////0.78539816339 * radians,  // 8192
////0.78539816339 * radians,  // 11585 Hz
//  } );

  
////T = 58 deg C
//// Sample C
//auto const L = quantity< length > ( 1.614 * millimeters  );// sample F
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////0.638 * radians, //  1 Hz
////0.645 * radians, //  1.414     Hz
////0.647 * radians, //  2  Hz
////0.632 * radians, //  2.828    Hz
////0.626 * radians, //  4  Hz
//
////0.607 * radians, //  5.657 Hz
////0.603 * radians, //  8     Hz
//0.613 * radians, //  11.314  Hz
//0.633 * radians, //  16.0    Hz
//0.664 * radians, //  22.627  Hz
//0.696 * radians, //  32.0    Hz
//
//0.718 * radians, //  45.255  Hz
//0.736 * radians, //  64.0    Hz
//0.749 * radians, //  90.510  Hz
//
//0.760 * radians,  // 128      Hz
//0.768 * radians,   // 181.019  Hz
//0.774 * radians, // 256      Hz
//
//0.778 * radians, // 362.039  Hz
//0.782 * radians, // 512      Hz
//
//0.785 * radians,  // 724.077
//0.790 * radians,  // 1024
//0.794 * radians,  // 1448 Hz
//0.802 * radians,  //  2048 Hz
//0.812 * radians, // 2896.3  Hz
//
//0.826 * radians, // 4096      Hz
//0.848 * radians,  // 5792.6
//0.878 * radians,  // 8192
//0.921 * radians,  // 11585 Hz
//  } );
  
  auto const beam_radius = quantity< length >( 4.0 * millimeters );
  auto const detector_radius = quantity< length>( .25 * millimeters  ) ;
  auto const diffusivity = quantity<thermal_diffusivity>( 50 * square_millimeters / second);
  
  initial_slab.set_thickness(L) ;
  initial_slab.set_diffusivity_update_k_hold_rhoCp( diffusivity );


  auto const bestFit_results = estimate_parameters::fit_all::fit(
    frequencies, experimental_phases,
    initial_slab, beam_radius, detector_radius ) ;
  
  bestFit_results.plot_model_phases_against_observations();
}

} // namespace fit_all
} // namespace fit_a_b1_b2_RC
} // namespace phase_analysis
} // namespace oneLayer2D
} // namespace twoColorPyrometery
} // namespace investigations

