//
//  Processed_tbd_files.hpp
//  tat
//
//  Created by Raymond Valdes on 10/2/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef Processed_tbd_files_hpp
#define Processed_tbd_files_hpp

#include <vector>
#include "units.h"
#include "thermal/equipment/detector/periodic_signal_properties.hpp"

namespace gTBC{
namespace gMeasure {

struct Processed_tbd_files{

  std::vector< thermal::equipment::detector::periodic_signal_properties > properties_1;
  units::quantity< units::si::wavelength > detector_wavelength_1;
  
  std::vector< thermal::equipment::detector::periodic_signal_properties > properties_2;
  units::quantity< units::si::wavelength > detector_wavelength_2;
  
  std::vector< units::quantity< units::si::frequency > > laser_frequencies;

  Processed_tbd_files
  (
    std::vector< thermal::equipment::detector::periodic_signal_properties > properties_1_,
    units::quantity< units::si::wavelength > detector_wavelength_1_,
  
    std::vector< thermal::equipment::detector::periodic_signal_properties > properties_2_,
    units::quantity< units::si::wavelength > detector_wavelength_2_,
  
    std::vector< units::quantity< units::si::frequency > > laser_frequencies_
  );
};

} // namespace gMeasure
} // namespace gTBC

#endif /* Processed_tbd_files_hpp */
