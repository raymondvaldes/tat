//
//  temperature_prediction.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>

#include "investigations/twoColorPyrometery/temperature_prediction.h"

#include "thermal/pyrometry/twoColor/temperatureSteady.h"
#include "thermal/pyrometry/twoColor/normalizedDetectorMeasurements.h"
#include "thermal/pyrometry/twoColor/signalRatio.h"
#include "thermal/pyrometry/twoColor/normalizedSignalRatio.h"
#include "thermal/pyrometry/twoColor/calibratedSignalRatio.h"

#include "math/construct/periodic_time_distribution.h"
#include "math/functions/periodicData.h"
#include "math/curveFit/cosine.h"

#include "thermal/equipment/detector/measurements.h"
#include "gTBC/gMeasure/get_signal_from_scope_file.h"
#include "tools/interface/xml.h"
#include "units.h"

#include "algorithm/vector/operator_overloads.h"
#include "thermal/pyrometry/twoColor/pyrometery_settings_file.h"


namespace investigations {

namespace twoColorPyrometery {

inline auto
measurementFactory( filesystem::directory const & dir,
  std::string const& filename,
  units::quantity< units::si::electric_potential > const & signal_DC_raw,
  units::quantity< units::si::electric_potential > const & signal_background,
  units::quantity< units::si::frequency > const & frequency,
  size_t const cycles,
  units::quantity< units::si::wavelength> const & detector_wavelength )
noexcept -> thermal::equipment::detector::Measurements
{
  assert( !filename.empty() );
  assert( signal_DC_raw.value() > 0 );
  assert( signal_background.value() >= 0  );
  assert( frequency.value() > 0  );
  assert( cycles > 0  );
  assert( detector_wavelength.value() > 0  );

  using namespace units::si;
  using math::construct::periodic_time_distribution;
  using thermal::equipment::detector::Measurements;
  using gTBC::gMeasure::get_signal_from_scope_file;
  
  auto const transient_DetectorSignal = get_signal_from_scope_file( dir, filename  );

  auto const steady_DetectorSignal = signal_DC_raw - signal_background ;

  auto const total_detectorSignal = steady_DetectorSignal + transient_DetectorSignal;

  auto const counts = transient_DetectorSignal.size();

  auto const referenceTime = periodic_time_distribution( frequency, cycles, counts ) ;
  
  return Measurements{ detector_wavelength, referenceTime, total_detectorSignal };
};


auto temperature_prediction( filesystem::directory const & dir ) -> void
{
  using std::cout;
  using std::string;

  using units::quantity;
  using units::si::dimensionless;
  using units::si::kelvin;
  using units::si::one_over_temperature;
  using units::si::temperature;
  using units::si::plane_angle;
  using units::si::radians;
  using units::pow;
  
  using algorithm::for_each;
  
  using math::functions::PeriodicData;
  using math::functions::PeriodicProperties;
  using math::curveFit::cosine;
  using thermal::pyrometry::twoColor::pyrometery_settings_file;
  using thermal::pyrometer::twoColor::temperatureSteady;
  using thermal::pyrometer::twoColor::signalRatio;
  using thermal::pyrometry::twoColor::normalizedDetectorMeasurements;
  using std::make_pair;

  auto const import = pyrometery_settings_file( dir, "twoColorPyro.xml" );

  auto const signalBackground = import.signalBackground;
  auto const wavelength1_nom = import.signal_DC_1.first ;
  auto const signalDC1_raw = import.signal_DC_1.second ;
  
  auto const wavelength2_nom = import.signal_DC_2.first ;
  auto const signalDC2_raw = import.signal_DC_2.second ;
  auto const wavelength_offset = import.wavelength_offset ;
  auto const gCoeff = import.gCoeff ;
  auto const temperoralFrequency = import.temperoralFrequency ;

  auto const cycles  = import.cycles;
  auto const filename_1  = import.filename_1;
  auto const filename_2  = import.filename_2;
  
  auto const signalDC1 = signalDC1_raw - signalBackground ;
  auto const signalDC2 = signalDC2_raw - signalBackground ;
  auto const wavelengthCorrected1 = wavelength1_nom + wavelength_offset;
  auto const wavelengthCorrected2 = wavelength2_nom + wavelength_offset;
  
  auto const SR = signalRatio( signalDC1, signalDC2 );


  auto const steadyTemperature_straight =
  temperatureSteady(
    gCoeff , SR, make_pair(wavelengthCorrected1, wavelengthCorrected2) ) ;

  
  auto const wavelength1 = wavelength1_nom + wavelength_offset ;
  auto const wavelength2 = wavelength2_nom + wavelength_offset ;
  
  auto const measurements_1 =
    measurementFactory( dir, filename_1, signalDC1_raw, signalBackground,
                        temperoralFrequency, cycles, wavelength1 ) ;
  
  auto const measurements_2 =
    measurementFactory( dir, filename_2, signalDC2_raw, signalBackground,
                        temperoralFrequency, cycles, wavelength2 ) ;
  
  
  
  auto const normalizedSRs =
  normalizedDetectorMeasurements( measurements_1, measurements_2, gCoeff );

  auto const myPeriodicData = PeriodicData< one_over_temperature >( normalizedSRs ) ;
  
  auto const initialConditions =
  PeriodicProperties<one_over_temperature>{
    myPeriodicData.initialEstimateOffset(),
    myPeriodicData.initialEstimateAmplitude(),
    temperoralFrequency, quantity<plane_angle>{ -1.6 * radians }
  } ;

  auto const fit_cosine = cosine( normalizedSRs, initialConditions );
  auto const fittedCosine = fit_cosine.fitted_cosine;
  

  auto const myFittedAmplitude = fittedCosine.get_amplitude() ;
  auto const myFittedOffset = fittedCosine.get_offset() ;
  
  auto const myFittedPhase = fittedCosine.get_phase() ;
  auto const steadyTemperature = quantity<dimensionless>{1} / myFittedOffset ;
  auto const transientTemperature = myFittedAmplitude * pow<2>( steadyTemperature );

  auto i = 0u;
  for_each( normalizedSRs.first , [&]( auto const & time )
  {
    cout << time << "\t"<< fittedCosine.evaluate( time ) << "\t" <<  normalizedSRs.second[i]  << "\n";
    i++;
  } ) ;
  
  cout << "\n" << units::engineering_prefix;
  cout << dir.pwd() << "\n";
  cout << "stage temperature\t\t" <<  quantity< temperature >( 473.15 * kelvin ) << "\n";
  cout << "signal frequency\t\t" << temperoralFrequency << "\n" << "\n";
  cout << "detector wavelength\t\t" << wavelength1 << "\n";
  cout << "detector wavelength\t\t" << wavelength2 << "\n" << "\n";
  cout << "steady temperature (DC) " << steadyTemperature_straight << "\n";

  cout << "steady temperature (total Signal)\t\t" << steadyTemperature << "\n";
  cout << "transient temperature(total Signal)\t" << transientTemperature << "\n";
  cout << "phase tempearture\t" << myFittedPhase << "\n";
}
  
} // namespace twoColorPyrometery
  
} // namespace investigations
