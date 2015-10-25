//
//  update_disk_optics.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "update_disk_optics.hpp"
#include "algorithm/algorithm.h"
#include <utility>

namespace thermal{
namespace model{
namespace oneLayer2D{

using algorithm::for_each;
using std::make_pair;
using equipment::detector::View_radius;
using equipment::laser::Beam_radius;
using thermal::model::slab::Radius;
using thermal::model::slab::Thermal_diffusivity;
using electronics::filter::low_pass::RC_first_order::Time_constant;
  
auto update_disk_optics
(
  Map_parameter_values const & parameter_values,
  Disk const & disk,
  Optics const & optics
) noexcept -> std::pair< Disk, Optics >
{
  auto d = disk;
  auto o = optics;
  
  auto assign_value_to_disk_optics = [ &d, &o ]( auto const &p ) noexcept
  {
    auto const parameter = p.first;
    auto const value = p.second;
    
    switch( parameter ) {
      case Parameter::detector_radius : {
        o.view_radius = View_radius::from_value( value );
        break;
      }
      case Parameter::laser_radius : {
        o.laser_radius = Beam_radius::from_value( value );
        break;
      }
      case Parameter::specimen_radius : {
        d.set_radius( Radius::from_value( value )  );
        break;
      }
      case Parameter::thermal_diffusivity : {
        d.set_diffusivity_update_k_hold_rhoCp(
          Thermal_diffusivity::from_value( value ) );
        break;
      }
      case Parameter::rc_filter : {
        o.filter_constant = Time_constant::from_value( value );
      }
    }
  };
  
  for( auto const p : parameter_values ) {
    assign_value_to_disk_optics( p );
  }
  

  return make_pair( d, o );
}

}}}
