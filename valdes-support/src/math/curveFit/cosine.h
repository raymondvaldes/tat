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
#include "math/estimation/constrained.hpp"
#include "math/estimation/lmdiff.hpp"
#include "math/functions/wrap2pi.h"
#include "math/coordinate_system/wrap_to_negPi_posPi.h"
#include "units.h"
#include "statistics/sum_of_squares/residuals.h"
#include "statistics/signal_processing/abs.h"

namespace math {
namespace curveFit {

using std::generate;
using std::vector;
using std::function;
using namespace units;

using functions::PeriodicProperties;
using functions::Cosine;
using math::functions::wrap2pi;
using math::estimation::x_limiter1;
using math::estimation::kx_limiter1;
using statistics::signal_processing::abs;

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
struct Cosine_fitting_results{

  functions::Cosine<T> fitted_cosine;
  int info;
  
  explicit Cosine_fitting_results
  (
    functions::Cosine<T> const & fitted_cosine_,
    int info_
  ) noexcept
  :
    fitted_cosine( fitted_cosine_ ),
    info( info_)
  {
  
  };

};
  

template< typename T >
auto cosine(
  std::pair<  std::vector< units::quantity< units::si::time > >,
              std::vector< units::quantity< T > >
  > const & input_raw,
  functions::PeriodicProperties< T > const & initialConditions_raw,
  units::quantity< units::si::plane_angle > const cosine_phase =
  units::quantity< units::si::plane_angle >::from_value(0)
)
noexcept -> Cosine_fitting_results< T >
{
  assert( cosine_phase.value() == 0 );

  auto const scaler = initialConditions_raw.offset.value();
  
  // scale function values
  auto input_scaled = input_raw;
  
  auto i = 0u;
  for( auto const s : input_scaled.second ) {
    input_scaled.second[i] = s /  scaler ;
    ++i;
  }
  
  // scale initialConditions
  auto initialConditions_scaled = initialConditions_raw;
  initialConditions_scaled.amplitude /= scaler;
  initialConditions_scaled.offset /= scaler;
  
  
  auto const input = input_scaled;
  auto const initialConditions = initialConditions_scaled;
  
  
  
  auto const inputTime = input.first;
  auto const inputSignal = input.second;

  {
    assert( !inputTime.empty() ) ;
    assert( !inputSignal.empty() ) ;
    assert( inputTime.size() == inputSignal.size() ) ;
    for( auto const t : inputTime ) {
      assert( isfinite( t ) );
    }
    for( auto const s : inputSignal ) {
      assert( isfinite( s ) ) ;
    }
  }
  
  
  
  auto unknownParameters = vector<double>{
    initialConditions.offset.value(),
    initialConditions.amplitude.value() ,
    initialConditions.phase.value()
  } ;
  
  auto const scalers = abs( unknownParameters );
  auto unknownParameters_scaled = vector<double> {
    unknownParameters[0] / scalers[0],
    unknownParameters[1] / scalers[1],
    unknownParameters[2] / scalers[2]
  };

  auto const CosineFactory = [&scalers]
  ( const double*x, functions::PeriodicProperties< T > const & p_input )
  noexcept
  {
    auto updatedProperties = p_input ;
    
    updatedProperties.offset = quantity< T >::from_value( x[0] * scalers[0] ) ;
    updatedProperties.amplitude = quantity< T >::from_value( x[1] * scalers[1] ) ;
    auto const angle = x[2] * scalers[2] * radians ;
        
    updatedProperties.phase = angle ;
    
    
    return Cosine<T>( updatedProperties ) ;
  };


  auto const minimizationEquation =
  [ &inputTime, &inputSignal, &initialConditions, &CosineFactory ]
  ( const double *x, double *fvec ) noexcept
  {
    auto const myCosineFunction = CosineFactory( x, initialConditions ) ;
    
    auto const residual = [ &myCosineFunction, &inputTime, &inputSignal ]
    ( int const i ) noexcept -> double
    {
      auto const model = myCosineFunction( inputTime[i] );
      auto const observation = inputSignal[i];
      
      return ( model -  observation ).value();
    };

    auto i = int(0);
    generate( fvec, fvec + inputTime.size() , [ &residual, &i ]() noexcept
    {
      auto const residual_value = residual(i) ;
      ++i;
      return residual_value;
    } ) ;
    
  };


 
  auto const numberPoints2Fit =  inputTime.size() ;
  
  auto settings = math::estimation::settings{};
  settings.set_relative_sum_square_error( 1e-16 );
  settings.set_relative_parameter_error( 1e-16 );
  settings.set_maximum_iterations( 1000000 );
  settings.set_initial_set_bound_factor( 1 );
  settings.set_error_of_fcn(1e-12 );
  settings.set_orthogonality_between_fvec_jacobian(1e-16);

  auto const info =
  lmdif( minimizationEquation, numberPoints2Fit, unknownParameters_scaled, settings );
  
  // this is to offset back the fitted phase by the phase of the curve
//  unknownParameters[2] -= cosine_phase.value() ;
  auto myFittedCosine =
  CosineFactory( unknownParameters_scaled.data(), initialConditions ) ;
  
  using math::coordinate_system::wrap_to_negPi_posPi ;
  auto const phase_angle = wrap_to_negPi_posPi( myFittedCosine.phase ) ;
  myFittedCosine.phase = phase_angle;
  
  myFittedCosine.offset *= scaler;
  myFittedCosine.amplitude *= scaler;

  auto const results = Cosine_fitting_results< T >( myFittedCosine, info );

  return results; ;
}

} // namespace curveFit
} // namespace math

#endif /* defined(__tat__math__curveFit__cosine__) */
