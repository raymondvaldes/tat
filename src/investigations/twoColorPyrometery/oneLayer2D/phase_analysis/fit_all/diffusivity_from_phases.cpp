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
//    
//    1448.155 * hertz,
//    2048 * hertz,
//
//    2896.3 * hertz,
//    4096 * hertz,
//    5792.6 * hertz,
//    8192 * hertz,
//  11585. * hertz

  });
  
  
////T = 61 deg C
//// day four
//// Sample E
//auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
//
//auto const experimental_phases = vector< quantity< plane_angle > >( {
////.82350 * radians, //  1.0  Hz
////.86322 * radians, //  1.414  Hz
////.90521 * radians, //  2.0  Hz
////.94716 * radians, //  2.828    Hz
////.98341 * radians, // 4.0  Hz
////1.00230 * radians, //  5.657 Hz
//
////1.00691 * radians, //  8     Hz
//.990 * radians, //  11.314  Hz
//.947 * radians, //  16.0    Hz
//.888 * radians, //  22.627  Hz
//.820 * radians, //  32.0    Hz
//
//.765 * radians, //  45.255  Hz
//.737 * radians, //  64.0    Hz
//.732 * radians, //  90.510  Hz
//
//.756 * radians,  // 128      Hz
//.772 * radians,   // 181.019  Hz
//.779 * radians, // 256      Hz
//.780 * radians, // 362.039  Hz
//
//.782 * radians, // 512      Hz
//.783 * radians,  // 724.077
//.788 * radians,  // 1024
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
//// Sample F
//auto const L = quantity< length > ( 1.2 * millimeters  );// sample F
//auto const experimental_phases = vector< quantity< plane_angle > >( {
////
////.721 * radians, //  1.414  Hz
////.753 * radians, //  2.0  Hz
////.777 * radians, //  2.828    Hz
////.791 * radians, // 4.0  Hz
////.792 * radians, //  5.657 Hz
////
////.771 * radians, //  8     Hz
//.771 * radians, //  11.314  Hz
//0.716 * radians, //  16.0    Hz
//0.695 * radians, //  22.627  Hz
//0.695 * radians, //  32.0    Hz
//
//0.713 * radians, //  45.255  Hz
//0.737 * radians, //  64.0    Hz
//0.756 * radians, //  90.510  Hz
//
//0.769 * radians,  // 128      Hz
//0.774 * radians,   // 181.019  Hz
//0.778 * radians, // 256      Hz
//
//0.782 * radians, // 362.039  Hz
//0.784 * radians, // 512      Hz
//
//0.787 * radians,  // 724.077
//.791 * radians,  // 1024
////0.78539816339 * radians,  // 1448 Hz
////0.78539816339 * radians,  //  2048 Hz
////0.78539816339 * radians, // 2896.3  Hz
////
////0.78539816339 * radians, // 4096      Hz
////0.78539816339 * radians,  // 5792.6
////0.78539816339 * radians,  // 8192
////0.78539816339 * radians,  // 11585 Hz
//  } );
//

  
  
////T = 58 deg C
//// Sample C
//auto const L = quantity< length > ( 1.818 * millimeters  );// sample F
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
//0.601 * radians, //  11.314  Hz
//0.625 * radians, //  16.0    Hz
//0.655 * radians, //  22.627  Hz
//0.690 * radians, //  32.0    Hz
//
//0.720 * radians, //  45.255  Hz
//0.744 * radians, //  64.0    Hz
//0.761 * radians, //  90.510  Hz
//
//0.777 * radians,  // 128      Hz
//0.787 * radians,   // 181.019  Hz
//0.792 * radians, // 256      Hz
//
//0.793 * radians, // 362.039  Hz
//0.794 * radians, // 512      Hz
//
//0.793 * radians,  // 724.077
//0.794 * radians,  // 1024
////0.796 * radians,  // 1448 Hz
////.801 * radians,  //  2048 Hz
////.809 * radians, // 2896.3  Hz
////
////.824 * radians, // 4096      Hz
////.845 * radians,  // 5792.6
////.877 * radians,  // 8192
////.924 * radians,  // 11585 Hz
//  } );

    
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
//0.794 * radians,  // 1448 Hz
//0.802 * radians,  //  2048 Hz
//0.78539816339 * radians, // 2896.3  Hz
//
//0.78539816339 * radians, // 4096      Hz
//0.78539816339 * radians,  // 5792.6
//0.78539816339 * radians,  // 8192
//0.78539816339 * radians,  // 11585 Hz
  } );
  
