//
//  complex_lambda.h
//  tat
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef complex_lambda_h_101815
#define complex_lambda_h_101815

#include "units.h"
#include "thermal/model/oneLayer2D/finite_disk/dimensionless/thermal_penetration.h"
#include "thermal/model/oneLayer2D/finite_disk/seperation_of_variables/lambda.h"
#include <complex>

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace seperation_of_variables{

using Complex_lambda =
  units::quantity< units::si::dimensionless, std::complex<double> >;

auto complex_lambda
(
  Lambda const lambda,
  dimensionless::Thermal_penetration const l
) noexcept -> Complex_lambda;

} // seperation_of_variables
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* complex_lambda_h */
