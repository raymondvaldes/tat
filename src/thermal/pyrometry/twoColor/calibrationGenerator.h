//
//  calibrationGenerator.h
//  tat
//
//  Created by Raymond Valdes_New on 2/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_calibrationGenerator_h
#define tat_calibrationGenerator_h

#include <algorithm>
#include <vector>
#include <utility>
#include "thermal/emission/spectrum.h"
#include "thermal/pyrometry/twoColor/calibrationCoefficient.h"

namespace thermal {

namespace pyrometry {

namespace twoColor {

template< typename T >
class calibrationGenerator {

private:
  emission::Spectrum<T> spectrum;

  auto extract_wavelength_pairs(
    units::quantity< units::si::wavelength > const & delta ) const noexcept
    -> std::vector< std::pair<  units::quantity< units::si::wavelength >,
                                units::quantity< units::si::wavelength > > >
  {
    using std::pair;
    using std::vector;
    using std::make_pair;
    using std::begin;
    using std::end;
    using std::for_each;
    
    using units::quantity;
    using units::si::wavelength;
    
    auto lambdaPairs =
      vector< pair< quantity< wavelength >, quantity< wavelength > > >(0);
  
    auto const push_back_lambdaPair = [&]
    ( auto const & signal ) noexcept
    {
      auto const first = signal.getElectromagneticWavelength() ;
      auto const second = first + delta ;

      auto const both_are_available = spectrum.if_available( second ) ;

      if( both_are_available ) {
        lambdaPairs.push_back( make_pair( first, second ) ) ;
      }
    };
    
    for_each( begin(spectrum), end(spectrum), push_back_lambdaPair );

    lambdaPairs.shrink_to_fit();
    
    return lambdaPairs;
  }
  
  auto signals_at_wavelengths(
    std::vector< std::pair< units::quantity< units::si::wavelength >,
                            units::quantity< units::si::wavelength > > >
                            const & lambdaPairs)
    const noexcept -> std::vector< std::pair< emission::Signal<T>,
                                              emission::Signal<T> > >
  {
    using std::pair;
    using std::vector;
    using std::make_pair;
    using std::begin;
    using std::end;
    using std::for_each;
    
    using emission::Signal;
    
    auto const N_signal_pairs = lambdaPairs.size();

    auto signalPairs = vector< pair< Signal<T>, Signal<T> > >();
    signalPairs.reserve( N_signal_pairs );
    
    for_each( begin( lambdaPairs ), end( lambdaPairs ),
    [&]( auto const &lambdaPair )
    {
        auto const first = spectrum.at_wavelength( lambdaPair.first ) ;
        auto const second = spectrum.at_wavelength( lambdaPair.second );
  
        signalPairs.push_back( make_pair( first, second ) ) ;
    } );
  
    return signalPairs;
  }
  
  auto evaluate_signals_for_calibration(
    std::vector< std::pair< emission::Signal<T>,
                            emission::Signal<T> > > const & signalPairs )
   const noexcept -> std::vector< units::quantity< units::si::dimensionless> >
   {
      using std::pair;
      using std::vector;
      using std::make_pair;
      using std::begin;
      using std::end;
      using std::for_each;
     
      using units::quantity;
      using units::si::dimensionless;
     
      auto const N_pairs = signalPairs.size();
   
      auto coefficients = vector< quantity< dimensionless> >( N_pairs ) ;
     
      for_each( begin( signalPairs ), end( signalPairs ),
      [&](auto const &signalPair)
      {
        using thermal::pyrometry::twoColor::calibrationCoefficient;
      
        auto const first = signalPair.first;
        auto const second = signalPair.second;
        
        auto const coefficient =
        calibrationCoefficient( first, second, spectrum.source_Temperature() ) ;
        
        coefficients.push_back( coefficient );
        std::cout << coefficient << "\n";
      } ) ;
     
      return coefficients;
   }

  auto compose_calibration_data(
  std::vector<  std::pair<
                            units::quantity< units::si::wavelength >,
                            units::quantity< units::si::wavelength > > >
                            const & lambdaPairs,
  std::vector< units::quantity< units::si::dimensionless> >
  const & coefficients )
  const noexcept
  -> std::vector<
      std::pair<
        std::pair<  units::quantity<units::si::wavelength>,
                    units::quantity< units::si::wavelength> > ,
        units::quantity< units::si::dimensionless >
      >
    >
  {
    using std::vector;
    using std::pair;
    using units::si::wavelength;
    using units::quantity;
    using units::si::dimensionless;
    using std::for_each;
    using std::make_pair;
    using std::begin;
    using std::end;
    
    auto size = coefficients.size();
    auto calibrationData = vector< pair<
      pair<  quantity<wavelength>, quantity<wavelength> > ,
      quantity< dimensionless >
                                 > >();
    calibrationData.reserve( size );
    
    auto i = 0;
    for_each( begin( coefficients ), end( coefficients ),
    [&]( auto const& coefficient )
    {

      auto calibrationPoint = make_pair( lambdaPairs[i], coefficients[i] ) ;
      calibrationData.push_back( calibrationPoint ) ;
      ++i;
    } ) ;
    return calibrationData;
  }

public:
  explicit
  calibrationGenerator( emission::Spectrum<T> const & spectrumInput )
  noexcept
  : spectrum(spectrumInput)
  {}

  auto coefficientsAt( units::quantity< units::si::wavelength > const & delta )
  const noexcept
  -> std::vector<
      std::pair<
        std::pair<  units::quantity<units::si::wavelength>,
                    units::quantity< units::si::wavelength> > ,
        units::quantity< units::si::dimensionless >
      >
    >
  {
    auto const lambdaPairs = extract_wavelength_pairs( delta );
    
    auto const signalPairs = signals_at_wavelengths( lambdaPairs );
    
    auto const coefficients = evaluate_signals_for_calibration( signalPairs ) ;
    
    auto const output = compose_calibration_data( lambdaPairs, coefficients ) ;
    
    return output ;
  }

};

} // namespace twoColor

} // namespace pyrometry

} // namespace thermal

#endif
