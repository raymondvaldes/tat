//
//  update_system_properties_generator.cpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "update_system_properties_generator.hpp"

#include <cassert>
#include <vector>
#include <tuple>
#include <cmath>

#include "math/estimation/constrained.hpp"
#include "thermal/model/oneLayer2D/map_parameter_values.hpp"
#include "thermal/model/oneLayer2D/update_disk_optics.hpp"

namespace thermal{
namespace analysis{
namespace oneLayer2D {

using math::estimation::x_limiter1;
using math::estimation::kx_limiter1;
using std::vector;
using std::make_tuple;
using std::make_pair;
using namespace units;

using thermal::model::oneLayer2D::map_parameter_values;
using thermal::model::oneLayer2D::update_disk_optics;
using thermal::model::oneLayer2D::Map_parameter_values;

auto update_system_properties_generator(
  model::slab::Slab const & slab_initial,
  model::Optics const & optics_initial,
  model::oneLayer2D::Parameters const & unknown_parameters
)
 noexcept ->
  std::pair< std::vector<double> ,
    std::function<
    std::tuple<
      model::slab::Slab,
      model::Optics  >( const double * x )  >
      >
{
  auto const size = unknown_parameters.size();
  auto const model_parameters = vector<double>( size, kx_limiter1( 1.0 ) );
  
  auto const scaling_factors =
  map_parameter_values( unknown_parameters, slab_initial, optics_initial  );

  
  auto const update_system_properties =
  [ scaling_factors, slab_initial, optics_initial, size]
  ( const double * x ) noexcept
  {
    auto parameter_values = Map_parameter_values();
    auto i = 0u;
    
    for( auto const &factor : scaling_factors )
    {
      auto const parameter = factor.first;
      auto const scale = factor.second;
      auto const value = x_limiter1( x[i] ) * scale;
      parameter_values.emplace( make_pair( parameter, value ) );
      ++i;
    }
    
    auto const update =
    update_disk_optics( parameter_values, slab_initial, optics_initial );
    
    auto const slab_updated = update.first;
    auto const optics_updated = update.second;
    
    ///DELETE THIS
//    auto const alpha = slab_updated.thermal_diffusivity();
//    auto const R = slab_updated.radius();
//    auto const Re = optics_updated.view_radius;
//    auto const RC_time_constant = optics_updated.filter_constant;
   // std::cout <<  alpha << "\t" << R << "\t" << Re << "\t" << RC_time_constant <<  "\n" ;
    //DELETE THIS
    
    return make_tuple( slab_updated, optics_updated ) ;
    
  };
  
  return make_pair( model_parameters, update_system_properties );
}

}
}
}
