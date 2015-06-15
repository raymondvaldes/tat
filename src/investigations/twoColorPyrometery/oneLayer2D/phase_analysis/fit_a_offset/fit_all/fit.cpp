//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 6/3/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_a_offset/fit_all/fit.h"

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_diffusivity_offset/fit_all/fit.h"

#include "thermal/model/slab/import_slab.h"
#include "units.h"

using namespace units;
using std::vector;
using thermal::model::slab::import ;
using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_diffusivity_offset::fit_all::fit;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace phase_analysis{
namespace fit_a_offset{
namespace fit_all{

auto fit( filesystem::directory const & dir ) -> void
{
 auto slab_initial = thermal::model::slab::import( dir, "initial_slab.xml" ) ;
  
  auto const frequencies = vector< quantity< frequency > >({
//    1.414 * hertz,
//    2 * hertz,
//    2.828 * hertz,
    4 * hertz,
    5.657 * hertz,
    8 * hertz,
    11.314 * hertz,
    16 * hertz,
    22.627 * hertz,
    32 * hertz,
    
//    45.255 * hertz,
//    64 * hertz,
//    90.51 * hertz,

//    128 * hertz,
//    181.019 * hertz,
//    256 * hertz,
//    362.039 * hertz,
//    
//    512 * hertz,
//    724.077 * hertz,
//    1024 * hertz,
//    1448.155 * hertz,
//    2048 * hertz
  });

////  //may 22
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

////  june2
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//.634 * radians, // 1.414 Hz
//.681 * radians, // 2.0 Hz
//.734 * radians, //  2.828 Hz
//.786 * radians, //  4.0   Hz
//.836 * radians, //  5.657 Hz
//
//.883 * radians, //  8     Hz
//.906 * radians, //  11.314  Hz
//.934 * radians, //  16.0    Hz
//.936 * radians, //  22.627  Hz
//.901 * radians, //  32.0    Hz
//
//.871 * radians, //  45.255  Hz
//.795 * radians, //  64.0    Hz
//.743 * radians, //  90.510  Hz
//
//.713 * radians,  // 128      Hz
//.702 * radians,   // 181.019  Hz
//.713 * radians, // 256      Hz
//.728 * radians, // 362.039  Hz
//.737 * radians, // 512      Hz
//.738 * radians,  //
//.739 * radians,  //
//.744 * radians,  //
//.752 * radians  //  2000 Hz
//  } );
  
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//.757 * radians, // 1.414 Hz
//.812 * radians, // 2.0 Hz
//.862 * radians, //  2.828 Hz
//.904 * radians, //  4.0   Hz
//.937 * radians, //  5.657 Hz
//
//.968 * radians, //  8     Hz
//.974 * radians, //  11.314  Hz
//.966 * radians, //  16.0    Hz
//.949 *  radians, //  22.627  Hz
//.895 * radians, //  32.0    Hz
//
//.831 * radians, //  45.255  Hz
//.763 * radians, //  64.0    Hz
//.714 * radians, //  90.510  Hz
//
////.710 * radians,  // 128      Hz
////.729 * radians,   // 181.019  Hz
////.742 * radians, // 256      Hz
////.747 * radians, // 362.039  Hz
////.750 * radians, // 512      Hz
////.755 * radians,  //
////.756 * radians,  //
////.758 * radians,  //
////.765 * radians  //  2000 Hz
//  } );
  
  //T=168 F (no filter)
  auto const experimental_phases = vector< quantity< plane_angle > >( {
//.746 * radians, // 1.414 Hz
//.800 * radians, // 2.0 Hz
//.854 * radians, //  2.828 Hz
.884 * radians, //  4.0   Hz
.920 * radians, //  5.657 Hz

.953 * radians, //  8     Hz
.972 * radians, //  11.314  Hz
.970 * radians, //  16.0    Hz
.953 * radians, //  22.627  Hz
.917 * radians, //  32.0    Hz

//.863 * radians, //  45.255  Hz
//.795 * radians, //  64.0    Hz
//.731 * radians, //  90.510  Hz

//.691 * radians,  // 128      Hz
//.673 * radians,   // 181.019  Hz
//.678 * radians, // 256      Hz
//
//.689 * radians, // 362.039  Hz
//.692 * radians, // 512      Hz
//.687 * radians,  // 724.077
//.677 * radians,  // 1024
//.675 * radians,  // 1448 Hz
//.672 * radians  //  2048 Hz
  } );
  
  slab_initial.characteristic_length = quantity< si::length >(.65 * millimeters);

  auto const beam_radius = quantity< length >( 1.54 * millimeters );
  auto const detector_offset = quantity< length >( .3 * millimeters  ) ; // initial value

  auto const bestFit_results = thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_diffusivity_offset::fit_all::fit(
    frequencies, experimental_phases , slab_initial, beam_radius,
    detector_offset ) ;
  
  bestFit_results.plot_model_phases_against( experimental_phases );

}

} // namespace fit_all
} // namespace fit_a_offset
} // namespace phase_analysis
} // namespace oneLayer2D
} // namespace twoColorPyrometery
} // namespace investigations
