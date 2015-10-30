//
//  frequency_detector_ground.hpp
//  tat
//
//  Created by Raymond Valdes on 10/13/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef frequency_detector_ground_h_101315
#define frequency_detector_ground_h_101315

#include <utility>

#include "units.h"

namespace gTBC{
namespace gMeasure{

struct Frequency_detector_ground{

  units::quantity< units::si::frequency > laser_frequency;
  
  std::pair<  units::quantity< units::si::wavelength >,
              units::quantity< units::si::electric_potential > > lambda1_grnd;
  
  std::pair<  units::quantity< units::si::wavelength >,
              units::quantity< units::si::electric_potential > > lambda2_grnd;
  
  Frequency_detector_ground(
    units::quantity< units::si::frequency > const laser_frequency_,
    std::pair<  units::quantity< units::si::wavelength >,
              units::quantity< units::si::electric_potential > >
              const lambda1_grnd_,
    std::pair<  units::quantity< units::si::wavelength >,
              units::quantity< units::si::electric_potential > >
              const lambda2_grnd_
    ): laser_frequency( laser_frequency_ ),
      lambda1_grnd( lambda1_grnd_ ),
      lambda2_grnd( lambda2_grnd_ )  {};
};

} // namespace gMeasure
} // namespace gTBC

#endif /* frequency_detector_ground_h */
