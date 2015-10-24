//
//  update_system_properties_generator.cpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "update_system_properties_generator.hpp"

#include <cassert>
#include <vector>
#include <tuple>
#include <cmath>
#include "algorithm/algorithm.h"

#include "math/estimation/constrained.hpp"
#include "electronics/filter/low-pass/RC-first-order/resistance.h"
#include "electronics/filter/low-pass/RC-first-order/capacitance.h"
#include "thermal/model/oneLayer2D/finite_disk/map_parameter_values.hpp"
#include "thermal/model/oneLayer2D/finite_disk/update_disk_optics.hpp"

namespace thermal { 
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

using electronics::filter::low_pass::RC_first_order::Resistance;
using electronics::filter::low_pass::RC_first_order::Capacitance;
using electronics::filter::low_pass::RC_first_order::Time_constant;
using math::estimation::x_limiter1;
using math::estimation::kx_limiter1;
using std::vector;
using std::make_tuple;
using std::make_pair;
using namespace units;

using thermal::model::oneLayer2D::finite_disk::map_parameter_values;
using thermal::model::oneLayer2D::finite_disk::update_disk_optics;
using thermal::model::oneLayer2D::finite_disk::Map_parameter_values;

using algorithm::for_each;
using std::make_pair;
using equipment::detector::View_radius;
using equipment::laser::Beam_radius;
using thermal::model::slab::Radius;
using thermal::model::slab::Thermal_diffusivity;
using electronics::filter::low_pass::RC_first_order::Time_constant;
 


auto update_system_properties_generator(
  model::slab::Slab const & slab_initial,
  model::Optics const & optics_initial,
  model::oneLayer2D::finite_disk::Parameters const & unknown_parameters
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
    

    auto const alpha = slab_updated.thermal_diffusivity();
    auto const R = slab_updated.radius();
    auto const Re = optics_updated.view_radius;
    auto const RC_time_constant = optics_updated.filter_constant;
    std::cout <<  alpha << "\t" << R << "\t" << Re << "\t" << RC_time_constant <<  "\n" ;
    
    
    return make_tuple( slab_updated, optics_updated ) ;
    
  };
  
  return make_pair( model_parameters, update_system_properties );
}


} } } } } }