//  //T = 58 deg C
//// Sample H
//auto const L = quantity< length > ( .62 * millimeters  );// sample F
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////.875 * radians, //  2  Hz
////.923 * radians, //  2.828    Hz
////.965 * radians, //  4  Hz
////
////1.002 * radians, //  5.657 Hz
////1.023 * radians, //  8     Hz
//1.017 * radians, //  11.314  Hz
//1.001 * radians, //  16.0    Hz
//0.968 * radians, //  22.627  Hz
//0.909 * radians, //  32.0    Hz
//
//0.844 * radians, //  45.255  Hz
//0.780 * radians, //  64.0    Hz
//0.743 * radians, //  90.510  Hz
//
//0.740 * radians,  // 128      Hz
//0.754 * radians,   // 181.019  Hz
//0.771 * radians, // 256      Hz
//
//0.781 * radians, // 362.039  Hz
//0.785 * radians, // 512      Hz
//
//0.787 * radians,  // 724.077
//0.792 * radians,  // 1024
////0.794 * radians,  // 1448 Hz
////0.802 * radians,  //  2048 Hz
////0.78539816339 * radians, // 2896.3  Hz
////
////0.78539816339 * radians, // 4096      Hz
////0.78539816339 * radians,  // 5792.6
////0.78539816339 * radians,  // 8192
////0.78539816339 * radians,  // 11585 Hz
//  } );


////T = 61 deg C
//// day four
//// Sample E
//auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
//
//auto const experimental_phases = vector< quantity< plane_angle > >( {
////.82350 * radians, //  1.0  Hz
////.86322 * radians, //  1.414  Hz
////.90521 * radians, //  2.0  Hz
////.94716 * radians, //  2.828    Hz
////.98341 * radians, // 4.0  Hz
////1.00230 * radians, //  5.657 Hz
////
////1.00691 * radians, //  8     Hz
//.98956 * radians, //  11.314  Hz
//.94624 * radians, //  16.0    Hz
//.88775 * radians, //  22.627  Hz
//.81816 * radians, //  32.0    Hz
//
//.76239 * radians, //  45.255  Hz
//.73525 * radians, //  64.0    Hz
//.74261 * radians, //  90.510  Hz
//
////.77451 * radians, //  45.255  Hz  // corrected 50%
////.74079 * radians, //  64.0    Hz //corrected  50%
////.74261 * radians, //  90.510  Hz  // corrected 50%
//
//.75555 * radians,  // 128      Hz
//.77133 * radians,   // 181.019  Hz
//.77923 * radians, // 256      Hz
//.77921 * radians, // 362.039  Hz
//
//.78284 * radians, // 512      Hz
//.78438 * radians,  // 724.077
//0.78539816339 * radians,  // 1024
////0.78539816339 * radians,  // 1448 Hz
////0.78539816339 * radians,  //  2048 Hz
////0.78539816339 * radians, // 2896.3  Hz
////
////0.78539816339 * radians, // 4096      Hz
////0.78539816339 * radians,  // 5792.6
////0.78539816339 * radians,  // 8192
////0.78539816339 * radians,  // 11585 Hz
//  } );
  
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
////  } );
//
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
////0.794 * radians,  // 1448 Hz
////0.802 * radians,  //  2048 Hz
////0.78539816339 * radians, // 2896.3  Hz
////
////0.78539816339 * radians, // 4096      Hz
////0.78539816339 * radians,  // 5792.6
////0.78539816339 * radians,  // 8192
////0.78539816339 * radians,  // 11585 Hz
//  } );

