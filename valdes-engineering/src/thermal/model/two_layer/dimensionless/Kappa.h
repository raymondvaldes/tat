//
//  Kappa.h
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_twoLayer_Kappa__
#define __tat_thermal_model_twoLayer_Kappa__

#include <complex>
#include "units.h"

namespace thermal {

namespace model {

namespace twoLayer {

namespace dimensionless {

auto
Kappa( units::quantity< units::si::dimensionless > const omega )
noexcept -> units::quantity< units::si::dimensionless, std::complex< double > >;
  
} // namespace dimensionless
  
} // namespace twoLayer
  
} // namespace model
  
} // namespace thermal

#endif /* defined(__tat_thermal_model_twoLayer_Kappa__) */
