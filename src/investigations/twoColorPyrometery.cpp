//
//  2colorPyrometery.cpp
//  tat
//
//  Created by Raymond Valdes on 12/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include <cassert>

#include "assert/assertExtensions.h"

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
#include "tools/interface/xml.h"

namespace investigations{

namespace twoColorPyrometery{
  

struct Detector_measurement {

  units::quantity< units::si::time > reference_time;
  units::quantity< units::si::electric_potential > signal;
  
  Detector_measurement(){};
  
  Detector_measurement( units::quantity< units::si::time > const & timestamp_In,
                        units::quantity< units::si::electric_potential > const & signal_In )
  : reference_time( timestamp_In ), signal( signal_In )
  {
    assert_ge_zero( timestamp_In );
    assert_gt_zero( signal_In );
  };
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
    assert_gt_zero( wavelengthIn );
    assert_equal( referenceTime.size(), signals.size() );
    
    auto i = 0u;
    using algorithm::generate;
    generate( measurements, [&referenceTime, &signals, &i]() noexcept
    {
      auto const melissa = Detector_measurement{ referenceTime[i], signals[i] };
      ++i;
      return melissa;
    } );
    
  };
  
  auto size( void )
  const noexcept -> size_t
  {
    return measurements.size();
  };
  
  auto referenceTimes( void )
  const noexcept-> std::vector< units::quantity<units::si::time> >
  {
    using std::vector;
    using units::quantity;
    using units::si::time;
    using algorithm::generate;
    
    auto const count = size();
    
    auto const myMeasurements = measurements;
    auto times = vector< quantity< time > >{ count };
    auto i = 0;

    generate( times, [ &myMeasurements, &i]() noexcept
    {
      auto const time = myMeasurements[i].reference_time;
      ++i;
      return time ;
    } );
  
    return times;
  }
  
};


inline auto
periodic_time_distribution( units::quantity< units::si::frequency > const & frequency,
                            size_t const cycles,
                            size_t const count )
noexcept -> std::vector< units::quantity< units::si::time > >
{
  assert_gt_zero( cycles ) ;
  assert_gt_zero( count ) ;
  assert_gt_zero( frequency ) ;

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
auto normalizedSignalRatio_from_measurement(
  units::quantity<units::si::wavelength> const & first_w,
  units::quantity<units::si::electric_potential> const & first_signal,
  units::quantity<units::si::wavelength> const & second_w,
  units::quantity<units::si::electric_potential> const &  second_signal,
  units::quantity< units::si::dimensionless > const & gCoeff )
  noexcept -> units::quantity< units::si::one_over_temperature >
{
  assert_gt_zero(first_w);
  assert_gt_zero(second_w);
  assert_lt(first_w, second_w);
  
  assert_gt_zero(first_signal);
  assert_gt_zero(second_signal);
  assert_gt_zero(gCoeff);

  using thermal::pyrometer::twoColor::signalRatio;
  using thermal::pyrometer::twoColor::calibratedSignalRatio;
  using thermal::pyrometer::twoColor::normalizedSignalRatio;

  auto const SR = signalRatio(  first_signal , second_signal ) ;
  auto const gSR = calibratedSignalRatio( SR, gCoeff ) ;
  
  auto const normalizedSR = normalizedSignalRatio( gSR,first_w,second_w);
  
  return normalizedSR ;
}
  

inline
auto normalizedDetectorMeasurements(  Detector_measurements const & first,
                                      Detector_measurements const & second,
  units::quantity< units::si::dimensionless > const & gCoeff )
noexcept  ->  std::pair< std::vector< units::quantity< units::si::time > > ,
std::vector< units::quantity< units::si::one_over_temperature > > >
{
  assert_gt_zero( first.size() ) ;
  assert_gt_zero( second.size() );
  assert_gt_zero( gCoeff ) ;

  using std::vector;
  using std::make_pair;
  using units::quantity;
  using units::si::time;
  using units::si::one_over_temperature;
  using thermal::pyrometer::twoColor::signalRatio;
  using thermal::pyrometer::twoColor::calibratedSignalRatio;
  using thermal::pyrometer::twoColor::normalizedSignalRatio;
  using algorithm::generate;
  
  auto const count = first.size();
  auto normalizedSRs = vector< quantity<one_over_temperature> >( count ) ;
  
  auto i = 0u;
  auto const normalizeSR_generator = [&first, &second, &gCoeff, &i]() noexcept
  {
    auto const val =  normalizedSignalRatio_from_measurement(
      first.wavelength, first.measurements[i].signal ,
      second.wavelength, second.measurements[i].signal,  gCoeff  ) ;
    i++;
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

  auto const fileName_string = dir.abs( inputFileName ) ;
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
  assert( !filename.empty() );
  assert_gt_zero( signal_DC_raw );
  assert_ge_zero( signal_background );
  assert_gt_zero( frequency );
  assert_gt_zero( cycles );
  assert_gt_zero( detector_wavelength );

  using namespace units::si;

  auto const transient_DetectorSignal = get_signal_from_scope_file( dir, filename  );

  auto const steady_DetectorSignal = signal_DC_raw - signal_background ;

  auto const total_detectorSignal = steady_DetectorSignal + transient_DetectorSignal;

  auto const counts = transient_DetectorSignal.size();

  auto const referenceTime = periodic_time_distribution( frequency, cycles, counts ) ;
    
  return Detector_measurements{ detector_wavelength, referenceTime, total_detectorSignal };
};


  
  
auto run( filesystem::directory const & dir ) noexcept -> void
{
  using std::cout;

  using units::quantity;
  using units::si::time;
  using units::si::micrometers;
  using units::si::wavelength;
  using units::si::volts;
  using units::si::electric_potential;
  using units::si::dimensionless;
  using units::si::frequency;
  using units::si::kelvin;
  using units::si::one_over_temperature;
  using units::si::hertz;
  using units::si::temperature;
  using units::si::plane_angle;
  using units::si::radians;
  
  using thermal::pyrometer::twoColor::signalRatio;
  using thermal::pyrometer::twoColor::calibratedSignalRatio;
  using thermal::pyrometer::twoColor::normalizedSignalRatio;
  
  using math::functions::PeriodicData;
  using math::functions::PeriodicProperties;
  using math::curveFit::cosine;

  //// get my tree
  using tools::interface::getTreefromFile;
  using tools::interface::getItem;

  calculateCalibrationCoefficients( dir ) ;


  auto const filename = "twoColorPyro.xml";
  auto const fullpath = dir.abs( filename );
  auto const pt = getTreefromFile( fullpath ) ;
  auto const conjunto = std::string{"temperature_measurement."};
  auto const settings_branch = pt.get_child( conjunto + "settings" );
  
  auto const signalBackground_value  = settings_branch.get<double>( "signal_background" );
  auto const signalBackground = quantity<electric_potential> ( signalBackground_value  * volts ) ;
  
  auto const signalDC1_raw_value  = settings_branch.get<double>( "signal_DC_1" );
  auto const signalDC1_raw = quantity<electric_potential> ( signalDC1_raw_value  * volts ) ;
  
  auto const signalDC2_raw_value  = settings_branch.get<double>( "signal_DC_2" );
  auto const signalDC2_raw = quantity<electric_potential> ( signalDC2_raw_value  * volts ) ;

  auto const gCoeff_value  = settings_branch.get<double>( "calibration_coefficient" );
  auto const gCoeff = quantity<dimensionless> ( gCoeff_value ) ;

  auto const wavelength1_value  = settings_branch.get<double>( "wavelength1_nominal" );
  auto const wavelength1_nom = quantity<wavelength> ( wavelength1_value  * micrometers ) ;
  
  auto const wavelength2_value  = settings_branch.get<double>( "wavelength2_nominal" );
  auto const wavelength2_nom = quantity<wavelength> ( wavelength2_value  * micrometers ) ;

  auto const wavelength_offset_value  = settings_branch.get<double>( "wavelenth_offset" );
  auto const wavelength_offset = quantity<wavelength> ( wavelength_offset_value  * micrometers ) ;
  

  auto const frequency_value  = settings_branch.get<double>( "frequency" );
  auto const temperoralFrequency = quantity<frequency> ( frequency_value  * hertz ) ;
  
  auto const cycles  = settings_branch.get<size_t>( "count" );

  auto const filename_1  = settings_branch.get<std::string>( "file1" );
  auto const filename_2  = settings_branch.get<std::string>( "file2" );
  
  
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
    temperoralFrequency, quantity<plane_angle>{ 0 * radians }
  } ;

  auto const fittedCosine = cosine( normalizedSRs, initialConditions );

  auto const myFittedAmplitude = fittedCosine.get_amplitude() ;
  auto const myFittedOffset = fittedCosine.get_offset() ;
  auto const myFittedPhase = fittedCosine.get_phase() ;

  auto const steadyTemperature = quantity<dimensionless>{1} / myFittedOffset ;
  
  using units::pow;
  auto const transientTemperature = myFittedAmplitude * pow<2>( steadyTemperature );

  //cout << "steady tempertaure (straight) " << steadyTemperature_straight << "\n";
  
  cout << "\n" << units::engineering_prefix;
  cout << "stage temperature\t\t" <<  quantity< temperature >( 477 * kelvin ) << "\n";
  cout << "signal frequency\t\t" << temperoralFrequency << "\n" << "\n";
  cout << "detector wavelength\t\t" << wavelength1 << "\n";
  cout << "detector wavelength\t\t" << wavelength2 << "\n" << "\n";
  cout << "steady temperature\t\t" << steadyTemperature << "\n";
  cout << "transient tempearture\t" << transientTemperature << "\n";
  cout << "phase tempearture\t" << myFittedPhase << "\n";
  
  
  
} //function

} //namespace twoColorPyrometry

} //namespace investigations