////T = 58 deg C
//// Sample F
//auto const L = quantity< length > ( 1.2 * millimeters  );// sample F
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////0.821 * radians, //  5.657 Hz
////0.794 * radians, //  8     Hz
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
//0.785 * radians,  // 724.077
//0.78539816339 * radians,  // 1024
////0.78539816339 * radians,  // 1448 Hz
////0.78539816339 * radians,  //  2048 Hz
////0.78539816339 * radians, // 2896.3  Hz
////
////0.78539816339 * radians, // 4096      Hz
////0.78539816339 * radians,  // 5792.6
////0.78539816339 * radians,  // 8192
////0.78539816339 * radians,  // 11585 Hz
//  } );




  
//  ////T = 61 deg C
//// day four (blue line) (25%)
//// Sample E
//auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
//
//auto const experimental_phases = vector< quantity< plane_angle > >( {
////.86289 * radians, //  1.0  Hz
////.92042 * radians, //  1.414  Hz
////.97712 * radians, //  2.0  Hz
//.97706 * radians, //  2.828    Hz
//.97546 * radians, // 4.0  Hz
//1.01023 * radians, //  5.657 Hz
//
//1.02301 * radians, //  8     Hz
//.99442 * radians, //  11.314  Hz
//.95859 * radians, //  16.0    Hz
//.88877 * radians, //  22.627  Hz
//.83534 * radians, //  32.0    Hz
//.78848 * radians, //  45.255  Hz
//
//.75203 * radians, //  64.0    Hz
//.75512 * radians, //  90.510  Hz
//.76506 * radians,  // 128      Hz
//.77735 * radians,   // 181.019  Hz
//.77929 * radians, // 256      Hz
////.79744 * radians, // 362.039  Hz
////
////.78284 * radians, // 512      Hz
////78438 * radians,  // 724.077
////.78803 * radians,  // 1024
////.79214 * radians,  // 1448 Hz
////.79592 * radians  //  2048 Hz
////.80403 * radians, // 2896.3  Hz
//
////.81694 * radians, // 4096      Hz
////.83670 * radians,  // 5792.6
////.86354 * radians,  // 8192
////.90431 * radians,  // 11585 Hz
//  } );


//  ////T = 61 deg C
//// day four (blue line) (40%)
//// Sample E
//auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
//
//auto const experimental_phases = vector< quantity< plane_angle > >( {
////.84739 * radians, //  1.0  Hz
////.89961 * radians, //  1.414  Hz
////.95240 * radians, //  2.0  Hz
////.97955 * radians, //  2.828    Hz
//.97285 * radians, // 4.0  Hz
//1.00249 * radians, //  5.657 Hz
//
//1.01305 * radians, //  8     Hz
//.98820 * radians, //  11.314  Hz
//.95005 * radians, //  16.0    Hz
//.88301 * radians, //  22.627  Hz
//.82559 * radians, //  32.0    Hz
//.77675 * radians, //  45.255  Hz
//
//.74312 * radians, //  64.0    Hz
//.74423 * radians, //  90.510  Hz
//.75741 * radians,  // 128      Hz
//.77020 * radians,   // 181.019  Hz
//.77373 * radians, // 256      Hz
////.79744 * radians, // 362.039  Hz
////
////.78284 * radians, // 512      Hz
////78438 * radians,  // 724.077
////.78803 * radians,  // 1024
////.79214 * radians,  // 1448 Hz
////.79592 * radians  //  2048 Hz
////.80403 * radians, // 2896.3  Hz
//
////.81694 * radians, // 4096      Hz
////.83670 * radians,  // 5792.6
////.86354 * radians,  // 8192
////.90431 * radians,  // 11585 Hz
//  } );
//  
    //T = 61 deg C
// day four (blue line) (50%)
// Sample E
//auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
//
//auto const experimental_phases = vector< quantity< plane_angle > >( {
////.84539 * radians, //  1.0  Hz
////.89923 * radians, //  1.414  Hz
////.95207 * radians, //  2.0  Hz
////.97778 * radians, //  2.828    Hz
//.96806 * radians, // 4.0  Hz
//.99785 * radians, //  5.657 Hz
//
//1.0082 * radians, //  8     Hz
//.98360 * radians, //  11.314  Hz
//.94596 * radians, //  16.0    Hz
//.87861 * radians, //  22.627  Hz
//.82207 * radians, //  32.0    Hz
//.77451 * radians, //  45.255  Hz
//
//.74079 * radians, //  64.0    Hz
//.74261 * radians, //  90.510  Hz
//.75460 * radians,  // 128      Hz
//.76677 * radians,   // 181.019  Hz
//.76933 * radians, // 256      Hz
////.78355 * radians, // 362.039  Hz
////
////.78284 * radians, // 512      Hz
////78438 * radians,  // 724.077
////.78803 * radians,  // 1024
////.79214 * radians,  // 1448 Hz
////.79592 * radians  //  2048 Hz
////.80403 * radians, // 2896.3  Hz
//
////.81694 * radians, // 4096      Hz
////.83670 * radians,  // 5792.6
////.86354 * radians,  // 8192
////.90431 * radians,  // 11585 Hz
//  } );








  

