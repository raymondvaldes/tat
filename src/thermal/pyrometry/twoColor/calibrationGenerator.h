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

public:
  explicit
  calibrationGenerator( emission::Spectrum<T> const & spectrumInput )
  noexcept
  : spectrum(spectrumInput)
  {}

  auto coefficientsAt( units::quantity< units::si::wavelength > const & delta )
  const noexcept
  -> std::vector< units::quantity< units::si::dimensionless> >
  {
    using std::vector;
    using std::begin;
    using std::pair;
    using std::make_pair;
    using std::end;
    using std::for_each;
  

    // loop through the spectrum where it checks if the value + delta is a valid point
    //if it is then it can push back the info to a new container
    // new container stores the two signals at ( pt1, pt1+delta)
    // then i can do analysis on the new container
    
    auto lambdaPairs =
      vector<
        pair<
          units::quantity< units::si::wavelength >,
          units::quantity< units::si::wavelength >
          >
      >(0);
  
    //save available
    auto const push_back_lambdaPair = [&]( auto const & val) {
      auto const first = val.getElectromagneticWavelength() ;
      auto const second = first + delta ;

      auto const both_are_available = spectrum.if_available( second ) ;

      if( both_are_available ) {
        lambdaPairs.push_back( make_pair( first, second ) ) ;
      }
    };
    
    for_each( begin(spectrum), end(spectrum), push_back_lambdaPair );
    auto const N_signal_pairs = lambdaPairs.size();

    // container that has the two signals based on the wavelenghts lambda
    auto signalPairs =
      vector<
        pair< emission::Signal<T>, emission::Signal<T> >
      >();
    signalPairs.reserve( N_signal_pairs );
    
    for_each( begin(lambdaPairs), end(lambdaPairs),
    [&]( auto const &lambdaPair )
    {
        auto const first = spectrum.at_wavelength( lambdaPair.first ) ;
        auto const second = spectrum.at_wavelength( lambdaPair.second );
  
        signalPairs.push_back( make_pair( first, second ) ) ;
    } );
    
    // populate vector
    auto coefficients =
    vector< units::quantity< units::si::dimensionless> >( N_signal_pairs ) ;
    
    for_each( begin(signalPairs), end( signalPairs ),
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

};

} // namespace twoColor

} // namespace pyrometry

} // namespace thermal

#endif
