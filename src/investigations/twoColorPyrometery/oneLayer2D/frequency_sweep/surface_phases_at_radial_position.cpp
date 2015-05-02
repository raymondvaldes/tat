//
//  surface_at_radial_position.cpp
//  tat
//
//  Created by Raymond Valdes on 5/2/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/surface_phases_at_radial_position.h"

#include <iostream>
#include "thermal/model/oneLayer2D/phase_amplitude/surface_frequency_profile.h"
#include "thermal/model/oneLayer2D/dimensionless/b.h"
#include "algorithm/algorithm.h"
#include "math/construct/range.h"
#include "plot/gnuplot.h"
#include "math/complex/extract_phases_from_properties.h"
#include "math/complex/extract_amplitudes_from_properties.h"

using thermal::model::oneLayer2D::phase_amplitude::surface_frequency_profile;
using thermal::model::oneLayer2D::dimensionless::b;
using std::vector;
using algorithm::for_each;
using math::construct::range_1og10;
using namespace units;
using math::complex::extract_phases_from_properties;
using math::complex::extract_amplitudes_from_properties;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace frequency_sweep{

auto surface_phases_at_radial_position( filesystem::directory const & dir ) -> void
{
  auto const L = quantity<length>( 661. * micrometers);
  auto const beam_radius = quantity<length>( 2.1 * millimeters);
  auto const deltaT = quantity<si::temperature>( 1.0 * kelvin );
  
  auto const alpha = quantity< thermal_diffusivity>( 22 * square_millimeters / second );
  auto const radial_position = quantity<dimensionless>( .5 );
  
  //( The radial position influences the shape of the profile,
  //  but not the "intensity" of it ).
  // fit amplitude curve to get the radial position.
  // Use the radial position to fit the phase curve
  
  auto const frequencies =
  range_1og10< quantity< si::frequency > >( 1. * hertz, 2000. * hertz, 30 );
  
  auto const b_laser = b( beam_radius, L );
  auto const ps = surface_frequency_profile(
      b_laser, deltaT, frequencies, L, alpha, radial_position
    );
  
  auto i = size_t(0);
  for_each( ps, [&frequencies, &i]( auto& p ){
    std::cout << frequencies[i] << "\t" <<  p.amplitude << "\t" << p.phase << "\n";
    ++i;
  });
  
  auto const phases = extract_phases_from_properties( ps );
  auto const amplitudes = extract_amplitudes_from_properties(ps);
  
  plot::simple_XY( frequencies, phases );
  plot::simple_XY( frequencies, amplitudes );
}

} // namespace frequency_sweep
} // namespace oneLayer2D
} // namespace twoColorPyrometery
} // namespace investigations
