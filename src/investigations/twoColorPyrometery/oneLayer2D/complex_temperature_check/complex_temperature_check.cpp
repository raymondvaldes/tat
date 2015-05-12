//
//  complex_temperature_check.cpp
//  tat
//
//  Created by Raymond Valdes on 5/8/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/complex_temperature_check/complex_temperature_check.h"

#include <iostream>
#include "units.h"
#include "thermal/model/oneLayer2D/complex/surface_phase_amplitude.h"
#include "thermal/define/lthermal.h"
#include "thermal/model/oneLayer2D/complex/detector_emission/detector_emission.h"
#include "thermal/pyrometry/twoColor/calibrate_wavelength.h"
#include "thermal/model/oneLayer2D/complex/reverseIntegration/tempeature_nd.h"
#include "math/transform/inverseHankel.h" //hankel settings

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace complex_temperature_check{

using namespace units;
using thermal::define::thermal_penetration;
using thermal::model::oneLayer2D::complex::detector_emission;
using thermal::model::oneLayer2D::complex::surface_phase_amplitude;
using thermal::pyrometry::twoColor::calibrate_wavelength;
using thermal::model::oneLayer2D::complex::reverseIntegration::temperature_nd;
using math::transform::iHankelSettings;
  
auto complex_temperature_check( filesystem::directory const & dir  )
noexcept -> void
{
  std::cout << "\n";
  auto const T_steady_state = quantity<si::temperature>( 781.14 * kelvin );
  auto const wavelength_offset = quantity< wavelength >( -.5743693 * micrometers );
  auto const lambda_1 = quantity< wavelength >( 4.6 * micrometers );
  auto const detector_wavelength_1 =
    calibrate_wavelength( lambda_1, wavelength_offset );
  
  auto const alpha = quantity<si::thermal_diffusivity >( 22.0 * square_millimeters/second );
  auto const radius_heating = quantity<si::length>( 2.11 * millimeters);
  auto const L = quantity<si::length>( .661 * millimeters );
  auto const f = quantity<si::frequency>( 10. * hertz );
  
  auto const r_dim  = quantity<si::length>( 0. * meters ) ;
  auto const deltaT = quantity<si::temperature>( 1.0 *kelvin );

  auto const b = radius_heating / L;
  auto const r =  r_dim /  radius_heating;
  auto const l = thermal_penetration( alpha, f, L );
  
  auto const point_eval = surface_phase_amplitude( r, b, l, deltaT );
 
  
  auto const r_e  = quantity< si::length >( 2.1 * millimeters ) ;
  auto const view_radius = r_e / radius_heating;
//  auto const detector_eval =
//  detector_emission( b, l, deltaT, view_radius, T_steady_state, detector_wavelength_1 );

  auto settings = iHankelSettings();
  settings.nu_end = 7.0;
  auto const detector_fast = temperature_nd( b, l, view_radius, settings );
  
  std::cout << "\n";
  std::cout << "center point:  " <<point_eval.phase << "\n";
 // std::cout << "detector area: " << arg( detector_eval ) << " rad" << "\n";
  std::cout << "detector-fast: " << -arg(detector_fast ) << "\n";
}

} // namespace
} // namespace
} // namespace
} // namespace
