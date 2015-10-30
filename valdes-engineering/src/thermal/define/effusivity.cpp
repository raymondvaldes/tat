/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include <cmath>
#include <cassert>
#include "thermal/define/effusivity.hpp"

namespace thermal{
namespace define{

using namespace units;
using std::sqrt;

double effusivity( const double k, const double rhoCp ) noexcept
{
  return sqrt( k * rhoCp ) ;
}

auto effusivity
(
  units::quantity< units::si::thermal_conductivity > const k,
  units::quantity< units::si::volumetric_heat_capacity > const rhoCp
)
noexcept -> units::quantity< units::si::thermal_effusivity >
{
  assert( k.value() > 0 );
  assert( rhoCp.value() > 0 );

  auto const e = sqrt( k * rhoCp ) ;
  return e;
}
    
} // namespace define
} // namespace thermal
