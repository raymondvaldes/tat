//
//  Kappa.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/two_layer/dimensionless/Kappa.h"

using std::complex;
using namespace units;

namespace thermal {

namespace model {

namespace twoLayer {

namespace dimensionless {

auto Kappa( units::quantity< units::si::dimensionless > const omega )
noexcept -> units::quantity< units::si::dimensionless, complex< double > >
{
  auto const i_imag = complex< double >( 0, 1 ) ;
  auto const i_non = quantity< si::dimensionless, complex< double > >( i_imag ) ;
  auto const k = sqrt( i_non * omega ) ;

  return k;
}
  
} // namespace dimensionless
  
} // namespace twoLayer
  
} // namespace model
  
} // namespace thermal
