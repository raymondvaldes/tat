//
//  processed_scope_data.hpp
//  tat
//
//  Created by Raymond Valdes on 10/2/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef processed_scope_data_hpp
#define processed_scope_data_hpp

#include <vector>
#include <utility>

#include "units.h"
#include "thermal/equipment/detector/measurements.h"

namespace gTBC{
namespace gMeasure {

struct processed_scope_data{

std::vector<
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > > laser_modulations;
  
  std::vector<
  std::pair<  thermal::equipment::detector::Measurements,
              thermal::equipment::detector::Measurements > > measurements;
  
  units::quantity< units::si::dimensionless > gCoefficient;
  units::quantity< units::si::length > detector_view_radius;
  
  
  processed_scope_data
  (
    std::vector<
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > > const & laser_modulations_,

    std::vector<  std::pair<  thermal::equipment::detector::Measurements,
                            thermal::equipment::detector::Measurements > >
    const & measurements_,
  
    units::quantity< units::si::dimensionless > const gCoefficient_,
    units::quantity< units::si::length > const detector_view_radius_
  );

};



} // namespace gMeasure
} // namespace gTBC

#endif /* processed_scope_data_hpp */
