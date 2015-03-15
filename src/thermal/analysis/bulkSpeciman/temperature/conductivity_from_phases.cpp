//
//  conductivity_from_phases.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/10/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <iterator>

#include "thermal/analysis/bulkSpeciman/temperature/conductivity_from_phases.h"
#include "math/estimation/lmdiff.hpp"
#include "math/estimation/settings.h"
#include "algorithm/algorithm.h"

namespace thermal {

namespace analysis {

namespace bulkSpeciman {

namespace temperature {

inline auto updateSlab
(
  const double* x ,
  thermal::model::slab::Slab const & mySlab
) noexcept -> thermal::model::slab::Slab
{
  using units::quantity;
  using units::si::thermal_diffusivity;
  using thermal::model::slab::Slab;

  auto const fittedDiffusivity =
  quantity< thermal_diffusivity >::from_value( x[0] ) ;

  auto const fittedSpeciman =
  Slab( mySlab.characteristic_length , fittedDiffusivity , mySlab.rhoCp ) ;
  
  return fittedSpeciman ;
}

auto
diffusivity_from_phases
(
  std::vector< units::quantity< units::si::angular_frequency > > const & omegas,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const & slab_initial
)
-> thermal::model::slab::Slab
{
  using std::vector;
  using std::generate;
  using math::estimation::settings;
  using thermal::model::slab::surface_temperature_phases;
  
  auto const numberPoints2Fit = omegas.size();

  auto const minimizationEquation =
  [ &omegas, &observations, &slab_initial, &numberPoints2Fit ]
  ( const double *x, double *fvec ) noexcept
  {
    auto const slabCurrent = updateSlab( x, slab_initial );
    
    auto const predictions = surface_temperature_phases( omegas, slabCurrent ) ;
    
    auto const residual = [ & ]( const int i )
    {
      return ( predictions[i]  -  observations[i] ).value() ;
    } ;

    auto i = 0;
    generate( fvec, fvec + numberPoints2Fit , [&]() noexcept
    {
      return residual(i++);
    } ) ;
  };

  auto const myDiffusivity = slab_initial.get_diffusivity();
  auto unknownParameters = vector<double>{ myDiffusivity.value() } ;
  lmdif( minimizationEquation, numberPoints2Fit, unknownParameters, settings{});

  auto const fittedSpeciman = updateSlab( unknownParameters.data(), slab_initial  );

  return fittedSpeciman;
}

auto
diffusivity_from_phases
(
  std::pair< std::vector< units::quantity< units::si::angular_frequency > >,
  std::vector< units::quantity< units::si::plane_angle > > > const & observations,
  thermal::model::slab::Slab const & slab_initial
)
-> thermal::model::slab::Slab
{
  return diffusivity_from_phases( observations.first, observations.second, slab_initial );
}

} // namespace temperature

} // namespace bulkSpeciman
  
} // namespace analysis

} // namespace thermal
