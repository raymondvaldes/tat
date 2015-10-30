//
//  lthermal_at_frequency.cpp
//  tat
//
//  Created by Raymond Valdes on 8/29/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include <iostream>

#include "lthermal_at_frequency.hpp"
#include "thermal/model/oneLayer2D/infinite_disk/dimensionless/thermal_penetration.h"
#include "thermal/model/oneLayer2D/infinite_disk/dimensional/thermal_penetration.hpp"
#include "units.h"

namespace investigations {
namespace twoColorPyrometery {
namespace oneLayer2D{
namespace calculators{
namespace thermal_penetration{

using std::cout;
using namespace units;
namespace nondimensional = thermal::model::oneLayer2D::dimensionless;
namespace dimensional =  thermal::model::oneLayer2D::dimensional;
  
auto lthermal_at_frequency( filesystem::directory const & ) -> void
{
  auto const diffusivity = quantity<si::thermal_diffusivity>( 70 * square_millimeters / second );
  auto const L = quantity< si::length >( 0.6 * millimeters );
  auto const frequency = 362  * hertz;
  
  auto const lthermal_nd =
  nondimensional::thermal_penetration( frequency, L, diffusivity );
  
  auto const lthermal =
  dimensional::thermal_penetration( frequency, diffusivity );
  
  cout << "The length scale is " << L <<".\n";
  cout << "Thermal diffusivity is " << diffusivity << ".\n";
  cout << "The modulation frequency is " << frequency << ".\n\n";
  cout << "The dimensionless thermal penetration is: " << lthermal_nd << ".\n";
  cout << "The dimensional thermal penetration is: " << lthermal << ".\n";

}
  
} // namespace thermal_penetration
} // namespace calculators
} // namespace oneLayer2D
} // namespace twoColorPyrometery
} // namespace investigations
