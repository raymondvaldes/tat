//
//  2colorPyrometery.cpp
//  tat
//
//  Created by Raymond Valdes on 12/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include <cassert>

#include "algorithm/algorithm.h"

#include "investigations/twoColorPyrometery.h"
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/poptea_initialize.h"

#include "thermal/pyrometry/twoColor/normalizedSignalRatio.h"
#include "thermal/pyrometry/twoColor/calibratedSignalRatio.h"
#include "thermal/pyrometry/twoColor/signalRatio.h"
#include "math/functions/periodicData.h"
#include "math/curveFit/cosine.h"

#include "tools/interface/import/columnData.h"


#include "units.h"

#include "investigations/twoColorPyrometery/calculateCalibrationCoefficients.h"
#include "algorithm/vector/stringToQuantity.h"
#include "algorithm/vector/repeatElements.h"

namespace investigations{

namespace twoColorPyrometery{
  

struct Detector_measurement {

  units::quantity< units::si::time > reference_time;
  units::quantity< units::si::electric_potential > signal;
  
  Detector_measurement(){};
  
  Detector_measurement( units::quantity< units::si::time > const & timestamp_In,
                        units::quantity< units::si::electric_potential > const & signal_In )
  : reference_time( timestamp_In ), signal( signal_In ) {};
};

struct Detector_measurements{

  units::quantity<units::si::wavelength> wavelength;
  std::vector< Detector_measurement > measurements;
  
  Detector_measurements(
    units::quantity<units::si::wavelength> const & wavelengthIn,
    std::vector< units::quantity< units::si::time> > referenceTime,
    std::vector< units::quantity< units::si::electric_potential > > const & signals )
    : wavelength( wavelengthIn), measurements( signals.size() )
  {
    using std::vector;
  
    auto i = 0u;
    using algorithm::for_each;

    using algorithm::generate;
    generate( measurements, [&referenceTime, &signals, &i]() noexcept
    {
      auto const melissa = Detector_measurement{ referenceTime[i], signals[i]};
      ++i;
      return melissa;
    } );
  };
  
  auto size( void ) const noexcept -> size_t { return measurements.size(); };
  
};


inline auto
periodic_time_distribution( units::quantity< units::si::frequency > const & frequency,
                            size_t const cycles,
                            size_t const count )
noexcept -> std::vector< units::quantity< units::si::time > >
{
  assert( cycles > 0) ;
  assert( count > 0 ) ;
  assert( frequency.value() > 0 ) ;

  using units::quantity;
  using units::si::dimensionless;
  using units::si::time;
  using units::si::seconds;
  
  using std::vector;
  using std::generate;
  using std::begin;
  using std::end;

  auto const period = quantity< dimensionless >( cycles  ) / frequency;
  auto const increment = period / quantity<dimensionless>(count);
  auto const starting_time = 0 * seconds ;
  
  auto time_distribution = vector< quantity< time > >( count, starting_time );
  
  auto scratch = quantity< time > ( starting_time ) ;
  generate( begin( time_distribution ) + 1 , end( time_distribution ), [&]()
  {
    scratch += increment;
    return scratch;
  } ) ;
  
  return time_distribution;
}

inline
auto normalizedDetectorMeasurements(  Detector_measurements first,
  Detector_measurements second, units::quantity< units::si::dimensionless > gCoeff )
  noexcept  ->  std::pair< std::vector< units::quantity< units::si::time > > ,
  std::vector< units::quantity< units::si::one_over_temperature > > >
{
  using std::vector;
  using std::make_pair;
  using units::quantity;
  using units::si::one_over_temperature;
  using thermal::pyrometer::twoColor::signalRatio;
  using thermal::pyrometer::twoColor::calibratedSignalRatio;
  using thermal::pyrometer::twoColor::normalizedSignalRatio;
  using algorithm::generate;
  
  auto const count = first.size();
  auto normalizedSRs = vector< quantity<one_over_temperature> >( count ) ;
  
  auto i = 0u;
  auto const normalizeSR_generator = [&]() noexcept
  {
    auto const SR = signalRatio(  first.measurements[i].signal,
                                  second.measurements[i].signal ) ;
    auto const gSR = calibratedSignalRatio( SR, gCoeff ) ;
    i++;
    
    return normalizedSignalRatio( gSR , first.wavelength , second.wavelength ) ;
  } ;
  
  generate( normalizedSRs, normalizeSR_generator ) ;

  i = 0;
  auto times = std::vector< units::quantity<units::si::time> >{count};
  generate( times, [&first, &i]() noexcept {
    auto val = first.measurements[i].reference_time;
    ++i;
    return val ;
  } );

  return make_pair( times, normalizedSRs ) ;
}


inline auto get_signal_from_scope_file( filesystem::directory const & dir,
                                        std::string const & inputFileName )
-> std::vector< units::quantity<units::si::electric_potential >>
{
  assert( !inputFileName.empty() );

  using tools::interface::import::columnData;
  using units::quantity;
  using units::si::electric_potential;
  using units::si::millivolts;
  using algorithm::vector::stringToQuantity;

  auto const fileName_string = dir.abs( inputFileName + ".dat"  );
  auto const myData = columnData{ fileName_string } ;
  
  auto const raw_signal_column = 3 ;
  auto const list_strings = myData.getColumn( raw_signal_column ) ;
  
  auto const raw_detector_signals =
  stringToQuantity< electric_potential >( list_strings, millivolts  ) ;
  
  return raw_detector_signals;
}

inline auto
measurementFactory( filesystem::directory const & dir,
  std::string const& filename,
  units::quantity< units::si::electric_potential > const & signal_DC_raw,
  units::quantity< units::si::electric_potential > const & signal_background,
  units::quantity< units::si::frequency > const & frequency,
  size_t const cycles,
  units::quantity< units::si::wavelength> const & detector_wavelength )
noexcept -> Detector_measurements
{
  using namespace units::si;

  auto const transient_DetectorSignal = get_signal_from_scope_file( dir, filename  );

  auto const counts = transient_DetectorSignal.size();

  auto const steady_DetectorSignal = signal_DC_raw - signal_background ;

  auto const total_detectorSignal = steady_DetectorSignal + transient_DetectorSignal;

  auto const referenceTime = periodic_time_distribution( frequency, cycles, counts ) ;
    
  return Detector_measurements{ detector_wavelength, referenceTime, total_detectorSignal };
};

