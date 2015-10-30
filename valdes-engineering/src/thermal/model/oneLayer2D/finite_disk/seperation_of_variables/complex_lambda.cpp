//
//  complex_lambda.cpp
//  tat
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/oneLayer2D/finite_disk/seperation_of_variables/complex_lambda.h"
#include <cmath>
#include <cassert>
#include <complex>

using namespace units;
using std::sqrt;
using std::complex;

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace seperation_of_variables{

auto complex_lambda
(
  Lambda const lambda,
  dimensionless::Thermal_penetration const l
) noexcept -> Complex_lambda
{
  assert( l > 0 ) ;
  assert( lambda > 0 );
  
  auto const i = quantity< si::dimensionless, complex<double> >( { 0, 1.0 } );
  auto const cmpl = sqrt( ( i / pow<2>(l) )  + pow<2>( lambda ) );
  
  return cmpl;
}

} // seperation_of_variables
} // finite_disk
} // oneLayer2d
} // model
} // thermal
