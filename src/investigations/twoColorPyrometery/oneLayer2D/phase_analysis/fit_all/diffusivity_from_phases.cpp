//
//  diffusivity_from_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all/diffusivity_from_phases.h"

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all/diffusivity_from_phases.h"
#include "thermal/pyrometry/twoColor/calibrate_wavelength.h"
#include "thermal/model/slab/import_slab.h"
#include "units.h"

using namespace units;
using std::vector;
using thermal::model::slab::import ;
using thermal::pyrometry::twoColor::calibrate_wavelength;
using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_all::fit;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace phase_analysis{
namespace fit_all{

auto diffusivity_from_phases( filesystem::directory const & dir ) -> void
{
  auto initial_slab = thermal::model::slab::import( dir, "initial_slab.xml" ) ;
  initial_slab.characteristic_length = quantity< si::length >(0.65 * millimeters);  
  
  auto const frequencies = vector< quantity< frequency > >({
//    1.414 * hertz,
//    2 * hertz,
//    2.828 * hertz,
//    4 * hertz,
//    5.657 * hertz,
    
//    8 * hertz,
//    11.314 * hertz,
    16 * hertz,
    22.627 * hertz,
    32 * hertz,
    
    45.255 * hertz,
    64 * hertz,
//    90.51 * hertz,
//    
//    128 * hertz,
//    181.019 * hertz,
//    256 * hertz,
//    362.039 * hertz,
//    
//    512 * hertz,
//    
//    724.077 * hertz,
//    1024 * hertz,
//    1448.155 * hertz,
//    2048 * hertz
  });


//////poco_adiabatic_may12_25mm_no_monochrometer_wav _.1_.1
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//0.772* radians,
//0.834* radians,
//0.896* radians,
//0.943* radians,
//0.992* radians,
//
//1.029* radians,
//1.067* radians,
//1.088* radians,
//1.058* radians,
//1.040 * radians,
//
//    0.952 * radians,
//    0.868 * radians,
//    0.803 * radians,
//    0.738 * radians,
//    0.713 * radians,
//    
//    0.714 * radians,
//    0.722 * radians,
//    0.727 * radians,
//    0.724 * radians,
//    0.718 * radians,
//    0.715 * radians,
//    0.709 * radians
//  } );

//////poco_adiabatic_may12_25mm_no_monochrometer_2_wav
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//0.826* radians,
//0.900* radians,
//0.966* radians,
//1.009* radians,
//1.059* radians,
//
//1.089* radians,
//1.118* radians,
//1.100* radians,
//1.076* radians,
//1.032 * radians,
//
//    0.934 * radians,
//    0.846 * radians,
//    0.778 * radians,
//    0.736 * radians,
//    0.714 * radians,
//    
//    0.718 * radians,
//    0.727 * radians,
//    0.729 * radians,
//    0.723 * radians,
//    0.715 * radians,
//    0.709 * radians,
//    0.698 * radians
//  } );
//
//////poco_adiabatic_may12_25mm_no_monochrometer_5r_wav (corrected bias)
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
  
//poco_adiabatic_may12_25mm_no_monochrometer_5r_wav
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

//poco_adiabatic_may12_25mm_no_monochrometer_5_5_140_wav
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//0.781* radians,
//0.847* radians,
//0.903* radians,
//0.946* radians,
//0.998* radians,
//1.016* radians,
//1.031* radians,
//1.026* radians,
//0.970* radians,
//0.901 * radians,
//
//    0.820 * radians,
//    0.759 * radians,
//    0.717 * radians,
//    0.725 * radians,
//    0.732 * radians,
//    0.744 * radians,
//    0.748 * radians,
//    0.743 * radians,
//    0.738 * radians,
//    0.732 * radians,
//    0.728 * radians,
//    0.725 * radians
//  } );

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
  
////poco_adiabatic_may15_25mm_monochrometer_5r_wav (5.6)
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
//////poco_adiabatic_may15_25mm_monochrometer_5r_wav_foil_lights_out (5.6)
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
  



////poco_adiabatic_temp
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//.650 * radians, // 1.414 Hz
//.708 * radians, // 2.0 Hz
//.761 * radians, //  2.828 Hz
//.816 * radians, //  4.0   Hz
//.863 * radians, //  5.657 Hz
//
//.916 * radians, //  8     Hz
//.948 * radians, //  11.314  Hz
//.966 * radians, //  16.0    Hz
//.968 * radians, //  22.627  Hz
//.936 * radians, //  32.0    Hz
//
//.872 * radians, //  45.255  Hz
//.808 * radians, //  64.0    Hz
//.756 * radians, //  90.510  Hz
//
////(.757)* radians,  // 128      Hz
////(.770) * radians, // 181.019  Hz
////(.776) * radians, // 256      Hz
////(.779) * radians, // 362.039  Hz
////(.773) * radians, // 512      Hz
////(.767) * radians,
////(.756) * radians,
////(.745) * radians,
////(.711) * radians
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
  
//  //may 22 (run 2)
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//0.672 * radians, // 1.414 Hz
//0.732 * radians, // 2.0 Hz
//0.787 * radians, //  2.828 Hz
//0.840 * radians, //  4.0   Hz
//0.891 * radians, //  5.657 Hz
//
//0.934 * radians, //  8     Hz
//0.960 * radians, //  11.314  Hz
//0.978 * radians, //  16.0    Hz
//0.959 * radians, //  22.627  Hz
//0.919 * radians, //  32.0    Hz
//
//0.851 * radians, //  45.255  Hz
//0.786 * radians, //  64.0    Hz
//0.717 * radians, //  90.510  Hz
//
//0.682 * radians,  // 128      Hz
//0.670 * radians,   // 181.019  Hz
//0.678 * radians, // 256      Hz
//0.689 * radians, // 362.039  Hz
//0.692 * radians, // 512      Hz
//0.688 * radians,  //
//0.683 * radians,  //
//0.680 * radians,  //
//0.678 * radians  //  2000 Hz
//  } );
  
//  may 29
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//0.632 * radians, // 1.414 Hz
//0.684 * radians, // 2.0 Hz
//0.732 * radians, //  2.828 Hz
//0.781 * radians, //  4.0   Hz
//0.828 * radians, //  5.657 Hz
//
//0.864 * radians, //  8     Hz
//0.900 * radians, //  11.314  Hz
//0.916 * radians, //  16.0    Hz
//0.909 * radians, //  22.627  Hz
//0.880 * radians, //  32.0    Hz
//
//0.838 * radians, //  45.255  Hz
//0.786 * radians, //  64.0    Hz
//0.722 * radians, //  90.510  Hz
//
//0.675 * radians,  // 128      Hz
//0.656 * radians,   // 181.019  Hz
//0.654 * radians, // 256      Hz
//0.631 * radians, // 362.039  Hz
//0.629 * radians, // 512      Hz
//0.645 * radians,  //
//0.634 * radians,  //
//0.626 * radians,  //
//0.625 * radians  //  2000 Hz
//  } );
  
//  //T=335 F (4.1 um filter)
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//.843 * radians, // 1.414 Hz
//.886 * radians, // 2.0 Hz
//.920 * radians, //  2.828 Hz
//.949 * radians, //  4.0   Hz
//.968 * radians, //  5.657 Hz
//
//.981 * radians, //  8     Hz
//.981 * radians, //  11.314  Hz
//.971 * radians, //  16.0    Hz
//.934 * radians, //  22.627  Hz
//.876 * radians, //  32.0    Hz
//
//.805 * radians, //  45.255  Hz
//.746 * radians, //  64.0    Hz
//.691 * radians, //  90.510  Hz
//
//.682 * radians,  // 128      Hz
//.686 * radians,   // 181.019  Hz
//.698 * radians, // 256      Hz
//.704 * radians, // 362.039  Hz
//.704 * radians, // 512      Hz
//.700 * radians,  // 724.077
//.697 * radians,  // 1024
//.697 * radians,  //
//.698 * radians  //  2000 Hz
//  } );
//  
//  //T=244 F (5.2 um filter)
//  auto const experimental_phases = vector< quantity< plane_angle > >( {
//.828 * radians, // 1.414 Hz
//.865 * radians, // 2.0 Hz
//.904 * radians, //  2.828 Hz
//.932 * radians, //  4.0   Hz
//.959 * radians, //  5.657 Hz
//
//.976 * radians, //  8     Hz
//.983 * radians, //  11.314  Hz
//.985 * radians, //  16.0    Hz
//.949 * radians, //  22.627  Hz
//.905 * radians, //  32.0    Hz
//
//.843 * radians, //  45.255  Hz
//.782 * radians, //  64.0    Hz
//.727 * radians, //  90.510  Hz
//
//.695 * radians,  // 128      Hz
//.688 * radians,   // 181.019  Hz
//.698 * radians, // 256      Hz
//.708 * radians, // 362.039  Hz
//.711 * radians, // 512      Hz
//.708 * radians,  // 724.077
//.705 * radians,  // 1024
//.704 * radians,  //
//.702 * radians  //  2000 Hz
//  } );
//  
  //T=168 F (no filter)
  auto const experimental_phases = vector< quantity< plane_angle > >( {
//.746 * radians, // 1.414 Hz
//.800 * radians, // 2.0 Hz
//.854 * radians, //  2.828 Hz
//.921 * radians, //  4.0   Hz
//.921 * radians, //  5.657 Hz

//.953 * radians, //  8     Hz
//.972 * radians, //  11.314  Hz
.970 * radians, //  16.0    Hz
.953 * radians, //  22.627  Hz
.917 * radians, //  32.0    Hz

.863 * radians, //  45.255  Hz
.795 * radians, //  64.0    Hz
//.731 * radians, //  90.510  Hz
//
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
  
  auto const beam_radius = quantity< length >( 1.5 * millimeters );
  auto const detector_view_radius = quantity< length>( 1.0 * millimeters  ) ; // initial value

  auto const bestFit_results = fit(
    frequencies, experimental_phases , initial_slab, beam_radius, detector_view_radius ) ;
  
  bestFit_results.plot_model_phases_against( experimental_phases );
}

} // namespace
} // namespace
} // namespace
} // namespace
} // namespace
