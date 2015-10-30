//
//  slab.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <complex>
#include <cmath>
#include <gsl.h>

#include "thermal/model/slab/slab.h"

#include "thermal/define/volumetricHeatCapacity.h"
#include "thermal/define/effusivity.hpp"
#include "thermal/define/diffusivity.h"
#include "thermal/define/conductivity.h"

namespace thermal { namespace model { namespace slab{

  using thermal::define::conductivity;
  using thermal::define::volumetricHeatCapacity;
  using thermal::define::effusivity;
  using thermal::define::diffusivity;
  using std::isnormal;
  using namespace units;

Slab::Slab(
  Thickness const L,
  Thermal_diffusivity const alpha,
  Thermal_conductivity const k_in,
  Radius const R

) noexcept
  : L( L ),
    k( k_in ),
    rhoCp( volumetricHeatCapacity( alpha, k )  ),
    R( R )
{
  assert( alpha.value() > 0  && isnormal( alpha.value() ) ) ;
  assert( k_in.value() > 0 && isnormal( k_in.value() )) ;
  assert( rhoCp.value() > 0 && isnormal( rhoCp.value() ) ) ;

  assert( L.value() > 0 && isnormal( L.value() )) ;
  assert( R.value() > 0 && isnormal( R.value() )) ;
};


Slab::Slab(
  Thickness const L,
  Thermal_diffusivity const alpha_in,
  Volumetric_heat_capacity const rhoCp_in,
  Radius const R
) noexcept :Slab(
    L,
    alpha_in,
    conductivity( rhoCp_in, alpha_in) ,
    R ) {}

Slab::Slab(
  Thickness const L,
  Thermal_conductivity const k_in,
  Volumetric_heat_capacity const rhoCp_in,
  Radius const R
) noexcept :Slab(
    L,
    diffusivity( k_in , rhoCp_in ),
    k_in, R ) {}
  

auto Slab::radius() const noexcept -> Radius
{
  return R;
}
  
auto Slab::thickness() const noexcept -> Thickness
{
  return L;
}




auto Slab::set_thickness( Thickness const L ) noexcept -> void
{
  this->L = L;
}

auto Slab::set_radius( Radius const R ) noexcept -> void
{
  this->R = R;
}


auto Slab::thermal_conductivity() const noexcept-> Thermal_conductivity
{
  return k;
}

auto Slab::volumetric_heatCapacity() const noexcept -> Volumetric_heat_capacity
{
  return rhoCp;
}

auto Slab::thermal_diffusivity() const noexcept -> Thermal_diffusivity
{
  auto const alpha = diffusivity( k, rhoCp );
  
  assert( alpha.value() > 0  && isfinite(alpha) );
  return alpha;
}

auto Slab::thermal_effusivity() const noexcept -> Thermal_effusivity
{
  auto const e = effusivity( k , rhoCp );

  assert( e.value() > 0  && isfinite(e) );
  return e;
}

auto Slab::set_conductivity ( Thermal_conductivity const k ) noexcept -> void
{
  assert( k.value() > 0  && isfinite( k ) );
  this->k = k;
}

auto Slab::set_volumetric_heatCapacity
( Volumetric_heat_capacity const rhoCp ) noexcept -> void
{
  assert( rhoCp.value() > 0  && isfinite( rhoCp ) );
  this->rhoCp = rhoCp;
}

auto Slab::set_effusivity_update_k_hold_rhoCp
( Thermal_effusivity const e ) noexcept -> void
{
  assert( e.value() > 0  && isfinite( e ) );

  auto const k = conductivity( rhoCp,  e ) ;
  set_conductivity( k );

  assert( this->k.value() > 0  && isfinite( this->k ) );
}

auto Slab::set_effusivity_update_rhoCp_hold_k
( Thermal_effusivity const e ) noexcept -> void
{
  assert( e.value() > 0  && isfinite( e ) );

  auto const rhoCp = volumetricHeatCapacity( e, k ) ;
  set_volumetric_heatCapacity( rhoCp );

  assert( this->rhoCp.value() > 0  && isfinite( this->rhoCp ) );
}

auto Slab::set_diffusivity_update_k_hold_rhoCp
( Thermal_diffusivity const alpha ) noexcept -> void
{
  Expects( alpha.value() > 0  && isfinite( alpha ) );
  
  auto const k = conductivity( rhoCp,  alpha ) ;
  set_conductivity( k );
  
  Ensures( abs(thermal_diffusivity() - alpha ).value() < 1e-14 );
  Ensures( this->k.value() > 0  && isfinite( this->k )  );
}

auto Slab::set_diffusivity_update_rhoCp_hold_k
( Thermal_diffusivity const alpha ) noexcept -> void
{
  Expects( alpha.value() > 0  && isfinite( alpha ) );

  auto const rhoCp = volumetricHeatCapacity( alpha, k ) ;
  set_volumetric_heatCapacity( rhoCp );
  
  Ensures( abs(thermal_diffusivity() - alpha ).value() < 1e-14 );
  Ensures( this->rhoCp.value() > 0  && isfinite( this->rhoCp ) );
}

} } } // thermal::model::slab
