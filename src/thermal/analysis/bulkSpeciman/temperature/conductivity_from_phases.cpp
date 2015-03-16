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


fitting_result::fitting_result
(
  thermal::model::slab::Slab const & initial_slab_,
  thermal::model::slab::Slab const & fitted_slab_,

  std::vector< units::quantity< units::si::plane_angle > > const & experimenta_phases_,
  std::vector< units::quantity< units::si::plane_angle > > const & bestFit_phases_
)
: initial_slab( initial_slab_ ),
  fitted_slab( fitted_slab_ ),
  experimenta_phases( experimenta_phases_ ),
  bestFit_phases( bestFit_phases_ )
{}

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
-> fitting_result
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
    
    auto const residual = [ & ]( const int i ) noexcept
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

  auto const fitted_slab = updateSlab( unknownParameters.data(), slab_initial  );
  auto const fitted_observations = surface_temperature_phases( omegas, fitted_slab ) ;


  auto const results =
  fitting_result( slab_initial, fitted_slab, observations ,fitted_observations);

  return results;
}

auto
diffusivity_from_phases
(
  std::pair< std::vector< units::quantity< units::si::angular_frequency > >,
  std::vector< units::quantity< units::si::plane_angle > > > const & observations,
  thermal::model::slab::Slab const & slab_initial
)
-> fitting_result
{
  return diffusivity_from_phases( observations.first, observations.second, slab_initial );
}

} // namespace temperature

} // namespace bulkSpeciman
  
} // namespace analysis

} // namespace thermal
