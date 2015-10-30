//
//  radial_temperature_gradient.cpp
//  tat
//
//  Created by Raymond Valdes on 8/5/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "surface_non_dimensional.hpp"

/*
This function takes a look at the surface temperature profile and uses it to 
calculate the tempearture gradient. I am interested in finding when the 
temperature gradient approaches zero.  This is for the transient problem only.
Intersted in the nondimensional temperature only!
*/

namespace investigations {
namespace twoColorPyrometery{
namespace oneLayer2D{
namespace radial_temperature_gradient{

auto surface_non_dimensional( filesystem::directory const &)
noexcept -> void
{
//load model
// calculate tempeature firled
// do finite differencing
// determine resolution
// forward-difference?
// create tempearture field
// calculate derivative
// (T, r)
// create log field
// first point (second order forward differencing)
// middle points (central differencing)
// final point (second order backwrad differencing)

//estimate error?
// Use two grid approach
//

//output gradient info, error for each value
/// (quantity, derivative, + error)




}

} // namespace
} // namespace
} // namespace
} // namespace

