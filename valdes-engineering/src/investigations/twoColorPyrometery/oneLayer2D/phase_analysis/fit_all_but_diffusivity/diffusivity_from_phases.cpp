//
//  diffusivity_from_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 5/7/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/phase_analysis/fit_all_but_diffusivity/diffusivity_from_phases.h"

#include "units.h"
#include "thermal/pyrometry/twoColor/calibrate_wavelength.h"
#include "thermal/analysis/oneLayer2D/estimate_parameters/phase_analysis/fit_all_but_diffusivity/diffusivity_from_phases.h"
#include "thermal/model/slab/import_slab.h"

using namespace units;
using thermal::model::slab::import ;
using std::vector;
using thermal::pyrometry::twoColor::calibrate_wavelength;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace phase_analysis{
namespace fit_all_but_diffusivity{

using thermal::analysis::oneLayer2D::estimate_parameters::phase_analysis::fit_all_but_diffusivity::diffusivity_from_phases;

auto diffusivity_from_phases( filesystem::directory const & dir ) -> void
{
  auto const initial_slab = thermal::model::slab::import( dir, "initial_slab.xml" ) ;  

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
//    45.255 * hertz,
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

  auto const phases = vector< quantity< plane_angle > >( {
  0.9879 * radians,
1.0455 * radians,
1.085 * radians,
1.1055 * radians,
1.1105 * radians,
1.106 * radians,
1.064 * radians,
1.0025 * radians,
0.912 * radians,
0.808 * radians,
//    0.7405715 * radians,
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
  } );
  
  auto const beam_radius = quantity< length >( 2.11362 * millimeters );
  auto const detector_view_radius = quantity< length>( .8 * millimeters  ) ; // initial value

  diffusivity_from_phases(
    frequencies, phases , initial_slab, beam_radius, detector_view_radius) ;
}

} // namespace
} // namespace
} // namespace
} // namespace
} // namespace
