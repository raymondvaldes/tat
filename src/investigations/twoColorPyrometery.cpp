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

#include "units.h"

namespace investigations{
namespace twoColorPyrometery{
  
void run( const filesystem::directory &dir ) noexcept
{
  using thermal::analysis::Poptea;

  {
    using thermal::analysis::initializePopTeawithExperimentalEmission;
    auto poptea = Poptea{
      initializePopTeawithExperimentalEmission( dir ) };
      
      
    auto transientDetectorSignal44 =
    poptea.loadTBDfile( dir,  std::string{ "graphite_400F_4.4_2.82843_0.dat" } ) ;

    auto transientDetectorSignal54 =
    poptea.loadTBDfile( dir,  std::string{ "graphite_400F_5.4_2.82843_5.dat" } ) ;

    using units::quantity;
    using units::si::milli;
    using units::si::volts;
    using units::si::electric_potential;
    const auto signalDCoffset = quantity<electric_potential>( 50 * milli *volts );

    using std::transform;
    transform( transientDetectorSignal44.begin(),
               transientDetectorSignal44.end(),
               transientDetectorSignal44.begin(),
        [&]( auto &val) { return val + signalDCoffset ; } );
    
    transform( transientDetectorSignal54.begin(),
               transientDetectorSignal54.end(),
               transientDetectorSignal54.begin(),
        [&]( auto &val) { return val + signalDCoffset ; } );
    
    
    using units::si::meter;
    using units::si::constants::C2_wien;
    
    using std::log10;
    
    
    using units::si::dimensionless;
    const auto gCoeff = quantity< dimensionless >( 1.03 );
    
    using units::si::length;
    using units::si::micro;
    using units::si::meters;
    const auto micrometers = micro*meters;
    const auto wavelength1 = quantity<length>( 4.4 * micrometers ) ;
    const auto wavelength2 = quantity<length>( 5.4 * micrometers ) ;

    using units::si::angular_frequency;
    using units::si::hertz;
    using units::si::radians;
    using units::si::frequency;
    const auto myFrequency = quantity<frequency>( 2.82843 * hertz ) ;
    const auto angularFrequency = quantity<angular_frequency>( 2 * M_2_PI * radians * myFrequency ) ;
    
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
                                   transientDetectorSignal54[i] );
      const auto gSR = calibratedSignalRatio( SR, gCoeff ) ;
      
      normalizedSRVector.push_back( normalizedSignalRatio( gSR , wavelength1, wavelength2 ) ) ;
    }












  
  }

  
  
  
  

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
