//
//  steady_state_temperature.cpp
//  tat
//
//  Created by Raymond Valdes on 9/9/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "steady_state_temperature.hpp"
#include <iostream>
#include <utility>
#include "units.h"
#include "thermal/pyrometry/twoColor/calibrationCoefficient.h"
#include "thermal/pyrometry/twoColor/temperatureSteady.h"
#include "thermal/pyrometry/twoColor/signalRatio.h"

namespace investigations {
namespace twoColorPyrometery {
namespace calculators{

using thermal::pyrometry::twoColor::calibrationCoefficient;
using thermal::pyrometer::twoColor::temperatureSteady;
using thermal::pyrometer::twoColor::signalRatio;
using namespace units;
using std::make_pair;

auto steady_state_temperature( void ) noexcept -> void
{
  auto const wavelength_1 = quantity< length >( 4.08133 * micrometers );
  auto const wavelength_2 = quantity< length >( 5.22813 * micrometers );
  auto const wavelength_pair = make_pair( wavelength_1, wavelength_2 );

  auto const calibration_signal_1 = quantity< electric_potential >( 0.1017 * volts ) ;
  auto const calibration_signal_2 = quantity< electric_potential >( 0.3199 * volts ) ;
  auto const calibration_signal_pair = make_pair( calibration_signal_1, calibration_signal_2 );

  auto const calibration_temperature = units::quantity< units::absolute< units::si::temperature > >::from_value( 369.0388889 );
  std::cout << "The calibration temperature is: " << calibration_temperature << "\n";

  auto const g_coefficient = calibrationCoefficient(
    calibration_signal_pair,
    wavelength_pair,
    calibration_temperature );
  std::cout << "The calibration coeffienct is: " << g_coefficient.value() << "\n";

  auto const g_coefficient_est = 0.776_nd;

  auto const signal_1 = quantity< electric_potential >( .829 * volts ) ;
  auto const signal_2 = quantity< electric_potential >( 1.5165 * volts ) ;
  auto const signal_ratio = signalRatio( signal_1, signal_2 );
  
  auto const temperature_measurement =
  temperatureSteady
  (
    g_coefficient_est,     signal_ratio,
    wavelength_pair
  );
  
  std::cout << "The predicted surface temperature is: " << temperature_measurement << "\n";

  std::cout << "hello, world" << "\n";
}

} // namespace calculators
} // namespace investigations
} // namespace twoColorPyrometery
