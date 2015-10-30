//
//  surface_phases_with_beam_diameter.cpp
//  tat
//
//  Created by Raymond Valdes on 5/18/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/surface_phases_with_beam_diameter.h"

#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/b.h"
#include "units.h"
#include "math/complex/extract_phases_from_properties.h"
#include "plot/gnuplot.h"
#include "cout/vector/print.h"

#include "thermal/model/oneLayer2D/infinite_disk/thermal_emission/centered_with_view/frequency_sweep.h"
using thermal::model::oneLayer2D::thermal_emission::centered_with_view::frequency_sweep;

using namespace units;
using cout::vector::print;
using thermal::model::oneLayer2D::dimensionless::b;
using math::complex::extract_phases_from_properties;
using plot::simple_XY;
using std::vector;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace frequency_sweep{

auto surface_phases_with_beam_diameter( filesystem::directory const & /*dir*/ ) -> void
{
  auto const deltaT = quantity< si::temperature > ( 1.0 * kelvin );

  auto const frequencies = vector< quantity< frequency > >({
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
    64 * hertz,
    90.51 * hertz,
    128 * hertz,
    181.019 * hertz,
    256 * hertz,
    362.039 * hertz,
    512 * hertz,
    724.077 * hertz,
    1024 * hertz,
    1448.155 * hertz,
    2048 * hertz,
    2896.31 * hertz,
    4096 * hertz,
    5792.62 * hertz,
    8192 * hertz,
    11585.25 * hertz
  });
  
  // establish nondimensional fitting parameters
  auto const L = quantity< length > ( 5 * millimeters  );

  auto const beam_radius = quantity< length >( 2.0 * millimeters );
  
  auto const detector_view_radius = quantity< length >( 0.5 * millimeters  ) ;
  auto const alpha = quantity<thermal_diffusivity>( 70 * square_millimeters / second);

  //(diffusivity shifts the curve left and right)
  
  auto const b1 = b( beam_radius, L );
  auto const b2 = b( detector_view_radius, L );
  
  auto const predictions =
  thermal::model::oneLayer2D::thermal_emission::centered_with_view::frequency_sweep(
    b1, deltaT, b2, frequencies, L, alpha );
    
  auto const phases = extract_phases_from_properties( predictions  ) ;
  
  
  print( phases );
  
  plot::simple_XY(frequencies, phases);
}

} // namespace frequency_sweep
} // namespace oneLayer2D
} // namespace twoColorPyrometery
} // namespace investigations
