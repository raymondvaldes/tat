//
//  cosine.h
//  tat
//
//  Created by Raymond Valdes on 1/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__math__curveFit__cosine__
#define __tat__math__curveFit__cosine__

#include <vector>
#include <cassert>
#include <algorithm>
#include "math/functions/cosine.h"
#include "math/estimation/lmdiff.hpp"
#include "math/functions/wrap2pi.h"

namespace math {

namespace curveFit {


struct propertiesToFit{
  const bool offset;
  const bool amplitude;
  const bool phase;
  const bool frequency;
  
  constexpr explicit
  propertiesToFit( const bool offsetIn, const bool amplitudeIn,
                   const bool phaseIn, const bool frequencyIn  )
  noexcept
  : offset(offsetIn), amplitude( amplitudeIn ),
    phase( phaseIn ), frequency( frequencyIn ) {}

};
  

template< typename T >
auto cosine( const std::vector< units::quantity< units::si::time > > &inputTime,
             const std::vector< units::quantity< T > > &inputSignal,
             const functions::PeriodicProperties< T > &initialConditions,
             const propertiesToFit fittingGuide =
             propertiesToFit{true, true, true, false} )
noexcept -> functions::Cosine<T>
{
    using std::generate;
    using std::vector;
    using std::function;
    using units::quantity;
    using units::si::plane_angle;
    using functions::PeriodicProperties;
    using functions::Cosine;
    using math::estimation::settings;
    using math::functions::wrap2pi;
  
  {
    assert( !inputTime.empty() ) ;
    assert( !inputSignal.empty() ) ;
    assert( inputTime.size() == inputSignal.size() ) ;
  }

  auto const CosineFactory = [  ]
  ( const double*x, const functions::PeriodicProperties< T > &input )
  noexcept
  {
    auto updatedProperties = input ;
    
    updatedProperties.offset = quantity< T >::from_value( x[0] ) ;
    updatedProperties.amplitude = quantity< T >::from_value( x[1] ) ;
    
    auto const phase_angle = x[2] * units::si::radians;
    updatedProperties.phase = phase_angle ;
    
    updatedProperties.phase = wrap2pi( phase_angle ) ;

    return Cosine<T>( updatedProperties ) ;
  };

  auto const minimizationEquation =
  [ &inputTime, &inputSignal, &initialConditions, &CosineFactory ]
  ( const double *x, double *fvec )
  noexcept
  {
    auto const myCosineFunction = CosineFactory( x, initialConditions );
    
    auto const residual = [ & ]( const int i )
    {
      return ( myCosineFunction( inputTime[i] ) -  inputSignal[i] ).value();
    };

    auto i = 0;
    generate( fvec, fvec + inputTime.size() , [&](){ return residual(i++); } ) ;
    
  };

  auto unknownParameters = vector<double>{
    initialConditions.offset.value(),
    initialConditions.amplitude.value(),
    initialConditions.phase.value() } ;
 
  auto const numberPoints2Fit =  inputTime.size() ;
  
  lmdif( minimizationEquation, numberPoints2Fit, unknownParameters, settings{});

  return CosineFactory( unknownParameters.data(), initialConditions ) ;
};


template< typename T >
auto cosine(  std::pair< std::vector< units::quantity<units::si::time> >,
              std::vector< units::quantity< T > > > const & input,
              functions::PeriodicProperties< T > const & initialConditions)
noexcept -> functions::Cosine<T>
{
  return cosine( input.first, input.second, initialConditions );
}

} // namespace curveFit

} // namespace math

#endif /* defined(__tat__math__curveFit__cosine__) */
