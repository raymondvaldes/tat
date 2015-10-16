//
//  measurements.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__measurements__
#define __tat__measurements__

#include <vector>

#include "thermal/equipment/detector/measurement.h"
#include "units.h"
#include "filesystem/path.h"


namespace thermal {

namespace equipment {

namespace detector {

class Measurements{

public:
  std::vector< Measurement > measurements;
  units::quantity<units::si::wavelength> wavelength; //of detector
  
  Measurements
  (
    units::quantity< units::si::wavelength > const wavelengthIn,
    std::vector< units::quantity< units::si::time > > const & referenceTime,
    std::vector< units::quantity< units::si::electric_potential > > const & signals
  );
  
  auto size( void ) const noexcept -> size_t;
  
  auto referenceTimes( void )
  const noexcept-> std::vector< units::quantity<units::si::time> >;
  
  auto delta_time( void )
  const noexcept -> units::quantity< units::si::time >;
  
  auto signals_electical_potential( void )
  const noexcept-> std::vector< units::quantity<units::si::electric_potential> >;
  
  auto plot_measurements( filesystem::path const & print_file = filesystem::path("") ) const noexcept -> void;
  auto print_table_measurements_values( void ) const noexcept -> void;

};

auto transient_sinusoidal_measurements_factory
(
  units::quantity< units::si::wavelength > const detector_wavelength,
  units::quantity< units::si::frequency > const periodic_frequency,
  units::quantity< units::si::plane_angle > const phase,
  units::quantity< units::si::electric_potential > const amplitude
) noexcept -> Measurements;



} // namespace detector

} // namespace equipment

} // namespace thermal

#endif /* defined(__tat__measurements__) */
