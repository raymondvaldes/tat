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

using namespace units;

Temperature::Temperature
(
  math::complex::properties< units::si::temperature > const & value
) noexcept: value( value )
{

}

Temperature::Temperature
(
  Phase const phase,
  Amplitude const amplitude
) noexcept: value( math::complex::properties< si::temperature >(phase, amplitude) )
{}

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
