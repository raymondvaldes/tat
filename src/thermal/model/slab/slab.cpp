//
//  slab.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <complex>

#include "thermal/model/slab/slab.h"

#include "thermal/define/volumetricHeatCapacity.h"
#include "thermal/define/effusivity.hpp"
#include "thermal/define/diffusivity.h"
#include "thermal/define/conductivity.h"

namespace thermal { namespace model { namespace slab{

  using thermal::define::conductivity;
  using thermal::define::volumetricHeatCapacity;
  using thermal::define::volumetricHeatCapacity;


Slab::Slab(
  Thickness const L,
  Thermal_diffusivity const alpha_in,
  Thermal_conductivity const k_in,
  Radius const R

)
  : L( L ),
    k( k_in ),
    rhoCp( thermal::define::volumetricHeatCapacity( alpha_in, k )  ),
    R( R )
{
  assert( alpha_in.value() > 0 ) ;
  assert( k_in.value() > 0 ) ;
  assert( rhoCp.value() > 0 ) ;

  assert( L.value() > 0 ) ;
  assert( R.value() > 0 );
};


Slab::Slab(
  Thickness const L,
  Thermal_diffusivity const alpha_in,
  Volumetric_heat_capacity const rhoCp_in,
  Radius const R
) :Slab(
    L,
    alpha_in,
    thermal::define::conductivity( rhoCp_in, alpha_in) ,
    R ) {}

Slab::Slab(
  Thickness const L,
  Thermal_conductivity const k_in,
  Volumetric_heat_capacity const rhoCp_in,
  Radius const R
) :Slab(
    L,
    thermal::define::diffusivity( k_in , rhoCp_in ),
    k_in, R ) {}
  

auto Slab::radius() const -> Radius
{
  return R;
}
  
auto Slab::thickness() const -> Thickness
{
  return L;
}

auto Slab::set_thickness( Thickness const L ) -> void
{
  this->L = L;
}

auto Slab::set_radius( Radius const R ) -> void
{
  this->R = R;
}


auto Slab::thermal_conductivity() const -> Thermal_conductivity
{
  return k;
}

auto Slab::volumetric_heatCapacity() const -> Volumetric_heat_capacity
{
  return rhoCp;
}

auto Slab::thermal_diffusivity() const -> Thermal_diffusivity
{
  using thermal::define::diffusivity;
  auto const alpha_here = diffusivity( k, rhoCp );
  return alpha_here;
}

auto Slab::thermal_effusivity() const -> Thermal_effusivity
{
  using thermal::define::effusivity;
  auto const e = effusivity( k , rhoCp );
  return e;
}

auto Slab::set_conductivity ( Thermal_conductivity const k_in ) -> void
{
  k = k_in;
}

auto Slab::set_volumetric_heatCapacity
( Volumetric_heat_capacity const rhoCp_in ) -> void
{
  rhoCp = rhoCp_in;
}

auto Slab::set_effusivity_update_k_hold_rhoCp
( Thermal_effusivity const e ) -> void
{
  auto const updated_k = conductivity( rhoCp,  e ) ;
  set_conductivity( updated_k );
}

auto Slab::set_effusivity_update_rhoCp_hold_k
( Thermal_effusivity const e ) -> void
{
  auto const updated_rhoCp = volumetricHeatCapacity( e, k ) ;
  
  set_volumetric_heatCapacity( updated_rhoCp );
}

auto Slab::set_diffusivity_update_k_hold_rhoCp
( Thermal_diffusivity const alpha_in ) -> void
{
  auto const updated_k = conductivity( rhoCp,  alpha_in ) ;
  set_conductivity( updated_k );
}

auto Slab::set_diffusivity_update_rhoCp_hold_k
( Thermal_diffusivity const alpha_in ) -> void
{
  auto const updated_rhoCp = volumetricHeatCapacity(alpha_in, k) ;
  
  set_volumetric_heatCapacity( updated_rhoCp );
}

} } } // thermal::model::slab
