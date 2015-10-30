//
//  processed_scope_data.cpp
//  tat
//
//  Created by Raymond Valdes on 10/2/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "processed_scope_data.hpp"

namespace gTBC{
namespace gMeasure {

processed_scope_data::processed_scope_data
(
  std::vector<
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > >
              const & laser_modulations_,

  std::vector<  std::pair<  thermal::equipment::detector::Measurements,
                          thermal::equipment::detector::Measurements > >
  const & measurements_,

  units::quantity< units::si::dimensionless > const gCoefficient_,
  units::quantity< units::si::length > const detector_view_radius_
)
: laser_modulations( laser_modulations_ ),
  measurements( measurements_ ),
  gCoefficient( gCoefficient_ ),
  detector_view_radius( detector_view_radius_ ) {}

} // namespace gMeasure
} // namespace gTBC
