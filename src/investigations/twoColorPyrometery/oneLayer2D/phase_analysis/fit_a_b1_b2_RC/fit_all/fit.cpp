//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 9/1/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit.hpp"

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

namespace slab = thermal::model::slab;
namespace estimate_parameters =
  thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_a_b1_b2_RC;


auto fit( filesystem::directory const & dir ) -> void
{
  auto initial_slab = slab::import( dir, "initial_slab.xml" ) ;

  auto const frequencies = vector< quantity< frequency > >({
//    1.0 * hertz,
//    1.414 * hertz,
//    2.0 * hertz,
//    2.828 * hertz,
//    4 * hertz,
//
//    5.657 * hertz,
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
    
    1448.155 * hertz,
    2048 * hertz,

    2896.3 * hertz,
    4096 * hertz,
    5792.6 * hertz,
    8192 * hertz,
  11585. * hertz

  });
  
  
//T = 58 deg C
// Sample C
auto const L = quantity< length > ( 1.614 * millimeters  );// sample F
auto const experimental_phases = vector< quantity< plane_angle > >( {

//0.638 * radians, //  1 Hz
//0.645 * radians, //  1.414     Hz
//0.647 * radians, //  2  Hz
//0.632 * radians, //  2.828    Hz
//0.626 * radians, //  4  Hz

//0.607 * radians, //  5.657 Hz
//0.603 * radians, //  8     Hz
0.613 * radians, //  11.314  Hz
0.633 * radians, //  16.0    Hz
0.664 * radians, //  22.627  Hz
0.696 * radians, //  32.0    Hz

0.718 * radians, //  45.255  Hz
0.736 * radians, //  64.0    Hz
0.749 * radians, //  90.510  Hz

0.760 * radians,  // 128      Hz
0.768 * radians,   // 181.019  Hz
0.774 * radians, // 256      Hz

0.778 * radians, // 362.039  Hz
0.782 * radians, // 512      Hz

0.785 * radians,  // 724.077
0.790 * radians,  // 1024
0.794 * radians,  // 1448 Hz
0.802 * radians,  //  2048 Hz
0.78539816339 * radians, // 2896.3  Hz

0.78539816339 * radians, // 4096      Hz
0.78539816339 * radians,  // 5792.6
0.78539816339 * radians,  // 8192
0.78539816339 * radians,  // 11585 Hz
  } );
  
  auto const beam_radius = quantity< length >( 2.2 * millimeters );
  auto const detector_radius = quantity< length>( .25 * millimeters  ) ;
  auto const diffusivity = quantity<thermal_diffusivity>( 50 * square_millimeters / second);
  
  initial_slab.characteristic_length = L;
  initial_slab.set_diffusivity_update_k_hold_rhoCp( diffusivity );


  auto const bestFit_results = estimate_parameters::fit_all::fit(
    frequencies, experimental_phases,
    initial_slab, beam_radius, detector_radius ) ;
  
  bestFit_results.plot_model_phases_against( experimental_phases );
}

} // namespace fit_all
} // namespace fit_a_b1_b2_RC
} // namespace phase_analysis
} // namespace oneLayer2D
} // namespace twoColorPyrometery
} // namespace investigations

