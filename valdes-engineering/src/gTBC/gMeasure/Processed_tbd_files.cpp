//
//  Processed_tbd_files.cpp
//  tat
//
//  Created by Raymond Valdes on 10/2/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "Processed_tbd_files.hpp"
#include <cassert>
#include <cmath>

namespace gTBC{
namespace gMeasure {

Processed_tbd_files::Processed_tbd_files
(
  std::vector< thermal::equipment::detector::periodic_signal_properties > properties_1_,
  units::quantity< units::si::wavelength > detector_wavelength_1_,

  std::vector< thermal::equipment::detector::periodic_signal_properties > properties_2_,
  units::quantity< units::si::wavelength > detector_wavelength_2_,

  std::vector< units::quantity< units::si::frequency > > laser_frequencies_
) :
  properties_1 ( properties_1_ ),
  detector_wavelength_1 ( detector_wavelength_1_ ),
  properties_2 ( properties_2_ ) ,
  detector_wavelength_2 ( detector_wavelength_2_ ) ,
  laser_frequencies ( laser_frequencies_ )
{
    assert( detector_wavelength_1 < detector_wavelength_2 );
    assert( properties_1.size() == properties_2.size() );
    assert( properties_1.size() == laser_frequencies.size() );
    assert( !laser_frequencies.empty() );
    for( auto const f : laser_frequencies ) {
      assert( std::isfinite( f.value() ) );
    }
  
}

} // namespace gMeasure
} // namespace gTBC
