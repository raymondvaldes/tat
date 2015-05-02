//
//  amplitudes_from_experiment.cpp
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/amplitude_analysis/amplitudes_from_experiment.h"

#include "units.h"
#include <utility>
#include <vector>

using namespace units;
using std::vector;
using std::make_pair;
using std::pair;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace amplitude_analysis{

auto amplitudes_from_experiment( filesystem::directory const & dir ) -> void
{

  auto const gCoeff = 0.863_nd;
  
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

    auto const detector_signal = std::pair< quantity<length>,
    quantity<length> >( .02715 * meters, .01974 * meters ) ;
  
//    auto const signal_amplitudes =
//    vector<
//      std::pair< quantity< length >, quantity< length > >
//    >( make_pair( 27.15 * meters   , 19.74 * meters)  );
  
//  auto const signal_amplitudes =
//    vector<
//      std::pair< quantity< electric_potential >, quantity< electric_potential > >
//    >({
//        make_pair( 27.15 * millivolts, 19.74 * millivolts )
////    { 22.17 * millivolts, 14.03 * millivolts },
////    { 16.65 * millivolts, 11.06 * millivolts },
////    { 15.66 * millivolts, 11.26 * millivolts },
////    { 12.71 * millivolts, 6.28 * millivolts },
////    { 6.14 * millivolts, 6.87 * millivolts },
////    { 7.58 * millivolts, 3.35 * millivolts },
////    { 3.33 * millivolts, 2.38 * millivolts },
////    { 2.77 * millivolts, 2.01 * millivolts },
////    { 2.59 * millivolts, 1.67 * millivolts },
////    { 2.38 * millivolts, 1.32 * millivolts },
////    { 1.62 * millivolts, 1.26 * millivolts },
////    { 1.37 * millivolts, 0.96 * millivolts },
////    { 1.53 * millivolts, 0.93 * millivolts },
////    { 1.26 * millivolts, 0.78 * millivolts },
////    { 1.02 * millivolts, 0.67 * millivolts },
////    { 0.87 * millivolts, 0.55 * millivolts },
////    { 0.75 * millivolts, 0.51 * millivolts },
////    { 0.67 * millivolts, 0.46 * millivolts },
////    { 0.61 * millivolts, 0.42 * millivolts },
////    { 0.55 * millivolts, 0.38 * millivolts },
////    { 0.46 * millivolts, 0.36 * millivolts },
//  });

}

} // namespace
} // namespace
} // namespace
} // namespace

