//
//  conductivity_from_phases.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/10/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <vector>

#include "thermal/model/slab/slab.h"
#include "thermal/analysis/bulkSpeciman/temperature/conductivity_from_phases.h"
#include "thermal/model/slab/slab.h"
#include "math/estimation/lmdiff.hpp"
#include "math/estimation/settings.h"
#include "algorithm/algorithm.h"
#include "units.h"

namespace thermal {

namespace analysis {

namespace bulkSpeciman {

namespace temperature {

auto
conductivity_from_phases
(
  std::vector< units::quantity< units::si::angular_frequency > > const & omegas,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const & slab_initial
)
-> void /* thermal::model::slab::Slab */
{
//  using std::vector;
//  using algorithm::generate;
//  using math::estimation::settings;
//  using thermal::model::slab::Slab;
//  using units::quantity;
//  using units::si::thermal_diffusivity;
//
//  auto const numberPoints2Fit = omegas.size();
//
//  auto const updateSlab = [  ]
//  ( const double* x , thermal::model::slab::Slab const & mySlab ) noexcept
//  {
//    auto const fittedDiffusivity =
//      quantity< thermal_diffusivity >::from_value( x[0] ) ;
//
//    auto const fittedSpeciman =
//    Slab( mySlab.characteristic_length , fittedDiffusivity , mySlab.k ) ;
//    
//    return fittedSpeciman ;
//  };
//
//  auto const minimizationEquation =
//  [ &omegas, &observations, &slab_initial, &updateSlab, &numberPoints2Fit ]
//  ( const double *x, double *fvec ) noexcept
//  {
//    using thermal::model::slab::surface_temperature_phases;
//    
//    auto const slabCurrent = updateSlab( x, slab_initial );
//    
//    auto const I_dummy = quantity<units::si::heat_flux>::from_value(1);
//
//    auto const predictions =
//      surface_temperature_phases( omegas, I_dummy, slabCurrent ) ;
//    
//    auto const residual = [ & ]( const int i )
//    {
//      return ( predictions[i]  -  observations[i] ).value() ;
//    } ;
//
//    auto i = 0;
//    std::generate( fvec, fvec + numberPoints2Fit , [&](){ return residual(i++); } ) ;
//  };
//
//  auto unknownParameters = vector<double>{ slab_initial.alpha.value() } ;
//  lmdif( minimizationEquation, numberPoints2Fit, unknownParameters, settings{});
//
//  auto const fittedSpeciman = updateSlab( unknownParameters.data(), slab_initial  );

//  return fittedSpeciman;
}

} // namespace temperature

} // namespace bulkSpeciman
  
} // namespace analysis

} // namespace thermal
