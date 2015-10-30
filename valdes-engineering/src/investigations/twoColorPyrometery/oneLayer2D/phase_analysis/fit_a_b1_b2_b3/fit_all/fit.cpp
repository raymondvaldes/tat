//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 8/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit.hpp"


#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all/diffusivity_from_phases.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_diffusivity_offset_view_radius_beam/fit_all/fit.hpp"
#include "thermal/model/oneLayer2D/model_selection.h"

#include "thermal/model/slab/import_slab.h"
#include "units.h"

using namespace units;
using std::vector;
using thermal::model::slab::import ;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace phase_analysis{
namespace fit_a_b1_b2_b3{
namespace fit_all{

using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_all::fit;
using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_diffusivity_offset_view_radius_beam::fit_all::fit;


auto fit( filesystem::directory const & dir ) -> void
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
1.186 * radians, //  1.414  Hz
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


////// Sample D
//auto const L = quantity< length > ( 10.13 * millimeters  ); //sample D
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
//0.611 * radians, //  11.314  Hz
//0.641 * radians, //  16.0    Hz
//0.669 * radians, //  22.627  Hz
//0.693 * radians, //  32.0    Hz
//
//0.714 * radians, //  45.255  Hz
//0.728 * radians, //  64.0    Hz
//0.744 * radians, //  90.510  Hz
//
//0.755 * radians,  // 128      Hz
//0.761 * radians,   // 181.019  Hz
//0.767 * radians, // 256      Hz
//
//0.770 * radians, // 362.039  Hz
//0.773 * radians, // 512      Hz
//
//0.774 * radians,  // 724.077
//0.778 * radians,  // 1024
////0.782 * radians,  // 1448 Hz
////0.789 * radians,  //  2048 Hz
////0.800 * radians, // 2896.3  Hz
////
////0.816 * radians, // 4096      Hz
////.842 * radians,  // 5792.6
////.877 * radians,  // 8192
////0.928 * radians,  // 11585 Hz
//  } );

////T = 58 deg C
//// Sample F
//auto const L = quantity< length > ( 1.2 * millimeters  );// sample F
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
//0.821 * radians, //  5.657 Hz
//0.794 * radians, //  8     Hz
//0.757 * radians, //  11.314  Hz
//0.722 * radians, //  16.0    Hz
//0.700 * radians, //  22.627  Hz
//0.698 * radians, //  32.0    Hz
//
//0.716 * radians, //  45.255  Hz
//0.739 * radians, //  64.0    Hz
//0.756 * radians, //  90.510  Hz
//
//0.771 * radians,  // 128      Hz
//0.775 * radians,   // 181.019  Hz
//0.779 * radians, // 256      Hz
//
//0.782 * radians, // 362.039  Hz
//0.784 * radians, // 512      Hz
//
//0.787 * radians,  // 724.077
//0.791 * radians,  // 1024
//
////0.775 * radians,  // 1448 Hz
////0.775 * radians  //  2048 Hz
//  } );
  
//////T = 58 deg C
//// day two without aperture
//// Sample E
//auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////.895 * radians, //  2.0  Hz
//.937 * radians, //  2.828    Hz
//.977 * radians, // 4.0  Hz
//1.001 * radians, //  5.657 Hz
//
//1.008 * radians, //  8     Hz
//.994 * radians, //  11.314  Hz
//.955 * radians, //  16.0    Hz
//.889 * radians, //  22.627  Hz
//.824 * radians, //  32.0    Hz
//
//.771 * radians, //  45.255  Hz
//.738 * radians, //  64.0    Hz
//.736 * radians, //  90.510  Hz
//
//(.756 - .00133) * radians,  // 128      Hz
//(.772 - .0024) * radians,   // 181.019  Hz
//(.779 - .0026) * radians, // 256      Hz
////
////(.782 - .0036) * radians, // 362.039  Hz
////(.783 - .0051) * radians, // 512      Hz
////
////(0.785 - .0073) * radians,  // 724.077
////(0.788 - .0103) * radians,  // 1024
////
////.792 * radians,  // 1448 Hz
////.798 * radians  //  2048 Hz
//  } );


  auto const beam_radius = quantity< length >( 4.4 * millimeters );
  auto const detector_view_radius = quantity< length>( 0.15 * millimeters  ) ;
  auto const alpha = quantity< thermal_diffusivity >( 35 * square_millimeters / second);
  
  initial_slab.set_thickness(L);
  initial_slab.set_diffusivity_update_k_hold_rhoCp( alpha );


  auto const detector_view_offset = quantity< length >( 0.10 * millimeters  ) ;


  fit(
    frequencies, experimental_phases , initial_slab, beam_radius, detector_view_radius, detector_view_offset ) ;
  
//  bestFit_results.plot_model_phases_against( experimental_phases );
  
}

} // namespace fit_all
} // namespace fit_a_b1_b2_b3
} // namespace phase_analysis
} // namespace oneLayer2D
} // namespace twoColorPyrometery
} // namespace investigations
