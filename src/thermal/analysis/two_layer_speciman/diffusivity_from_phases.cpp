//
//  diffusivity_from_phases.cpp
//  tat
//
//  Created by Raymond Valdes on 3/24/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/analysis/two_layer_speciman/diffusivity_from_phases.h"

#include "thermal/model/two_layer/complex/surface_phases.h"
#include "math/estimation/settings.h"
#include "math/estimation/lmdiff.hpp"
#include "algorithm/algorithm.h"

namespace thermal {
namespace analysis {
namespace two_layer_speciman {

using std::pair;
using std::vector;
using std::generate;
using math::estimation::settings;
using thermal::model::slab::Slab;
using model::twoLayer::complex::surface_phases;
using namespace units;

inline auto updateSlab
(
  const double* x ,
  thermal::model::slab::Slab const & mySlab
) noexcept -> thermal::model::slab::Slab
{

  auto const fittedDiffusivity =
  quantity< thermal_diffusivity >::from_value( x[0] ) ;
  
  auto const fitted_length = mySlab.characteristic_length ;

  auto const fittedSpeciman =
  Slab( fitted_length , fittedDiffusivity , mySlab.rhoCp ) ;
  
  return fittedSpeciman ;
}

fitting_result::fitting_result
(
  std::vector< units::quantity<units::si::frequency> > const  frequencies_,

  thermal::model::slab::Slab const initial_slab_,
  thermal::model::slab::Slab const fitted_slab_,
  thermal::model::slab::Slab const substrate_slab_,
 
  std::vector< units::quantity< units::si::plane_angle > > const experimenta_phases_,
  std::vector< units::quantity< units::si::plane_angle > > const bestFit_phases_
)
: frequencies( frequencies_ ),
  initial_slab( initial_slab_ ),
  fitted_slab( fitted_slab_ ),
  substrate_slab( substrate_slab_ ),
  experimenta_phases( experimenta_phases_ ),
  bestFit_phases( bestFit_phases_ )
{
  assert( frequencies.size() > 0 );
  assert( experimenta_phases.size() > 0 );
  assert( bestFit_phases.size() > 0 );
}

auto
diffusivity_from_phases
(
  std::pair<
    std::vector< units::quantity< units::si::frequency > >,
    std::vector< units::quantity< units::si::plane_angle > >
  > const & observations,
  thermal::model::slab::Slab const & slab_initial,
  thermal::model::slab::Slab const & slab_substrate
)
-> fitting_result
{
  auto const results = diffusivity_from_phases(
  observations.first, observations.second, slab_initial, slab_substrate ) ;

  return results ;
}

auto diffusivity_from_phases
(
  std::vector< units::quantity< units::si::frequency > > const & frequencies,
  std::vector< units::quantity< units::si::plane_angle > > const & observations,
  thermal::model::slab::Slab const & slab_initial,
  thermal::model::slab::Slab const & slab_substrate
) noexcept -> fitting_result
{
  assert( frequencies.size() > 0 );
  
  auto const numberPoints2Fit = frequencies.size();

  auto const minimizationEquation =
  [ & ] ( const double *x, double *fvec ) noexcept
  {
    auto const slabCurrent = updateSlab( x, slab_initial );
    
    auto const predictions =
    surface_phases( frequencies, slabCurrent, slab_substrate) ;
    
    //std::cout << slabCurrent.get_diffusivity() << "\n";
    //investigations::twoColorPyrometery::plot::phase_exp_model( frequencies, observations, predictions );
    
    auto const residual = [ & ]( const int i ) noexcept {
      return ( predictions[i]  -  observations[i] ).value() ;
    } ;

    auto i = 0;
    generate( fvec, fvec + numberPoints2Fit , [&]() noexcept {
      return residual( i++ );
    } ) ;
  };

  auto const myDiffusivity = slab_initial.get_diffusivity();
  auto unknownParameters = vector<double>{ myDiffusivity.value() } ;
  
  lmdif( minimizationEquation, numberPoints2Fit, unknownParameters, settings{});

  auto const model_slab = updateSlab( unknownParameters.data(), slab_initial );
  auto const model_observations = surface_phases( frequencies, model_slab, slab_substrate ) ;


  auto const results =  fitting_result
  (
    frequencies,
    slab_initial, model_slab, slab_substrate,
    observations ,model_observations
  );

  return results;
}

} // namespace two_layer_speciman
} // namespace analysis
} // namespace thermal
