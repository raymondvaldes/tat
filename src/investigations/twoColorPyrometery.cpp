//
//  2colorPyrometery.cpp
//  tat
//
//  Created by Raymond Valdes on 12/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "algorithm/algorithm.h"

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
  

  using std::generate;
  using std::transform;
  using std::vector;
  using std::log10;
  
  using std::cout;
  using std::endl;

  using units::quantity;
  using namespace units::si;
  using units::si::time;
  using units::si::constants::C2_wien;
  
  using thermal::analysis::initializePopTeawithExperimentalEmission;
  using thermal::analysis::Poptea;
  using thermal::pyrometer::twoColor::signalRatio;
  using thermal::pyrometer::twoColor::calibratedSignalRatio;
  using thermal::pyrometer::twoColor::normalizedSignalRatio;
  
  using math::functions::PeriodicData;
  using math::functions::PeriodicProperties;
  using math::curveFit::cosine;

auto run( const filesystem::directory &dir ) noexcept -> void
{
  {
    auto poptea = Poptea{
      initializePopTeawithExperimentalEmission( dir ) };
  
    auto transientDetectorSignal44 =
    poptea.loadTBDfile( dir,  std::string{ "graphite_400F_oneFreq_4.4_2.82843_7.dat" } ) ;

    auto transientDetectorSignal54 =
    poptea.loadTBDfile( dir,  std::string{ "graphite_400F_oneFreq_5.4_2.82843_8.dat" } ) ;

    const auto millivolts = milli*volts;
    const auto signalDCoffset1 = quantity<electric_potential>( 88.0 * millivolts );   /*graphite*/ /*predicted T_ss = 477 K */
    const auto signalDCoffset2 = quantity<electric_potential>( 112.0 * millivolts );  /*graphite*/

/*
/add thermocouple , use high temp epoxy [do this no matter what!!]
/also concern about the actual wavelength, do offset using CO2 absorption band

  Which samples do I want to run?  I want to do a handful of well characterized 
  ones like graphite, steel, use low conductivity metals. Use a sample as the 
  calibration.
  
  Make non-contact measurements using unknown color (get the transient field) 
  first!.
 
  Which TBCs?  Can I use the temperature information to make predictions of the 
  temperature field? How do I know the properties of the samples that I am 
  trying to solve for?

  Can I then use this to make temperature measurements?  Yes, by varying the 
  stage temperature or external temperature of the sample.
  
  What do I need?  I need to know the DC offest and we can get that by doing a 
  single blocked measurement and recording that data in wave filesnames (along 
  with the number of cycles).
  
  How do I deal with TBCs that are translucent without graphite coating?
  As long as temperature detected is close to the stage temperature then the 
  properties in the equation will not be temperature dependent. Maintain that 
  scenario.
  */
  
    algorithm::transform(
      transientDetectorSignal44,
      transientDetectorSignal44.begin(),
      [&]( auto &val) noexcept { return val + signalDCoffset1 ; }) ;

    algorithm::transform(
      transientDetectorSignal54,
      transientDetectorSignal54.begin(),
      [&]( auto &val) noexcept { return val + signalDCoffset2 ; } );

    const auto gCoeff = quantity< dimensionless >( 0.955943212775443 ); /*graphite at 400F*/

    const auto wavelength1 = quantity<length>( 4.4 * micrometers ) ;
    const auto wavelength2 = quantity<length>( 5.4 * micrometers ) ;


    const auto temperoralFrequency = quantity<frequency>( 2.82843 * hertz ) ;
    
    auto normalizedSRVector =
    vector<quantity<one_over_temperature>>( transientDetectorSignal44.size() );
    

    auto i = 0;
    const auto normalizeSR_function =
    [&]()
    {
      const auto SR = signalRatio( transientDetectorSignal44[i],
                                   transientDetectorSignal54[i] ) ;
      const auto gSR = calibratedSignalRatio( SR, gCoeff ) ;
      i++;
      
      return normalizedSignalRatio( gSR , wavelength1, wavelength2 ) ;
    };
    
    algorithm::generate( normalizedSRVector, normalizeSR_function ) ;
    
    const auto dataPoints = quantity< dimensionless > ( 2049 );
    const auto cycles = quantity< dimensionless >( 6 ) ;
    const auto period = quantity< dimensionless >(1) / temperoralFrequency;
    
    auto myTimeVector = vector< quantity< time > >( dataPoints.value(), 0 * seconds );
    {
      auto timeMeasurement = quantity< time > ( 0 * seconds ) ;
      const auto totalTime = cycles * period;
      const auto increment = totalTime / dataPoints;
      
      generate( myTimeVector.begin()+1 , myTimeVector.end(),
      [&]()
      {
        timeMeasurement += increment;
        return timeMeasurement;
      } ) ;
    }

    const auto angularFrequency =
      quantity< angular_frequency >( 2 * M_PI * radians * temperoralFrequency );
    
    const auto myPeriodicData =
      PeriodicData< one_over_temperature>( myTimeVector, normalizedSRVector ) ;
    
    
    const auto initialConditions =
    PeriodicProperties<one_over_temperature>(
      myPeriodicData.initialEstimateOffset(),
      myPeriodicData.initialEstimateAmplitude(),
      angularFrequency,
      quantity<plane_angle>( 0 * radians )
    ) ;

    const auto fittedCosine =
    math::curveFit::cosine<one_over_temperature>( myTimeVector, normalizedSRVector, initialConditions );

    const auto myFittedAmplitude = fittedCosine.get_amplitude() ;
    const auto myFittedOffset = fittedCosine.get_offset() ;
    const auto myFittedPhase = fittedCosine.get_phase() ;
  
    const auto steadyTemperature = quantity<dimensionless>(1) / myFittedOffset ;
    const auto transientTemperature = myFittedAmplitude * steadyTemperature * steadyTemperature ;

    
    cout << "\n" << units::engineering_prefix;
    cout << "stage temperature\t\t" <<  quantity< temperature >(477 * kelvin) << endl;
    cout << "signal frequency\t\t" << temperoralFrequency << endl << endl;
    cout << "detector wavelength\t\t" << wavelength1 << endl;
    cout << "detector wavelength\t\t" << wavelength2 << endl << endl;
    cout << "steady temperature\t\t" << steadyTemperature << endl;
    cout << "transient tempearture\t" << transientTemperature << endl;
    cout << "phase tempearture\t" << myFittedPhase << endl;
    
  }


  if(false)
  {
    using thermal::analysis::initializePopTeaAndLoadSimuEmission;
    auto poptea = Poptea{
      initializePopTeaAndLoadSimuEmission( dir ) };
    poptea.bestFit() ;
    cout << poptea.ppUnknownParameters() << "\n";
  }
  
} //function

} //namespace twoColorPyrometry

} //namespace investigations
