//
//  predicted_sweep.cpp
//  tat
//
//  Created by Raymond Valdes on 4/30/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <vector>

#include "investigations/twoColorPyrometery/oneLayer2D/frequency_sweep/avg_phases_at_surface.h"
#include "thermal/model/slab/import_slab.h"

#include "thermal/model/oneLayer2D/dimensionless/b.h"
#include "units.h"
#include "math/complex/extract_phases_from_properties.h"
#include "plot/gnuplot.h"
#include "cout/vector/print.h"
#include "thermal/model/oneLayer2D/thermal_emission/frequency_sweep.h"
using thermal::model::oneLayer2D::thermal_emission::frequency_sweep;

using namespace units;
using thermal::model::slab::import ;

using thermal::model::oneLayer2D::dimensionless::b;
using math::complex::extract_phases_from_properties;
using plot::simple_XY;
using std::vector;
using cout::vector::print;
using cout::vector::print_table_values;

namespace investigations{
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace frequency_sweep{

auto avg_phases_at_surface( filesystem::directory const & dir ) -> void
{
  auto const deltaT = quantity< si::temperature > ( 1.0 * kelvin );

  auto const frequencies = vector< quantity< frequency > >({
  
//    .01414 * hertz,
//    .05414 * hertz,
//    .10 * hertz,
//    .1414 * hertz,
//
//    .2 * hertz,
//    .4 * hertz,
//    .8 * hertz,
  
    1.0 * hertz,
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
    
    2896.384 * hertz,
    4096 * hertz,
    5792.768 * hertz,
    8192 * hertz,
    11585.536 * hertz
    
  });
  
  // establish nondimensional fitting parameters (specimen-e)
  auto const L = quantity< si::length > ( 1.614 * millimeters );
  auto const beam_radius = quantity< length >( 2.087 * millimeters );
  auto const detector_view_radius = quantity< length >( .096 * millimeters  ) ;
  auto const alpha = quantity<thermal_diffusivity >( 39.72 * square_millimeters / second );
  
  // establish nondimensional fitting parameters (specimen-e)
//  auto const L = quantity< si::length> ( 1.2 * millimeters );
//  auto const beam_radius = quantity< length >( 2.34 * millimeters );
//  auto const detector_view_radius = quantity< length>( .333 * millimeters  ) ;
//  auto const alpha = quantity<thermal_diffusivity>( 43.77 * square_millimeters / second);
  
//  // establish nondimensional fitting parameters (specimen-e)
//  auto const L = quantity< si::length> ( .800 * millimeters );
//  auto const beam_radius = quantity< length >( 2.597 * millimeters );
//  auto const detector_view_radius = quantity< length>( .1895 * millimeters  ) ;
//  auto const alpha = quantity<thermal_diffusivity>( 40.33 * square_millimeters / second);

//  // establish nondimensional fitting parameters (specimen-h)
//  auto const L = quantity< si::length> ( .8 * millimeters );
//  auto const beam_radius = quantity< length >( 2.112 * millimeters );
//  auto const detector_view_radius = quantity< length>( 0.122 * millimeters  ) ;
//  auto const alpha = quantity<thermal_diffusivity>( 36.72 * square_millimeters / second);


  //(diffusivity shifts the curve left and right)
  
  auto const b1 = b( beam_radius, L ) ;
  auto const b2 = b( detector_view_radius, L ) ;
  
  auto const predictions =
  thermal::model::oneLayer2D::thermal_emission::frequency_sweep(
    b1, deltaT, b2, frequencies, L, alpha );
    
  auto const phases = extract_phases_from_properties( predictions  ) ;
  
  print_table_values( frequencies, phases );
//  plot::simple_XY(frequencies, phases);
}

} // namespace
} // namespace
} // namespace
} // namespace
