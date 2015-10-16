//
//  temperature.h
//  tat
//
//  Created by Raymond Valdes on 10/15/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef Complex_temperature_h_101515
#define Complex_temperature_h_101515

#include "units.h"
#include "math/complex/properties.h"
#include "thermal/model/complex/phase.h"
#include "thermal/model/complex/amplitude.h"

namespace thermal{
namespace model{
namespace complex{

class Temperature{

  private:
  math::complex::properties< units::si::temperature > value;
  
  public:
  
  Temperature
  ( math::complex::properties< units::si::temperature > const & value );
  Temperature (){};
  
  auto phase() const noexcept -> Phase ;
  auto amplitude() const noexcept -> Amplitude;
  
};

} // namespace complex
} // namespace model
} // namespace thermal


#endif /* Complex_temperature_h */
