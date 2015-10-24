//
//  fit.cpp
//  tat-test
//
//  Created by Raymond Valdes on 10/21/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <vector>

#include "units.h"
#include "thermal/model/slab/slab.h"
#include "thermal/experimental/observations/slab/slab.hpp"
#include "thermal/analysis/oneLayer2D/finite_disk/centered_with_view/phase_analysis/fit_a_s_re_RC.hpp"

#include "thermal/model/optics/optics.h"
#include "thermal/plot/phase/model_vs_experiment_phases.hpp"
#include "thermal/model/oneLayer2D/generator/disk.hpp"
#include "thermal/model/oneLayer2D/model_selection.h"

using std::vector;
using namespace units;
using thermal::experimental::observations::Slab;
using thermal::model::Optics;
using thermal::analysis::oneLayer2D::finite_disk::centered_with_view::phase_analysis::fit_a_s_re_RC;


BOOST_AUTO_TEST_SUITE( thermal )
BOOST_AUTO_TEST_SUITE( analysis )
BOOST_AUTO_TEST_SUITE( oneLayer2D )
BOOST_AUTO_TEST_SUITE( finite_disk )
BOOST_AUTO_TEST_SUITE( phase )
BOOST_AUTO_TEST_SUITE( centered_point_with_view )

BOOST_AUTO_TEST_CASE( fit_all )
{
  auto const frequencies = vector< quantity< frequency > >({
    1.414213623 * hertz,
    2.0 * hertz,
    2.828427246 * hertz,
    4 * hertz,

    5.656854492 * hertz,
    8 * hertz,
    11.31370898 * hertz,
    16 * hertz,
    22.62741797 * hertz,
    32 * hertz,
    
    45.25483594 * hertz,
    64 * hertz,
    90.50967188 * hertz,
    
    128 * hertz,
    181.0193438 * hertz,
    256 * hertz,

    362.0386875 * hertz,
    512 * hertz,

    724.077375 * hertz,
    1024 * hertz,
    
    1448.15475 * hertz,
    2048 * hertz,

    2896.3095 * hertz,
    4096 * hertz,
    5792.619 * hertz,
    8192 * hertz,
    11585.238 * hertz

  });
  

  auto const phases = vector< quantity< plane_angle > >( {
  1.215 * radians, //  1.414  Hz
  1.281 * radians, //  2.0  Hz
  1.332 * radians, //  2.828    Hz
  1.369 * radians, // 4.0  Hz
  1.396 * radians, //  5.657 Hz

  1.406 * radians, //  8     Hz
  1.398 * radians, //  11.314  Hz
  1.372 * radians, //  16.0    Hz
  1.327 * radians, //  22.627  Hz
  1.259 * radians, //  32.0    Hz

  1.169 * radians, //  45.255  Hz
  1.061 * radians, //  64.0    Hz
  .947 * radians, //  90.510  Hz

  .860 * radians,  // 128      Hz
  0.793 * radians,   // 181.019  Hz
  0.768 * radians, // 256      Hz

  0.772 * radians, // 362.039  Hz
  0.786 * radians, // 512      Hz

  0.795 * radians,  // 724.077
  0.799 * radians,  // 1024
  0.769 * radians,  // 1448 Hz
  0.816 * radians,  //  2048 Hz
  0.822 * radians, // 2896.3  Hz

  0.837 * radians, // 4096      Hz
  0.860 * radians,  // 5792.6
  0.888 * radians,  // 8192
  0.933 * radians,  // 11585 Hz
    } );
  

  auto const L = quantity< length > ( .424 * millimeters  );// sample E
  auto const diffusivity = quantity<thermal_diffusivity>( 50 * square_millimeters / second);
  auto const conductivity_dummey =
    quantity< thermal_conductivity >( 80 * watts / meter / si::kelvin );
  
  auto const R = quantity< length >( 5.0 * millimeters );

  auto const slab_initial =
  thermal::model::slab::Slab( L, diffusivity, conductivity_dummey, R );
  
  
  auto const laser_radius = thermal::equipment::laser::Beam_radius( 5.9 * millimeters);
  auto const laser_intensity = thermal::equipment::laser::Beam_intensity( 5.0 * si::watts / si::square_meter );
  auto const view_radius = thermal::equipment::detector::View_radius( 2.0 * millimeters );
  auto const m = equipment::laser::Modulation_depth( 0.5 );
  
  auto const optics = Optics( laser_radius, laser_intensity, view_radius, m  );

  
  auto const best_fit = fit_a_s_re_RC( frequencies, phases, slab_initial, optics );

  std::cout << "\n" << best_fit.phase_goodness_of_fit  << "\n";

//  using thermal::model::oneLayer2D::generator::Disk;
//
//  auto const slab_bf = best_fit.bulk_slab;
//  auto const optics_bf = best_fit.optics;
//  auto const model = Disk(
//    thermal::model::oneLayer2D::Conduction_model::finite_disk,
//    thermal::model::oneLayer2D::Detector_model::center_point,
//    slab_bf,
//    optics_bf );
//
//  auto const model_complex_temperatures = model.evaluate( frequencies );
//
//  auto const model_phases = model_complex_temperatures.phases();
//  auto const experimental_phases = phases;
//  
//  thermal::plot::phase::model_vs_experiment_phases(
//        frequencies, model_phases, experimental_phases );
}


BOOST_AUTO_TEST_SUITE_END()  // suite fit_a_s_RC
BOOST_AUTO_TEST_SUITE_END()  // suite phase
BOOST_AUTO_TEST_SUITE_END()  // suite finite_disk
BOOST_AUTO_TEST_SUITE_END()  // suite oneLayer2D
BOOST_AUTO_TEST_SUITE_END()  // suite analysis
BOOST_AUTO_TEST_SUITE_END()  // suite thermal
