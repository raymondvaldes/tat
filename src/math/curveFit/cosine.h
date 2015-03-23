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
#include <iostream>
#include <cmath>
#include <utility>

#include "math/functions/cosine.h"
#include "math/estimation/lmdiff.hpp"
#include "math/functions/wrap2pi.h"
#include "math/coordinate_system/wrap_to_negPi_posPi.h"
#include "units.h"

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
struct cosine_fitting{

  functions::Cosine<T> fitted_cosine;
  units::quantity< units::si::dimensionless > R_square;
  
  
  cosine_fitting
  (
    functions::Cosine<T> const & fitted_cosine_,
    units::quantity< units::si::dimensionless > R_square_
  );

};
  

template< typename T >
auto cosine(
  std::pair<  std::vector< units::quantity<units::si::time> >,
              std::vector< units::quantity< T > >
  > const & input,
  functions::PeriodicProperties< T > const & initialConditions,
  units::quantity< units::si::plane_angle> const cosine_phase =
  units::quantity< units::si::plane_angle>::from_value(0)
)
noexcept -> functions::Cosine< T >
{
  auto const inputTime = input.first;
  auto const inputSignal = input.second;
    using std::generate;
    using std::vector;
    using std::function;
    using units::quantity;
    using units::si::plane_angle;
    using functions::PeriodicProperties;
    using functions::Cosine;
    using math::estimation::settings;
    using math::functions::wrap2pi;
    using units::si::radians;
  
  {
    assert( !inputTime.empty() ) ;
    assert( !inputSignal.empty() ) ;
    assert( inputTime.size() == inputSignal.size() ) ;
  }

  auto const CosineFactory = [ &cosine_phase  ]
  ( const double*x, const functions::PeriodicProperties< T > p_input )
  noexcept
  {
    auto updatedProperties = p_input ;
    
    updatedProperties.offset = quantity< T >::from_value( x[0] ) ;
    updatedProperties.amplitude = quantity< T >::from_value( x[1] ) ;

    using math::coordinate_system::wrap_to_negPi_posPi;
    auto const angle = x[2] * radians ;
    auto const phase_angle = wrap_to_negPi_posPi( angle )    ;
        
    updatedProperties.phase = phase_angle ;

    return Cosine<T>( updatedProperties ) ;
  };

  auto const minimizationEquation =
  [ &inputTime, &inputSignal, &initialConditions, &CosineFactory ]
  ( const double *x, double *fvec ) noexcept
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


  // this is to offset back the fitted phase by the phase of the curve
  unknownParameters[2] -= cosine_phase.value() ;
  return CosineFactory( unknownParameters.data(), initialConditions ) ;}

} // namespace curveFit

} // namespace math

#endif /* defined(__tat__math__curveFit__cosine__) */
