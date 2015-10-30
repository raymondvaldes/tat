//
//  analysis_from_properties_sweep.cpp
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/pyrometry/twoColor/periodic/analysis_from_properties_sweep.h"
#include "thermal/pyrometry/twoColor/periodic/analysis_from_properties.h"

#include <cassert>
#include <cmath>
#include "gTBC/gMeasure/Processed_tbd_files.hpp"

using namespace units;

using algorithm::for_each;
using std::vector;
using namespace units;

namespace thermal {
namespace pyrometry {
namespace twoColor {
namespace periodic {

auto analysis_from_properties_sweep
(
  std::vector<
  math::functions::PeriodicProperties< units::si::electric_potential >> const & properties_1,
  units::quantity<units::si::wavelength> const detector_wavelength_1,
  std::vector<
  math::functions::PeriodicProperties< units::si::electric_potential >> const & properties_2,
  units::quantity<units::si::wavelength> const detector_wavelength_2,
  units::quantity< units::si::dimensionless > const & gCoeff,
  std::vector< units::quantity< units::si::frequency > > const & laser_frequencies
)
noexcept -> transient_analysis_sweep_results
{
  {
    assert( !properties_1.empty() );
    assert( properties_1.size() == properties_2.size() );
    assert( properties_1.size() == laser_frequencies.size() );
    assert( detector_wavelength_1 > 0 * meters );
    assert( detector_wavelength_1 < detector_wavelength_2 );
    assert( gCoeff > 0 );
    for( auto const freq : laser_frequencies ) {
      assert( freq > 0 * hertz );
    }
    auto n = 0u;
    for( auto const prop1 : properties_1 ) {
      assert( properties_1[n].omega == properties_2[n].omega );
      n++;
    }
  }

  
  auto results = vector< transient_analysis_results > ();
  results.reserve( properties_1.size() );

  size_t i = 0;
  for_each( laser_frequencies , [&]( auto const laser_frequency ) noexcept
  {
    auto const result =
    analysis_from_properties(
      properties_1[i], detector_wavelength_1,
      properties_2[i], detector_wavelength_2,
      gCoeff, laser_frequency
    ) ;
    
    results.push_back( result );
    ++i;
  } );

  auto const output = transient_analysis_sweep_results( results );

  return output;
}

auto analysis_from_properties_sweep
(
  gTBC::gMeasure::Processed_tbd_files const processed_files,
  units::quantity< units::si::dimensionless > const gCoeff
)
noexcept -> transient_analysis_sweep_results
{
  auto const output = analysis_from_properties_sweep
  (
    processed_files.properties_1,
    processed_files.detector_wavelength_1,
    processed_files.properties_2,
    processed_files.detector_wavelength_2,
    gCoeff,
    processed_files.laser_frequencies
  );


  return output;
}

} // namespace periodic  
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal
