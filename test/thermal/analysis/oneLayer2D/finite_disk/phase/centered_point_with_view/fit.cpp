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
#include "thermal/analysis/oneLayer2D/fit.hpp"

#include "thermal/model/optics/optics.h"
#include "thermal/plot/phase/model_vs_experiment_phases.hpp"
#include "thermal/model/oneLayer2D/generator/disk.hpp"
#include "thermal/model/oneLayer2D/model_selection.h"
#include "thermal/model/oneLayer2D/parameter_list.hpp"
#include "thermal/model/complex/temperatures_factory_dummy_amplitudes.hpp"
#include "thermal/analysis/oneLayer2D/fit_selection.h"

using std::vector;
using namespace units;
using thermal::experimental::observations::Slab;
using thermal::model::Optics;
using thermal::model::complex::temperature_factory_dummy_amplitudes;
using thermal::model::oneLayer2D::generator::Disk;
using thermal::model::oneLayer2D::Detector_model;
using thermal::model::oneLayer2D::Conduction_model;
using thermal::analysis::oneLayer2D::Fit_selection;

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
  auto const laser_power = thermal::equipment::laser::Beam_power( 5.0 * si::watts );
  auto const view_radius = thermal::equipment::detector::View_radius( 2.0 * millimeters );
  auto const m = equipment::laser::Modulation_depth( 0.5 );
  
  auto const optics = Optics( laser_radius, laser_power, view_radius, m  );

  using thermal::model::oneLayer2D::Parameters;
  auto const parameters = Parameters({
    thermal::model::oneLayer2D::Parameter::disk_thermal_diffusivity,
    thermal::model::oneLayer2D::Parameter::disk_radius,
    thermal::model::oneLayer2D::Parameter::detector_radius,
    thermal::model::oneLayer2D::Parameter::rc_filter
  });  
  
  auto const conduction_model = thermal::model::oneLayer2D::Conduction_model::finite_disk;
  auto const detector_model = thermal::model::oneLayer2D::Detector_model::center_with_view;
  
  auto const initial_disk = Disk(
    Conduction_model::finite_disk,
    Detector_model::center_with_view,
    slab_initial,
    optics );
  
  auto const temperatures = temperature_factory_dummy_amplitudes( phases );


  auto const best_fit_phases =
  fit( frequencies, temperatures, Fit_selection::phases, initial_disk, parameters);

//  auto const best_fit_amplitudes =
//  fit( frequencies, temperatures, Fit_selection::amplitudes, initial_disk, parameters);


std::cout << best_fit_phases.phase_goodness_of_fit_function() << "\n\n";
  BOOST_CHECK_CLOSE_FRACTION( 7.41395e-5, best_fit_phases.phase_goodness_of_fit_function(), 1e-5);
}


BOOST_AUTO_TEST_SUITE_END()  // suite fit_a_s_RC
BOOST_AUTO_TEST_SUITE_END()  // suite phase
BOOST_AUTO_TEST_SUITE_END()  // suite finite_disk
BOOST_AUTO_TEST_SUITE_END()  // suite oneLayer2D
BOOST_AUTO_TEST_SUITE_END()  // suite analysis
BOOST_AUTO_TEST_SUITE_END()  // suite thermal
