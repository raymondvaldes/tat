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
  initial_slab.characteristic_length = quantity< si::length >(0.651 * millimeters);
  
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

//////poco_adiabatic_may12_25mm_no_monochrometer_5r_wav
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//0.881* radians,
//0.957* radians,
//1.023* radians,
//1.079* radians,
//1.130* radians,
//
//1.163* radians,
//1.183* radians,
//1.173* radians,
//1.139* radians,
//1.078 * radians,
//
//    0.992 * radians,
//    0.891 * radians,
//    0.805 * radians,
//    0.751 * radians,
//    0.727 * radians,
//    
//    0.730 * radians,
//    0.739 * radians,
//    0.746 * radians,
//    0.746 * radians,
//    0.746 * radians,
//    0.742 * radians,
//    0.705 * radians
//  } );

//////////poco_adiabatic_may12_25mm_no_monochrometer_5r_wav (corrected bias)
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//(0.881+ .036)* radians,
//(0.957+ .036)* radians,
//(1.023+ .036)* radians,
//(1.079+ .036)* radians,
//(1.130+ .036)* radians,
//
//(1.163+ .036)* radians,
//(1.183+ .036)* radians,
//(1.173+ .036)* radians,
//(1.139+ .036)* radians,
//(1.078+ .036) * radians,
//
//   ( 0.992+ .036) * radians,
//   ( 0.891+ .036) * radians,
//   ( 0.805+ .036) * radians,
//    
//    (0.751 + .036)* radians,
//    (0.727+ .036) * radians,
//    (0.730+ .036) * radians,
//    (0.739+ .036) * radians,
//    (0.746+ .036) * radians,
//    (0.746+ .036) * radians,
//    (0.746+ .036) * radians,
//    (0.742+ .036) * radians,
//    (0.705+ .036) * radians
//  } );

//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//0.881* radians,
//0.957* radians,
//1.023* radians,
//1.079* radians,
//1.130* radians,
//
//1.163* radians,
//1.183* radians,
//1.173* radians,
//1.139* radians,
//1.078 * radians,
//
//    0.992 * radians,
//    0.891 * radians,
//    0.805 * radians,
//    
//    (0.751)* radians,
//    (0.727) * radians,
//    (0.730) * radians,
//    (0.739) * radians,
//    (0.746) * radians,
//    (0.746) * radians,
//    (0.746) * radians,
//    (0.742) * radians,
//    (0.705) * radians
//  } );

////poco_adiabatic_may15_25mm_monochrometer_5r_wav_foil (5.6)
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//0.854* radians,
//0.923* radians,
//0.982* radians,
//1.028* radians,
//1.064* radians,
//
//1.085* radians,
//1.079* radians,
//1.029* radians,
//0.957* radians,
//0.871 * radians,
//
//    0.787 * radians,
//    0.729 * radians,
//    0.701 * radians,
//    
//    (0.747)* radians,
//    (0.759) * radians,
//    (0.773) * radians,
//    (0.776) * radians,
//    (0.771) * radians,
//    (0.760) * radians,
//    (0.738) * radians,
//    (0.690) * radians,
//    (0.593) * radians
//  } );
//
////poco_adiabatic_may15_25mm_monochrometer_5r_wav_foil_lights_out (5.6)
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//0.859* radians,
//0.930* radians,
//0.991* radians,
//1.039* radians,
//1.073* radians,
//
//1.097* radians,
//1.092* radians,
//1.049* radians,
//0.963* radians,
//0.870 * radians,
//
//    0.784 * radians,
//    0.719 * radians,
//    0.723 * radians,
//    
//    (0.752)* radians,
//    (0.769) * radians,
//    (0.781) * radians,
//    (0.785) * radians,
////    (0.780) * radians,
////    (0.768) * radians,
////    (0.746) * radians,
////    (0.687) * radians,
////    (0.589) * radians
//  } );
  

//////poco_adiabatic_temp
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//1.301 * radians, // 1.414 Hz
//1.346* radians, // 2.0 Hz
//1.368* radians, //  2.828 Hz
//1.377* radians, //  4.0   Hz
//1.363* radians, //  5.657 Hz
//
//1.331* radians, //  8     Hz
//1.272* radians, //  11.314  Hz
//1.193* radians, //  16.0    Hz
//1.086* radians, //  22.627  Hz
//.972 * radians, //  32.0    Hz
//
//.862 * radians, //  45.255  Hz
//.786 * radians, //  64.0    Hz
//.747 * radians, //  90.510  Hz
//
//(.757)* radians,  // 128      Hz
//(.770) * radians, // 181.019  Hz
//(.776) * radians, // 256      Hz
//(.779) * radians, // 362.039  Hz
//(.773) * radians, // 512      Hz
//(.767) * radians,
//(.756) * radians,
//(.745) * radians,
//(.711) * radians
//  } );
  
  
//  //may 22
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

.863 * radians, //  45.255  Hz
.795 * radians, //  64.0    Hz
.731 * radians, //  90.510  Hz

.691 * radians,  // 128      Hz
.673 * radians,   // 181.019  Hz
.678 * radians, // 256      Hz

.689 * radians, // 362.039  Hz
.692 * radians, // 512      Hz
.687 * radians,  // 724.077
.677 * radians,  // 1024
.675 * radians,  // 1448 Hz
.672 * radians  //  2048 Hz
  } );
  
  auto const beam_radius = quantity< length >( 1.54 * millimeters );
  auto const detector_view_radius = quantity< length>( .1 * millimeters  ) ; // initial value

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
