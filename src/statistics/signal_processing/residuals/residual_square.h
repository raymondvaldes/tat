//
//  residual_square.h
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_statistics_signal_processing_residuals_residual_square_h
#define tat_statistics_signal_processing_residuals_residual_square_h

#include <cassert>
#include <cmath>

#include "units.h"
#include "statistics/signal_processing/residuals/residual.h"

namespace statistics{
namespace signal_processing{

template< typename T >
auto residual_square(
  units::quantity< T > const observation,
  units::quantity< T > const model
) noexcept
{
  using std::isfinite;
  using namespace units;
  
  assert( isfinite( observation.value() ) );
  assert( isfinite( model.value() ) );
  
  auto const rs = pow<2>( residual( observation, model ) );
  
  return rs;
}

template< typename T >
auto residual_square( T const observation, T const model ) noexcept
{
  using std::isfinite;
  using std::pow;
  
  assert( isfinite( observation ) );
  assert( isfinite( model ) );
  
  auto const rs = pow( residual( observation, model ) , 2 );
  
  return rs;
}

}
}

#endif
