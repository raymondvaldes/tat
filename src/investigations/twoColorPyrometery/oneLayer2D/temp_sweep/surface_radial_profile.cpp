//
//  surface_radial_profile.cpp
//  tat
//
//  Created by Raymond Valdes on 5/1/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/temp_sweep/surface_radial_profile.h"

#include <iostream>
#include "thermal/model/oneLayer2D/infinite_disk/phase_amplitude/surface_radial_profile.h"
#include "thermal/model/oneLayer2D/dimensionless/b.h"
#include "algorithm/algorithm.h"
#include "math/construct/range.h"
#include "plot/gnuplot.h"
#include "math/complex/extract_phases_from_properties.h"
#include "math/complex/extract_amplitudes_from_properties.h"

using thermal::model::oneLayer2D::complex::temperature::surface_radial_profile;
using thermal::model::oneLayer2D::dimensionless::b;
using std::vector;
using algorithm::for_each;
using math::construct::range_1og10;
using namespace units;
using math::complex::extract_phases_from_properties;
using math::complex::extract_amplitudes_from_properties;
using std::cout;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace temp_sweep{

auto surface_radial_profile( filesystem::directory const & ) -> void
{
  auto const beam_radius = quantity<length>( 2.0 * millimeters);
  auto const deltaT = quantity<si::temperature>( 1.0 * kelvin );
  
  auto const L = quantity<length>( .1 * millimeters   );
  auto const alpha = quantity< thermal_diffusivity>( 70 * square_millimeters / second );
  
  auto const f = quantity< si::frequency >( 10 * hertz );
  
  auto const radial_positions =
  range_1og10< quantity< si::dimensionless> >( .01, 10 , 200 );
  
  auto const b_laser = b( beam_radius, L );
  auto const ps =
  thermal::model::oneLayer2D::complex::temperature::surface_radial_profile(
      b_laser, deltaT, radial_positions, L, alpha, f
    );
  
  auto i = size_t(0);
  auto const p_ref = ps[0].amplitude;
  for_each( ps, [&radial_positions, &i, &p_ref]( auto& p ){
    cout << radial_positions[i] << "\t" <<  p.amplitude/p_ref << "\t" << p.phase << "\n";
    ++i;
  });
  
//  auto const phases = extract_phases_from_properties( ps );
  auto const amplitudes = extract_amplitudes_from_properties(ps);
  
  
//  plot::simple_XY(radial_positions, phases );
  plot::simple_XY(radial_positions, amplitudes );

}

} // namespace temp_sweep
} // namespace oneLayer2D
} // namespace twoColorPyrometery
} // namespace investigations
