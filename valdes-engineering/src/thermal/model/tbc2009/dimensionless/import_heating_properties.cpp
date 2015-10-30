//
//  import_heating_properties.cpp
//  tat
//
//  Created by Raymond Valdes on 4/1/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "import_heating_properties.h"

namespace thermal {
namespace model {
namespace tbc2009 {
namespace dimensionless {

using std::string;
using namespace units;
using tools::interface::getBranch;
using tools::interface::getTreefromFile;

auto import_heating_properties
(
  filesystem::directory const & dir ,
  std::string const & filename
) -> HeatingProperties
{

  auto const slab_ptree = getTreefromFile( dir.abs( filename ) ) ;
  auto const settings_tree = slab_ptree.get_child( "heating.properties");

  auto const R0_val  = settings_tree.get<double>( "R0" );
  auto const R0 = quantity< si::dimensionless >( R0_val );
  
  auto const R1_val  = settings_tree.get<double>( "R1" );
  auto const R1 = quantity< si::dimensionless >( R1_val );
 
  auto const Lambda_val  = settings_tree.get<double>( "Lambda" );
  auto const Lambda = quantity< si::dimensionless >( Lambda_val );

  auto const b_val  = settings_tree.get<double>( "b" );
  auto const b = quantity< si::dimensionless >( b_val );
  
  
  auto const hp = HeatingProperties( Lambda , R0, R1, b );
  return hp;
}

} // namespace dimensionless
} // namespace tbc2009
} // namespace model
} // namespace thermal
