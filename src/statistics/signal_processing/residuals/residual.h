//
//  residual.h
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_statistics_signal_processing_residuals_residual_h
#define tat_statistics_signal_processing_residuals_residual_h

#include <cassert>
#include <cmath>

namespace statistics{
namespace signal_processing{

template< typename T >
auto residual( T const observation, T const model ) noexcept
{
  using std::isfinite;
  
  assert( isfinite( observation ) );
  assert( isfinite( model ) );
  
  auto const residual_value = observation - model;
  
  return residual_value;
}

}
}

#endif
