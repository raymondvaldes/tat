//
//  slab.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/slab/slab.h"

namespace thermal {

namespace model {

namespace slab {

auto neumann_and_direchlet_BC(
  units::quantity< units::si::length> x ,
  units::quantity< units::si::electric_potential > I_transient,
  units::quantity< units::si::thermal_conductivity > k,
  units::quantity< units::si::length > characteristic_length,
  units::quantity< units::si::thermal_diffusivity > alpha,
  units::quantity< units::si::frequency > f
)
noexcept -> double
{
  using math::differential::waveEquation::analytical_solution_10;

  assert( x.value() > 0 ) ;
  assert( I_transient.value() > 0 ) ;
  assert( k.value() > 0 ) ;
  assert( characteristic_length.value() > 0 ) ;
  assert( alpha.value() > 0 ) ;
  assert( f.value() > 0 ) ;

//  auto const A_non =
//  auto const omega_non =
//  auto const kappa =

//  auto const s_x = analytical_solution_10( x,  )

  return 0;
}

  
} // namespace slab
  
} // namespace model
  
} // namespace thermal
