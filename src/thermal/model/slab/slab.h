//
//  slab.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_model_slab_slab_9342_
#define __tat_thermal_model_slab_slab_9342_

#include "units.h"

namespace thermal {
namespace model{
namespace slab {

using Thickness = units::quantity<units::si::length, double>;
using Radius = units::quantity<units::si::length, double>;
using Thermal_diffusivity = units::quantity< units::si::thermal_diffusivity, double>;
using Thermal_conductivity = units::quantity< units::si::thermal_conductivity, double>;
using Volumetric_heat_capacity =
  units::quantity< units::si::volumetric_heat_capacity, double>;
using Thermal_effusivity = units::quantity< units::si::thermal_effusivity, double>;
using Biot_number = units::quantity< units::si::dimensionless, double>;

class Slab
{
private:
  Thickness L;
  Thermal_conductivity k;
  Volumetric_heat_capacity rhoCp;
  Radius R;

public:
  Biot_number Bi1 = 0.001;
  Biot_number Bi2 = 0.001;
  
  Slab(
    Thickness const L,
    Thermal_diffusivity const alpha_in,
    Thermal_conductivity const k_in,
    Radius const R = Radius( 25.0 * units::si::millimeters )
  );
  
  Slab(
    Thickness const L,
    Thermal_diffusivity const alpha_in,
    Volumetric_heat_capacity const rhoCp_in,
    Radius const R = Radius( 25.0 * units::si::millimeters)
    
  );
  
  Slab(
    Thickness const L,
    Thermal_conductivity const k_in,
    Volumetric_heat_capacity const rhoCp_in,
    Radius const R = Radius( 25.0 * units::si::millimeters )
  );
  
  // getters
  auto radius() const -> Radius;
  auto thickness() const -> Thickness;
  
  auto thermal_conductivity() const -> Thermal_conductivity;
  auto volumetric_heatCapacity() const -> Volumetric_heat_capacity;
  auto thermal_diffusivity() const -> Thermal_diffusivity;
  auto thermal_effusivity() const -> Thermal_effusivity;


  // setters
  auto set_thickness( Thickness const L ) -> void;
  auto set_radius( Radius const R ) -> void;
  
  auto set_effusivity_update_k_hold_rhoCp ( Thermal_effusivity const e )
  -> void;
  
  auto set_effusivity_update_rhoCp_hold_k ( Thermal_effusivity const e )
  -> void;
  
  auto set_diffusivity_update_k_hold_rhoCp ( Thermal_diffusivity const alpha )
  -> void;
  
  auto set_diffusivity_update_rhoCp_hold_k ( Thermal_diffusivity const alpha )
  -> void;
  
  auto set_conductivity( Thermal_conductivity const k ) -> void;
  
  auto set_volumetric_heatCapacity( Volumetric_heat_capacity const rhoCp_in )
  -> void;
};

}}}

#endif /* defined(__tat__slab__) */
