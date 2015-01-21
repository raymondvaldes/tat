//
//  2colorPyrometery.cpp
//  tat
//
//  Created by Raymond Valdes on 12/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery.h"
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/poptea_initialize.h"

#include "thermal/pyrometry/twoColor/normalizedSignalRatio.h"
#include "thermal/pyrometry/twoColor/calibratedSignalRatio.h"
#include "thermal/pyrometry/twoColor/signalRatio.h"
#include "math/functions/periodicData.h"
#include "math/curveFit/cosine.h"

#include "units.h"

namespace investigations{
namespace twoColorPyrometery{
  
auto run( const filesystem::directory &dir ) noexcept -> void
{
  using thermal::analysis::Poptea;

  {
    using thermal::analysis::initializePopTeawithExperimentalEmission;
    auto poptea = Poptea{
      initializePopTeawithExperimentalEmission( dir ) };
    
    auto transientDetectorSignal44 =
    poptea.loadTBDfile( dir,  std::string{ "graphite_400F_4.4_2.82843_4.dat" } ) ;

    auto transientDetectorSignal54 =
    poptea.loadTBDfile( dir,  std::string{ "graphite_400F_5.4_2.82843_9.dat" } ) ;

    using units::quantity;
    using units::si::milli;
    using units::si::volts;
    using units::si::electric_potential;
    const auto signalDCoffset1 = quantity<electric_potential>( 77.42 * milli *volts );
    const auto signalDCoffset2 = quantity<electric_potential>( 94.457 * milli *volts );

    using std::transform;
    transform( transientDetectorSignal44.begin(),
               transientDetectorSignal44.end(),
               transientDetectorSignal44.begin(),
        [&]( auto &val) { return val + signalDCoffset1 ; } );
    
    transform( transientDetectorSignal54.begin(),
               transientDetectorSignal54.end(),
               transientDetectorSignal54.begin(),
        [&]( auto &val) { return val + signalDCoffset2 ; } );
    
    
    using units::si::meter;
    using units::si::constants::C2_wien;
    
    using std::log10;
    
    
    using units::si::dimensionless;
    const auto gCoeff = quantity< dimensionless >( 0.955943212775443 );
    
    using units::si::length;
    using units::si::micro;
    using units::si::meters;
    using units::si::milli;
    using units::si::seconds;
    using units::si::time;
    const auto micrometers = micro*meters;
    const auto wavelength1 = quantity<length>( 4.4 * micrometers ) ;
    const auto wavelength2 = quantity<length>( 5.4 * micrometers ) ;

    using units::si::angular_frequency;
    using units::si::hertz;
    using units::si::radians;
    using units::si::frequency;
    const auto temperoralFrequency = quantity<frequency>( 2.82843 * hertz ) ;
    
    using thermal::pyrometer::twoColor::normalizedSignalRatio;

    using std::vector;
    using units::si::one_over_temperature;
    auto normalizedSRVector =
    vector<quantity<one_over_temperature>>();
    
    for( size_t i = 0; i < transientDetectorSignal44.size(); ++i)
    {
      using thermal::pyrometer::twoColor::signalRatio;
      using thermal::pyrometer::twoColor::calibratedSignalRatio;

      const auto SR = signalRatio( transientDetectorSignal44[i],
                                   transientDetectorSignal54[i] ) ;
      const auto gSR = calibratedSignalRatio( SR, gCoeff ) ;
      
      normalizedSRVector.push_back( normalizedSignalRatio( gSR , wavelength1, wavelength2 ) ) ;
      
      
    }

    
    


    const auto dataPoints = quantity<dimensionless> ( 2049 );
    const auto cycles = quantity<dimensionless>( 6 ) ;
    auto myTimeVector = vector<quantity<units::si::time>>( dataPoints );
    const auto period = quantity<units::si::dimensionless>(1) / temperoralFrequency;
    
    auto timeMeasurement = quantity<time> ( 0 * seconds ) ;
    const auto totalTime = cycles * period;
    const auto increment = totalTime / dataPoints;
    for( auto val :  myTimeVector )
    {
      val = timeMeasurement;
      timeMeasurement += increment;
    }


    const auto angularFrequency = quantity<angular_frequency>( 2 * M_2_PI * radians * temperoralFrequency ) ;
  
    using math::functions::PeriodicData;
    auto myPeriodicData = PeriodicData<units::si::one_over_temperature>( myTimeVector, normalizedSRVector ) ;
    
    
    
    const auto offset = myPeriodicData.initialEstimateOffset() ;
    const auto amplitude = myPeriodicData.initialEstimateAmplitude() ;
    const auto phase = quantity<units::si::plane_angle>( 0 * radians );
    const auto omega = angularFrequency;
    auto initialConditions =
    math::functions::PeriodicProperties<one_over_temperature>( offset, amplitude, omega, phase ) ;


    using namespace math::curveFit;
    auto fittedCosine =
    math::curveFit::cosine<one_over_temperature>( myTimeVector, normalizedSRVector, initialConditions );

    const auto myFittedAmplitude = fittedCosine.get_amplitude();
    const auto myFittedOffset = fittedCosine.get_offset();
  
    const auto steadyTemperature = quantity<dimensionless>(1) / myFittedOffset;
    const auto transientTemperature = myFittedAmplitude * steadyTemperature * steadyTemperature;
    
    
    using std::cout;
    using std::endl;
    
    cout << "\n" << units::engineering_prefix;
    cout << "stage temperature\t" <<  quantity<units::si::temperature>(477 * units::si::kelvin) << endl;
    cout << "signal frequency\t" << temperoralFrequency << endl;
    cout << "detector wavelength\t" << wavelength1 << endl;
    cout << "detector wavelength\t" << wavelength2 << endl;
    cout << "steady temperature offset\t" << steadyTemperature << endl;
    cout << "transient tempearture\t" << transientTemperature << endl;
  }
  
  

  if(false)
  {
    using thermal::analysis::initializePopTeaAndLoadSimuEmission;
    auto poptea = Poptea{
      initializePopTeaAndLoadSimuEmission( dir ) };
    poptea.bestFit() ;
    std::cout << poptea.ppUnknownParameters() << "\n";
  }
  
} //function

} //namespace twoColorPyrometry

} //namespace investigations
