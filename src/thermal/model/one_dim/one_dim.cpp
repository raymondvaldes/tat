/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
 -------------------------------------------------------------------------------
 License
 This file is part of Thermal Analysis Toolbox.
 
 Thermal Analysis Toolbox is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or (at your
 option) any later version.
 
 Thermal Analysis Toolbox is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License along with
 Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.
 
\*----------------------------------------------------------------------------*/

#include "thermal/model/one_dim/one_dim.h"

namespace thermal{ namespace model {namespace one_dim{

one_dim::one_dim(
  const sensible::layer &coating_in,
  const sensible::layer &substrate_in,
  const sensible::radiativeSysProp &radiative_prop_in,
  const thermal::equipment::Laser &laser_in,
  const double temp_in,
  const double gamma_in )
  :
  coat( coating_in.kthermal.offset, coating_in.psithermal.offset,
        coating_in.getDepth(), coating_in.getLambda() ),
  coat_full( coating_in ),
  sub_full( substrate_in ), 
  I_intensity_ss(             laser_in.Is ),
  I_intensity_tt(             laser_in.It ),
  Temperature_interface(      temp_in ),
  gamma(                      gamma_in ),
  R1(                         radiative_prop_in.R1 ),
  Emit1(                      radiative_prop_in.Emit1 )
{}
  
one_dim::~one_dim( void ) {}

}}}