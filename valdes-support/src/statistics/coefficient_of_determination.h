//
//  coefficient_of_determination.h
//  tat
//
//  Created by Raymond Valdes_New on 3/16/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_coefficient_of_determination_h
#define tat_coefficient_of_determination_h

#include <vector>

#include "units.h"
#include "statistics/sum_of_squares/total.h"
#include "statistics/sum_of_squares/residuals.h"

namespace statistics {

namespace sum_of_squares {

template< typename T >
auto coefficient_of_determination
(
  std::vector< units::quantity< T > > const & model_values,
  std::vector< units::quantity< T > > const & predicted_values
)
{
//  auto const SS_residuals = residuals( model_values, predicted_values );
//  auto const SS_total = total( model_values, predicted_values );
//  
//  auto const R_square = 1 - SS_residuals / SS_total ;
  auto const R_square = 1 ;

  return R_square;
}
  
} // namespace sum_of_squares
  
} // namespace statistics

#endif
