//
//  fit.cpp
//  tat
//
//  Created by Raymond Valdes on 10/19/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "fit_a_s_re_RC.hpp"

#include <cassert>
#include <vector>
#include <tuple>
#include <cmath>

#include "math/estimation/constrained.hpp"
#include "electronics/filter/low-pass/RC-first-order/resistance.h"
#include "electronics/filter/low-pass/RC-first-order/capacitance.h"
#include "theoretical_modeling.hpp"
#include "make_minimization_equation.hpp"
#include "fitting_algorithm.hpp"
#include "thermal/model/oneLayer2D/finite_disk/parameter_list.hpp"
#include "update_system_properties_generator.hpp"
#include "thermal/model/oneLayer2D/finite_disk/map_parameter_values.hpp"
#include "update_disk_optics.hpp"

#include "algorithm/algorithm.h"
using thermal::model::oneLayer2D::finite_disk::map_parameter_values;
using thermal::model::oneLayer2D::finite_disk::Map_parameter_values;

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
using namespace units;
using algorithm::for_each;
using std::make_pair;
using equipment::detector::View_radius;
using equipment::laser::Beam_radius;
using thermal::model::slab::Radius;
using thermal::model::slab::Thermal_diffusivity;
using electronics::filter::low_pass::RC_first_order::Time_constant;

inline auto Update_system_properties_generator(
  model::slab::Slab const & slab_initial,
  model::Optics const & optics_initial
) noexcept ->
  std::pair< std::vector<double> ,
    std::function<
    std::tuple<
      model::slab::Slab,
      model::Optics >( const double * x)> >
{
  using thermal::model::oneLayer2D::finite_disk::Parameters;

  auto const unknown_parameters = Parameters({
    thermal::model::oneLayer2D::finite_disk::Parameter::thermal_diffusivity,
    thermal::model::oneLayer2D::finite_disk::Parameter::specimen_radius,
    thermal::model::oneLayer2D::finite_disk::Parameter::detector_radius,
    thermal::model::oneLayer2D::finite_disk::Parameter::rc_filter
  });

  auto const size = unknown_parameters.size();
  auto const model_parameters = vector<double>( size, kx_limiter1( 1.0 ) );
  
  auto const scaling_factors =
  map_parameter_values( unknown_parameters, slab_initial, optics_initial  );


  // parameter estimation algorithm
  auto const update_system_properties =
  [ &slab_initial, &optics_initial, scaling_factors]
  ( const double * x ) noexcept
  {

    auto parameter_values = Map_parameter_values();
    auto i = 0u;
    for( auto const &factor : scaling_factors )
    {
      auto const parameter = factor.first;
      auto const scale = factor.second;
      auto const value = x_limiter1( x[i] ) * scale;
      parameter_values.emplace( std::make_pair( parameter, value ) );
      ++i;
    }

    auto const update =
    update_disk_optics( parameter_values, slab_initial, optics_initial );
    auto disk = update.first;
    auto const optics = update.second;
    

    auto const alpha = disk.thermal_diffusivity();
    auto const R = disk.radius();
    auto const Re = optics.view_radius;
    auto const RC_time_constant =  optics.filter_constant;

    std::cout <<  alpha << "\t" << R << "\t" << Re << "\t" << RC_time_constant <<  "\n" ;
    
    auto slab_updated = slab_initial;
      slab_updated.set_diffusivity_update_k_hold_rhoCp( alpha ); ///error here
      slab_updated.set_radius( R );
    
    return make_tuple( slab_updated, optics )  ;
  };

  return make_pair( model_parameters, update_system_properties );
};


auto fit_a_s_re_RC
(
  equipment::laser::Modulation_frequencies const & frequencies,
  emission::Phases const & exp_phases,
  model::slab::Slab const & slab_initial,
  model::Optics const & optics_initial
)
noexcept -> estimate_parameters::phase_analysis::Best_fit
{
  assert( !frequencies.empty() );
  assert( !exp_phases.empty() );
  assert( frequencies.size() == exp_phases.size() );
  
  using thermal::model::oneLayer2D::finite_disk::Parameters;
  auto const parameters = Parameters({
    thermal::model::oneLayer2D::finite_disk::Parameter::thermal_diffusivity,
    thermal::model::oneLayer2D::finite_disk::Parameter::specimen_radius,
    thermal::model::oneLayer2D::finite_disk::Parameter::detector_radius,
    thermal::model::oneLayer2D::finite_disk::Parameter::rc_filter
  });
  
  
  // parameter estimation algorithm
  auto const model =
  Update_system_properties_generator( slab_initial, optics_initial );

//  auto const model =
//  update_system_properties_generator( slab_initial, optics_initial, parameters);
  
  
  auto m_parameters = model.first;
  auto m_evaluate = model.second;
  
  auto const result =
  fitting_algorithm( frequencies, exp_phases, m_parameters , m_evaluate  );

  
 return result;
}

} } } } } }
