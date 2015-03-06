//
//  slab.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__slab__
#define __tat__slab__

#include <cassert>
#include "math/differential/waveEquation/analytical.h"
#include "units.h"

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

  assert( x.value() > 0 );
  

//  auto const A_non =
//  auto const omega_non =
//  auto const kappa =

//  auto const s_x = analytical_solution_10( x,  )


  return 0;



//auto analytical_solution_10(
//  double const x,
//  std::complex<double> const Kappa,
//  double const A,
//  double const L_b )
//noexcept -> std::complex<double>
//};
  
} // namespace slab
  
} // namespace model
  
} // namespace thermal

#endif /* defined(__tat__slab__) */