  using std::for_each;
  using std::begin;
  using std::end;
  using std::generate;
  using std::transform;
  using std::vector;
  using std::log10;
  
  using std::cout;
  using std::endl;

  using units::quantity;
  using namespace units::si;
  using units::si::time;
  using units::si::wavelength;
  using units::si::constants::C2_wien;
  
  using thermal::analysis::initializePopTeawithExperimentalEmission;
  using thermal::analysis::Poptea;
  using thermal::pyrometer::twoColor::signalRatio;
  using thermal::pyrometer::twoColor::calibratedSignalRatio;
  using thermal::pyrometer::twoColor::normalizedSignalRatio;
  
  using math::functions::PeriodicData;
  using math::functions::PeriodicProperties;
  using math::curveFit::cosine;
  using algorithm::generate;

  
auto run( filesystem::directory const & dir ) noexcept -> void
{
    using math::curveFit::cosine;


  calculateCalibrationCoefficients( dir ) ;
  
    auto const signalBackground = quantity<electric_potential> ( 3.403  * volts ) ;
    auto const signalDC1_raw = quantity<electric_potential>(  3.63  * volts );
    auto const signalDC2_raw = quantity<electric_potential>(  3.59  * volts );

    
    auto const gCoeff = quantity< dimensionless >( 1.305 ) ; /*graphite at 400F*/
    auto const wavelength1 = quantity< wavelength >( 3.837130694 * micrometers ) ;
    auto const wavelength2 = quantity< wavelength >( 4.837130694 * micrometers ) ;
    auto const temperoralFrequency = quantity< frequency >( 2.82843 * hertz ) ;
    auto const cycles = 6;
    auto const filename_1 = "graphite_400F_jan28_v2_5.4_2.82843_10";
    auto const filename_2 = "graphite_400F_jan28_v2_4.4_2.82843_4";

  {
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
      temperoralFrequency, quantity<plane_angle>{ 0 * radians }
    } ;

    auto const fittedCosine = cosine( normalizedSRs, initialConditions );

    auto const myFittedAmplitude = fittedCosine.get_amplitude() ;
    auto const myFittedOffset = fittedCosine.get_offset() ;
    auto const myFittedPhase = fittedCosine.get_phase() ;
  
    auto const steadyTemperature = quantity<dimensionless>{1} / myFittedOffset ;
    auto const transientTemperature = myFittedAmplitude * steadyTemperature * steadyTemperature ;

    
    cout << "\n" << units::engineering_prefix;
    cout << "stage temperature\t\t" <<  quantity< units::si::temperature >( 477 * kelvin ) << endl;
    cout << "signal frequency\t\t" << temperoralFrequency << endl << endl;
    cout << "detector wavelength\t\t" << wavelength1 << endl;
    cout << "detector wavelength\t\t" << wavelength2 << endl << endl;
    cout << "steady temperature\t\t" << steadyTemperature << endl;
    cout << "transient tempearture\t" << transientTemperature << endl;
    cout << "phase tempearture\t" << myFittedPhase << endl;
    
  }
  
} //function

} //namespace twoColorPyrometry

} //namespace investigations
