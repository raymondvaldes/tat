//
//  diffusivity_from_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 4/29/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/fit_all_but_laser/diffusivity_from_phases.h"
#include "units.h"

#include "thermal/analysis/oneLayer2D/estimate_parameters/fit_all_but_laser/diffusivity_from_phases.h"
#include "thermal/model/slab/import_slab.h"

using namespace units;
using thermal::model::slab::import ;
using thermal::analysis::oneLayer2D::estimate_parameters::fit_all_but_laser::diffusivity_from_phases;
using std::vector;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace fit_all_but_laser{

auto diffusivity_from_phases( filesystem::directory const & dir ) -> void
{
 // auto const gCoeff = 1.23_nd;
  auto const initial_slab = import( dir, "initial_slab.xml" ) ;
  
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
//    90.51 * hertz
 //   128 * hertz,
 //   181.019 * hertz,
 //   256 * hertz,
 //   362.039 * hertz,
 //   512 * hertz,
 //   724.077 * hertz,
 //   1024 * hertz,
 //   1448.155 * hertz,
 //   2048 * hertz
  });
  
  auto const phases = vector< quantity< plane_angle > >({
    0.975120667 * radians,
    1.034716667 * radians,
    1.079263333 * radians,
    1.105916667 * radians,
    1.114323333 * radians,
    1.105973333 * radians,
    1.061003333 * radians,
    0.993261 * radians,
    0.902343 * radians,
    0.806916333 * radians,
    0.734095333 * radians,
 //   0.668 * radians,
  //  0.6465 * radians
 //   0.65 * radians,
 //   0.6495 * radians,
//    0.639 * radians,
//    0.623 * radians,
//    0.5975 * radians,
//    0.5755 * radians,
//    0.549 * radians,
//    0.525 * radians,
 //   0.491 * radians
  });
  
  auto const beam_radius = quantity< length >( 2.11362 * millimeters );
  auto const detector_view_radius = quantity< length>( .8 * millimeters  ) ;

  auto const bestFit_results =
  thermal::analysis::oneLayer2D::estimate_parameters::fit_all_but_laser::diffusivity_from_phases(
    frequencies, phases , initial_slab, beam_radius, detector_view_radius ) ;
}

} // namespace
} // namespace
} // namespace
} // namespace
