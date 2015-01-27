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

namespace math {

namespace curveFit {


struct propertiesToFit{
  const bool offset;
  const bool amplitude;
  const bool phase;
  const bool frequency;
  
  explicit propertiesToFit( const bool offsetIn, const bool amplitudeIn,
                            const bool phaseIn, const bool frequencyIn  )
                            : offset(offsetIn), amplitude( amplitudeIn ),
                              phase( phaseIn ), frequency( frequencyIn ) {}
};

template< typename T >
auto cosine( const std::vector< units::quantity< units::si::time > > &inputTime,
             const std::vector< units::quantity< T > > &inputSignal,
             const functions::PeriodicProperties< T > &initialConditions,
             const propertiesToFit fittingGuide =
             propertiesToFit{true, true, true, false} )
noexcept
-> functions::Cosine<T>
{

    using std::vector;
    using std::function;
    using units::quantity;
    using units::si::plane_angle;
    using functions::PeriodicProperties;
    using functions::Cosine;
    
  

  {
    assert( !inputTime.empty() ) ;
    assert( !inputSignal.empty() ) ;
    assert( inputTime.size() == inputSignal.size() ) ;
  }

  const auto CosineGenerator = [  ]
  ( const double*x, const functions::PeriodicProperties< T > &input ) noexcept
  -> functions::Cosine<T>
  {
    auto updatedProperties = PeriodicProperties<T>( input );
    
    updatedProperties.offset = quantity< T >::from_value( x[0] ) ;
    updatedProperties.amplitude = quantity< T >::from_value( x[1] ) ;
    updatedProperties.phase = quantity< plane_angle >::from_value( x[2] );

    return Cosine<T>( updatedProperties ) ;
  };

  auto minimizationEquation =
  [ &inputTime, &inputSignal, &initialConditions, &CosineGenerator ]
  ( const double *x, double *fvec ) noexcept
  {
    const auto myCosineFunction = CosineGenerator( x, initialConditions );
    const auto residual = [ & ]( const int i )
    {
      return ( myCosineFunction( inputTime[i] ) -  inputSignal[i] ).value();
    };

    using std::generate;
    int i(0);
    generate( fvec, fvec + inputTime.size() , [&](){ return residual(i++); } ) ;
    
  };

  auto parameters2Fit = vector<double>{
    initialConditions.offset.value(),
    initialConditions.amplitude.value(),
    initialConditions.phase.value() } ;
 
  const auto numberPoints2Fit =  inputTime.size() ;
  lmdif( minimizationEquation, numberPoints2Fit,
          parameters2Fit, math::estimation::settings{} ) ;

  return CosineGenerator( parameters2Fit.data(), initialConditions ) ;
};

} // namespace curveFit

} // namespace math

#endif /* defined(__tat__math__curveFit__cosine__) */
