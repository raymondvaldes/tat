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
    using std::begin;
    using std::end;
    using std::for_each;
  
    //determine size
    auto N = 0;
    
    auto const min = spectrum.min() ;
    auto const max = spectrum.max() ;


    // loop through the spectrum where it checks if the value + delta is a valid point
    //if it is then it can push back the info to a new container
    // new container stores the two signals at ( pt1, pt1+delta)
    // then i can do analysis on the new container
    auto myWavelengths = std::make_pair( min, max );
    

    auto
    pass = spectrum.if_available( min.getElectromagneticWavelength() ) ;
    pass = spectrum.if_available( min.getElectromagneticWavelength() ) ;
  
    for_each( begin(spectrum), end(spectrum), []( auto const & val){
      std::cout << "hello, world!\n";
    } );
    
    
    
    // populate vector
    auto coefficients =
    std::vector< units::quantity< units::si::dimensionless> >( N );
    
    
    
    return coefficients;
  }

};

} // namespace twoColor

} // namespace pyrometry

} // namespace thermal

#endif
