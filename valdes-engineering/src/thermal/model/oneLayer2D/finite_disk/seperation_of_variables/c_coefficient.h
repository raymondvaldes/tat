//
//  c_coefficient.h
//  tat
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef c_coefficient_h_101815
#define c_coefficient_h_101815

#include "units.h"
#include "lambda.h"
#include "complex_lambda.h"
#include <complex>

#include "thermal/model/oneLayer2d/finite_disk/disk/biot.h"
#include "thermal/model/oneLayer2d/finite_disk/laser_beam/modulation_depth.h"
#include "thermal/model/oneLayer2d/finite_disk/disk/dimensionless/thickness.hpp"
#include "thermal/model/oneLayer2d/finite_disk/disk/dimensionless/radius.hpp"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace seperation_of_variables{

using C_coefficient =
   units::quantity< units::si::dimensionless, std::complex<double> >;

auto c_coefficient
(
  Lambda const lambda,
  Complex_lambda const complex_lambda,
  disk::Biot const biot2,
  disk::dimensionless::Thickness_w const w,
  disk::dimensionless::Radius_s const s,
  laser_beam::Modulation_depth const m
) noexcept -> C_coefficient;

} // seperation_of_variables
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* c_coefficient_h */
