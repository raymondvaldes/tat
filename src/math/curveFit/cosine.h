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
#include "math/functions/cosine.h"
#include "math/estimation/parameterestimation.hpp"
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
             const functions::PeriodicProperties< T > initialConditions,
             const propertiesToFit fittingGuide =
             propertiesToFit{true, true, true, false} )
noexcept
-> functions::Cosine<T>
{
  math::estimation::settings Settings;
  
  int dataPointsToFit = inputTime.size();

  const auto CosineGenerator = [  ]
  ( double*x, const functions::PeriodicProperties< T > &initialConditions )
  -> functions::Cosine<T>
  {
    using units::quantity;
    using units::si::plane_angle;

    using functions::PeriodicProperties;
    auto updatedProperties = PeriodicProperties<T>( initialConditions );
    
    updatedProperties.offset = quantity< T >::from_value( x[0] ) ;
    updatedProperties.amplitude = quantity< T >::from_value( x[1] ) ;
    updatedProperties.phase = quantity< plane_angle >::from_value( x[2] );

    using functions::Cosine;
    return Cosine<T>( updatedProperties ) ;
  };

  using std::function;
  function<void ( double*, double* )> fcn =
  [ &inputTime, &inputSignal, &initialConditions, &CosineGenerator ]
  ( double *x, double *fvec )
  {
    const auto myCosineFunction = CosineGenerator( x, initialConditions );

    for( int i = 0 ; i < inputTime.size() ; ++i )
    {
      const auto val = myCosineFunction( inputTime[i] ) -  inputSignal[i] ;
      fvec[i] = val.value() ;
    }
  };

  using std::vector;
  vector<double> fittingVector = {
    initialConditions.offset.value(),
    initialConditions.amplitude.value(),
    initialConditions.phase.value() } ;
 
  lmdif( fcn, dataPointsToFit, fittingVector, Settings ) ;

  return CosineGenerator( fittingVector.data(), initialConditions ) ;
};

} // namespace curveFit

} // namespace math

#endif /* defined(__tat__math__curveFit__cosine__) */
