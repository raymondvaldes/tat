//
//  coating_from_dimensionless.cpp
//  tat
//
//  Created by Raymond Valdes on 3/31/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/tbc2009/dimensionless/coating_from_dimensionless.h"
#include "thermal/model/tbc2009/dimensionless/a.h"
#include "thermal/model/tbc2009/dimensionless/gamma.h"
#include "thermal/define/conductivity.h"
#include "thermal/define/volumetricHeatCapacity.h"


namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless{

using thermal::define::conductivity;
using thermal::define::volumetricHeatCapacity;

auto coating_from_dimensionless
(
  units::quantity< units::si::length > const L_coat,
  ThermalProperties const tp,
  slab::Slab substrate
) noexcept -> slab::Slab
{
  auto const alpha_sub = substrate.get_diffusivity();
  auto const a = tp.a_sub;
  auto const gamma = tp.gamma;

  auto const alpha_coat = alphaCoat_from_a( a, alpha_sub );
  auto const e_sub = substrate.get_effusivity();
  auto const e_coat = eCoat_from_gamma( gamma, e_sub );
  auto const k_coat = conductivity( e_coat, alpha_coat ) ;

  return slab::Slab( L_coat, alpha_coat, k_coat );
}

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal
