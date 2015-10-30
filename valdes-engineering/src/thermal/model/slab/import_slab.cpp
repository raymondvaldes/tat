//
//  import_slab.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/14/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/slab/import_slab.h"
#include "tools/interface/xml.h"
#include "units.h"

namespace thermal {

namespace model {

namespace slab {

using tools::interface::getTreefromFile;

using units::quantity;
using units::si::thermal_conductivity;
using units::si::length;
using units::si::micrometers;
using units::si::kelvin;
using units::si::square_millimeters;
using units::si::watts;
using units::si::second;
using units::si::thermal_diffusivity;
using units::si::meter;

auto
import
(
  filesystem::directory const & dir ,
  std::string const & filename
) -> Slab
{
  using std::string;
  auto const slab_ptree = getTreefromFile( dir.abs( filename ) ) ;
  auto const settings_tree = slab_ptree.get_child( "slab.properties");

  auto const thickness_value  = settings_tree.get<double>( "thickness" );
  
  auto const thickness = quantity< length >( thickness_value * micrometers );

  auto const k_value = settings_tree.get<double>("thermal_conductivity");
  auto const k =
  quantity< thermal_conductivity >( k_value  * watts / ( meter * kelvin ) );

  auto const alpha_value = settings_tree.get<double>("thermal_diffusivity");
  auto const alpha =
  quantity<thermal_diffusivity>( alpha_value * square_millimeters / second );
  
  auto const mySlab_off = Slab{ thickness, alpha, k };

  return mySlab_off;
}
  
} // namespace slab
  
} // namespace model
  
} // namespace thermal
