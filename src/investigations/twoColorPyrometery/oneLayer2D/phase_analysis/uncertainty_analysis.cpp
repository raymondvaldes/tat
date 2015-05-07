//
//  uncertainty_analysis.cpp
//  tat
//
//  Created by Raymond Valdes on 5/7/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/uncertainty_analysis.h"

#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/uncertainty_analysis.h"
#include "thermal/pyrometry/twoColor/calibrate_wavelength.h"
#include "thermal/model/slab/import_slab.h"
#include "units.h"

using namespace units;
using std::vector;
using thermal::model::slab::import ;
using thermal::pyrometry::twoColor::calibrate_wavelength;
using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::uncertainty_analysis;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace phase_analysis{

auto uncertainty_analysis( filesystem::directory const & dir ) noexcept -> void
{
  auto const initial_slab = thermal::model::slab::import( dir, "initial_slab.xml" ) ;
  auto const steady_state_temperature = quantity<si::temperature>( 781.14 * kelvin );
  
  auto const nominal_wavelength = quantity< si::wavelength >( 4.6 * micrometers );
  auto const wavelength_offset = quantity< wavelength >( -.5743693 * micrometers );
  auto const lambda_1 = quantity<wavelength>( 4.6 * micrometers );
  auto const lambda_2 = quantity<wavelength>( 5.6 * micrometers );
  auto const lambda_avg = quantity<wavelength>( 5.1 * micrometers );
  
  auto const detector_wavelength_1 =
    calibrate_wavelength( lambda_1, wavelength_offset );
  
  auto const detector_wavelength_2 =
    calibrate_wavelength( lambda_2, wavelength_offset );  

  auto const detector_wavelength_avg =
    calibrate_wavelength( lambda_avg, wavelength_offset );
  
  auto const frequencies = vector< quantity< frequency > >({
    1.414 * hertz,
    2 * hertz,
    2.828 * hertz,
    4 * hertz,
    5.657 * hertz,
    8 * hertz,
    11.314 * hertz,
    16 * hertz,
    22.627 * hertz,
    32 * hertz,
    45.255 * hertz,
//    64 * hertz,
//    90.51 * hertz,
//    128 * hertz,
//    181.019 * hertz,
//    256 * hertz,
//    362.039 * hertz,
//    512 * hertz,
//    724.077 * hertz,
//    1024 * hertz,
//    1448.155 * hertz,
//    2048 * hertz
  });

  auto const phases = vector< quantity< plane_angle > >({
    0.96987525 * radians,
    1.030075 * radians,
    1.076665 * radians,
    1.1059025 * radians,
    1.11566 * radians,
    1.1053475 * radians,
    1.0592525 * radians,
    0.98896025 * radians,
    0.89821 * radians,
    0.80698475 * radians,
    0.7405715 * radians,
//    0.668 * radians,
//    0.6465 * radians,
//    0.65 * radians,
//    0.6495 * radians,
//    0.639 * radians,
//    0.623 * radians,
//    0.5975 * radians,
//    0.5755 * radians,
//    0.549 * radians,
//    0.525 * radians,
//    0.491 * radians
  });
  
  auto const beam_radius = quantity< length >( 2.11362 * millimeters );
  auto const detector_view_radius = quantity< length>( .8 * millimeters  ) ; // initial value

  thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::uncertainty_analysis(
    frequencies, phases , initial_slab, beam_radius, detector_view_radius,
    steady_state_temperature, detector_wavelength_avg );

}

} // namespace
} // namespace
} // namespace
} // namespace
