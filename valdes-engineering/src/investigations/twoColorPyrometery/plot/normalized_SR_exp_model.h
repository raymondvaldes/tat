//
//  normalized_SR_exp_model.h
//  tat
//
//  Created by Raymond Valdes_New on 3/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__normalized_SR_exp_model__
#define __tat__normalized_SR_exp_model__

#include <vector>
#include "units.h"

namespace investigations {

namespace twoColorPyrometery {

namespace plot{

auto normalized_SR_exp_model
(
  std::vector< units::quantity< units::si::time > > const & X,
  std::vector< units::quantity< units::si::one_over_temperature > > const & Y1,
  std::vector< units::quantity< units::si::one_over_temperature > > const & Y2
) noexcept -> void;

} // namespace plot
  
} // namespace twoColorPyrometery
  
} // namespace investigations

#endif /* defined(__tat__normalized_SR_exp_model__) */
