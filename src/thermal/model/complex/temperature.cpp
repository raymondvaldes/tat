//
//  temperature.cpp
//  tat
//
//  Created by Raymond Valdes on 10/15/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/complex/temperature.h"

namespace thermal{
namespace model{
namespace complex{


Temperature::Temperature
(
  math::complex::properties< units::si::temperature > const & value
): value( value )
{

}

auto Temperature::phase() const noexcept -> Phase
{
  auto const p = value.phase;
  return p;
}


auto Temperature::amplitude() const noexcept -> Amplitude
{
  auto const a = value.amplitude;
  return a;
}


} // namespace complex
} // namespace model
} // namespace thermal
