//
//  amplitudes_from_experiment.cpp
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/amplitude_analysis/amplitudes_from_experiment.h"

#include <iostream>
#include <utility>
#include <vector>

#include "units.h"
#include "math/functions/PeriodicProperties.h"
#include "thermal/pyrometry/twoColor/periodic/analysis_from_properties_sweep.h"
#include "thermal/pyrometry/twoColor/calibrate_wavelength.h"
#include "cout/vector/print.h"

using namespace units;
using std::vector;
using math::functions::PeriodicProperties;
using thermal::pyrometry::twoColor::periodic::analysis_from_properties_sweep;
using thermal::pyrometry::twoColor::calibrate_wavelength;
using cout::vector::print;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace amplitude_analysis{

auto amplitudes_from_experiment( filesystem::directory const & dir ) -> void
{
  auto const gCoeff = 0.863029_nd;
  
  auto const DC_background = 3.358*volts;
  auto const DC_1 = 3.614*volts - DC_background;
  auto const DC_2 = 3.601*volts - DC_background;
  
  auto const wavelength_offset = quantity< wavelength >( -.5743693 * micrometers );
  auto const lambda_1 = quantity<wavelength>( 4.6*micrometers );
  auto const lambda_2 = quantity<wavelength>( 5.6*micrometers );
  
  auto const detector_wavelength_1 =
    calibrate_wavelength( lambda_1, wavelength_offset );
  
  auto const detector_wavelength_2 =
    calibrate_wavelength( lambda_2, wavelength_offset );
  
  auto const frequencies = vector< quantity< frequency > >({
    1.414   * hertz,
    2       * hertz,
    2.828   * hertz,
    4       * hertz,
    5.657   * hertz,
    8       * hertz,
    11.314  * hertz,
    16      * hertz,
    22.627  * hertz,
    32      * hertz,
    45.255  * hertz,
    64      * hertz,
    90.51   * hertz,
    128     * hertz,
    181.019 * hertz,
    256     * hertz,
    362.039 * hertz,
    512     * hertz,
    724.077 * hertz,
    1024    * hertz,
    1448.155* hertz,
    2048    * hertz
  });

  auto const properties_1 =
  vector< PeriodicProperties< electric_potential >>({
    PeriodicProperties< electric_potential >(
    DC_1,
    27.15 /1000 * volts,
    1.414   * hertz,
    0.988 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    22.17 /1000 * volts,
    2   * hertz,
    1.0455 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    16.65 /1000 * volts,
    2.828   * hertz,
    1.085 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    15.66 /1000 * volts,
    4   * hertz,
    1.1055 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    12.71 /1000 * volts,
    5.657   * hertz,
    1.1105 * radians ),
    PeriodicProperties< electric_potential >(
    DC_1,
    6.14 /1000 * volts,
    8   * hertz,
    1.106 * radians ),
    PeriodicProperties< electric_potential >(
    DC_1,
    7.58 /1000 * volts,
    11.314   * hertz,
    1.064 * radians ),
    PeriodicProperties< electric_potential >(
    DC_1,
    3.33 /1000 * volts,
    16   * hertz,
    1.0025 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    2.77 /1000 * volts,
    22.627   * hertz,
    .912 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    2.59 /1000 * volts,
    32   * hertz,
    .808 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    2.38 /1000 * volts,
    42.255   * hertz,
    .7215 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    1.62 /1000 * volts,
    64.   * hertz,
    .665 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    1.37 /1000 * volts,
    90.51   * hertz,
    .6465 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    1.53 /1000 * volts,
    128.   * hertz,
    .65 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    1.26 /1000 * volts,
    181.019   * hertz,
    .6495 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    1.02 /1000 * volts,
    256   * hertz,
    .639 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    .87 /1000 * volts,
    362.039   * hertz,
    .5975 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    .75 /1000 * volts,
    512   * hertz,
    .5975 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    .67 /1000 * volts,
    724.077   * hertz,
    .5755 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    .61 /1000 * volts,
    1024.   * hertz,
    .549 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    .55 /1000 * volts,
    1448.155   * hertz,
    .525 * radians),
    PeriodicProperties< electric_potential >(
    DC_1,
    .46 /1000 * volts,
    2048.   * hertz,
    .491 * radians)
  });
  
  auto const properties_2 =
  vector< PeriodicProperties< electric_potential >>({
    PeriodicProperties< electric_potential >(
    DC_2,
    19.74 /1000 * volts,
    1.414   * hertz,
    1.001 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    14.03 /1000 * volts,
    2   * hertz,
    1.064 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    11.06 /1000 * volts,
    2.828   * hertz,
    1.096 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    11.26 /1000 * volts,
    4   * hertz,
    1.121 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    6.28 /1000 * volts,
    5.657   * hertz,
    1.124 * radians ),
    PeriodicProperties< electric_potential >(
    DC_2,
    6.87 /1000 * volts,
    8   * hertz,
    1.12 * radians ),
    PeriodicProperties< electric_potential >(
    DC_2,
    3.35 /1000 * volts,
    11.314   * hertz,
    1.077 * radians ),
    PeriodicProperties< electric_potential >(
    DC_2,
    2.38 /1000 * volts,
    16   * hertz,
    1.008 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    2.01 /1000 * volts,
    22.627   * hertz,
    0.918 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    1.67 /1000 * volts,
    32   * hertz,
    0.809 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    1.32 /1000 * volts,
    42.255   * hertz,
    0.726 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    1.26 /1000 * volts,
    64.   * hertz,
    0.668 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    0.96 /1000 * volts,
    90.51   * hertz,
    0.652 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    0.93 /1000 * volts,
    128.   * hertz,
    0.658 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    0.78 /1000 * volts,
    181.019   * hertz,
    0.66 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    0.67 /1000 * volts,
    256   * hertz,
    0.648 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    0.55 /1000 * volts,
    362.039   * hertz,
    0.634 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    0.51 /1000 * volts,
    512   * hertz,
    0.61 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    0.46 /1000 * volts,
    724.077   * hertz,
    0.589 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    0.42 /1000 * volts,
    1024.   * hertz,
    0.56 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    0.38 /1000 * volts,
    1448.155   * hertz,
    0.538 * radians),
    PeriodicProperties< electric_potential >(
    DC_2,
    0.36 /1000 * volts,
    2048.   * hertz,
    0.495 * radians)
  });

  auto const temperature_analysis =
    analysis_from_properties_sweep(
      properties_1, detector_wavelength_1,
      properties_2, detector_wavelength_2,
      gCoeff,
      frequencies
    );

  auto const surface_temperature_phases =
  temperature_analysis.surface_temperature_phases();
  
  auto const surface_temperature_steady =
  temperature_analysis.surface_steady_temperature();
  
  auto const surface_temperature_amplitudes =
  temperature_analysis.surface_temperature_amplitudes();
  
  std::cout << surface_temperature_steady << "\n";
  
  cout::vector::print( surface_temperature_amplitudes );

}

} // namespace
} // namespace
} // namespace
} // namespace