//////T = 61 deg C
//// dayone
//// Sample E
//auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////.797 * radians, //  2.0  Hz
////.827 * radians, //  2.828    Hz
////.852 * radians, // 4.0  Hz
////0.868 * radians, //  5.657 Hz
////
////0.871 * radians, //  8     Hz
//.971 * radians, //  11.314  Hz
//.938 * radians, //  16.0    Hz
//.885 * radians, //  22.627  Hz
//.823 * radians, //  32.0    Hz
//
//.769 * radians, //  45.255  Hz
//.738 * radians, //  64.0    Hz
//.736 * radians, //  90.510  Hz
//
//.755 * radians,  // 128      Hz
//.771 * radians,   // 181.019  Hz
//.779 * radians, // 256      Hz
//
//.781 * radians, // 362.039  Hz
//.783 * radians, // 512      Hz
//
//0.791 * radians,  // 724.077
//0.795 * radians,  // 1024
////
////0.799 * radians,  // 1448 Hz
////0.806 * radians  //  2048 Hz
//  } );

//////T = 58 deg C
//// day two with aperture
//// Sample E
//auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
//
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////.860 * radians, //  2.0  Hz
////.908 * radians, //  2.828    Hz
////.947 * radians, // 4.0  Hz
////.975 * radians, //  5.657 Hz
////
////.988 * radians, //  8     Hz
//.980 * radians, //  11.314  Hz
//.945 * radians, //  16.0    Hz
//.891 * radians, //  22.627  Hz
//.821 * radians, //  32.0    Hz
//
//.766 * radians, //  45.255  Hz
//.734 * radians, //  64.0    Hz
//.731 * radians, //  90.510  Hz
//
//.751 * radians,  // 128      Hz
//.768 * radians,   // 181.019  Hz
//.776 * radians, // 256      Hz
//
//.779 * radians, // 362.039  Hz
//.781 * radians, // 512      Hz
//
//0.784 * radians,  // 724.077
//0.787 * radians,  // 1024
//
////.792 * radians,  // 1448 Hz
////0.822 * radians  //  2048 Hz
//  } );

//////T = 58 deg C
//// day two without aperture
//// Sample E
//auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////.895 * radians, //  2.0  Hz
////.937 * radians, //  2.828    Hz
////.977 * radians, // 4.0  Hz
////1.001 * radians, //  5.657 Hz
////
////1.008 * radians, //  8     Hz
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
//
//(.782 - .0036) * radians, // 362.039  Hz
//(.783 - .0051) * radians, // 512      Hz
//
//(0.785 - .0073) * radians,  // 724.077
//(0.788 - .0103) * radians,  // 1024
////
////.792 * radians,  // 1448 Hz
////.798 * radians  //  2048 Hz
//  } );


//////T = 58 deg C
//// day two without aperture
//// Sample E // 15 min hold
//auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////.855 * radians, //  2.0  Hz
////.893 * radians, //  2.828    Hz
////.925 * radians, // 4.0  Hz
////.947 * radians, //  5.657 Hz
////
////.955 * radians, //  8     Hz
//.944 * radians, //  11.314  Hz
//.914 * radians, //  16.0    Hz
//.872 * radians, //  22.627  Hz
//.809 * radians, //  32.0    Hz
//
//.759 * radians, //  45.255  Hz
//.730 * radians, //  64.0    Hz
//.729 * radians, //  90.510  Hz
//
//(.749 ) * radians,  // 128      Hz
//(.766 ) * radians,   // 181.019  Hz
//(.774 ) * radians, // 256      Hz
//
//(.778 ) * radians, // 362.039  Hz
//(.780 ) * radians, // 512      Hz
//
//( 0.783 ) * radians,  // 724.077
//( 0.786 )  * radians,  // 1024
////
////.791 * radians,  // 1448 Hz
////.798 * radians  //  2048 Hz
//  } );


