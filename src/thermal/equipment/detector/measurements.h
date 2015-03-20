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

namespace thermal {

namespace equipment {

namespace detector {

struct Measurements{

  units::quantity<units::si::wavelength> wavelength; //of detector
  std::vector< Measurement > measurements;
  
  Measurements
  (
    units::quantity< units::si::wavelength > const & wavelengthIn,
    std::vector< units::quantity< units::si::time > > const & referenceTime,
    std::vector< units::quantity< units::si::electric_potential > > const & signals
  );
  
  auto size( void ) const noexcept -> size_t;
  
  auto referenceTimes( void )
  const noexcept-> std::vector< units::quantity<units::si::time> >;
  
  auto signals_electical_potential( void )
  const noexcept-> std::vector< units::quantity<units::si::electric_potential> >;
  
  auto plot_measurements( void ) const noexcept -> void;
};

} // namespace detector

} // namespace equipment

} // namespace thermal

#endif /* defined(__tat__measurements__) */