//////T = 60 deg C
//// day three without aperture
//// Sample E // 15 min hold
//auto const L = quantity< length > ( 0.8 * millimeters  );// sample E
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////.940 * radians, // 4.0  Hz
////.963 * radians, //  5.657 Hz
////
////.966 * radians, //  8     Hz
//.949 * radians, //  11.314  Hz
//.915 * radians, //  16.0    Hz
//.863 * radians, //  22.627  Hz
//.804 * radians, //  32.0    Hz
//
//.756 * radians, //  45.255  Hz
//.731 * radians, //  64.0    Hz
//.729 * radians, //  90.510  Hz
//
//(.749 ) * radians,  // 128      Hz
//(.766 ) * radians,   // 181.019  Hz
//(.774 ) * radians, // 256      Hz
//
//(.778 ) * radians, // 362.039  Hz
//(.780 ) * radians, // 512      Hz
//
//( 0.783 ) * radians,  // 724.077
//( 0.786 )  * radians,  // 1024
//
////.791 * radians,  // 1448 Hz
////.798 * radians  //  2048 Hz
//  } );


//
////T = 82 deg C
////
//// Sample C
//auto const L = quantity< length > ( 1.64 * millimeters  );// sample E
//
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////0.416 * radians, //  2.0  Hz
////0.584 * radians, //  2.828    Hz
////0.583 * radians, // 4.0  Hz
////0.581 * radians, //  5.657 Hz
////
////0.585 * radians, //  8     Hz
//0.598 * radians, //  11.314  Hz
//0.624 * radians, //  16.0    Hz
//0.658 * radians, //  22.627  Hz
//0.689 * radians, //  32.0    Hz
//
//0.709 * radians, //  45.255  Hz
//0.723 * radians, //  64.0    Hz
//0.731 * radians, //  90.510  Hz
//
//0.740 * radians,  // 128      Hz
//0.745 * radians,   // 181.019  Hz
//0.781 * radians, // 256      Hz
//
//0.786 * radians, // 362.039  Hz
//0.788 * radians, // 512      Hz
//
//0.791 * radians,  // 724.077
//0.795 * radians,  // 1024
////
////0.799 * radians,  // 1448 Hz
////0.806 * radians  //  2048 Hz
//  } );

////T = 82 deg C
//// Sample D
//auto const L = quantity< length > ( 10.13 * millimeters  ); //sample D
//auto const experimental_phases = vector< quantity< plane_angle > >( {
//
////0.416 * radians, //  2.0  Hz
////0.416 * radians, //  2.828    Hz
////0.462 * radians, // 4.0  Hz
////0.505 * radians, //  5.657 Hz
////
////0.549 * radians, //  8     Hz
//0.590 * radians, //  11.314  Hz
//0.626 * radians, //  16.0    Hz
//0.659 * radians, //  22.627  Hz
//0.684 * radians, //  32.0    Hz
//
//0.705 * radians, //  45.255  Hz
//0.716 * radians, //  64.0    Hz
//0.727 * radians, //  90.510  Hz
//
//0.737 * radians,  // 128      Hz
//0.743 * radians,   // 181.019  Hz
//0.781 * radians, // 256      Hz
//
//0.786 * radians, // 362.039  Hz
//0.788 * radians, // 512      Hz
//
//0.791 * radians,  // 724.077
//0.795 * radians,  // 1024
//
////0.799 * radians,  // 1448 Hz
////0.806 * radians  //  2048 Hz
//  } );


  auto const beam_radius = quantity< length >( 2.2 * millimeters );
  auto const detector_view_radius = quantity< length>( .25 * millimeters  ) ;
  auto const alpha = quantity<thermal_diffusivity>( 50 * square_millimeters / second);
  
  initial_slab.set_thickness(L);
  initial_slab.set_diffusivity_update_k_hold_rhoCp( alpha );


  auto const bestFit_results = fit(
    frequencies, experimental_phases , initial_slab, beam_radius, detector_view_radius ) ;
  
  bestFit_results.plot_model_phases_against( experimental_phases );
}

} // namespace
} // namespace
} // namespace
} // namespace
} // namespace
