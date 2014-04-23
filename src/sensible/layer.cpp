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

#include "sensible/layer.h"
#include "thermal/define/diffusivity.h"
#include "thermal/define/effusivity.hpp"

namespace sensible{
  
  using boost::property_tree::ptree;
  
  
layer::layer( const property kthermal_, const property psithermal_,
              const double depth_, const double lambda_ )
: kthermal( kthermal_ ),
  psithermal( psithermal_ ),
  depth( depth_ ),
  lambda( lambda_ )
{}

double layer::opticalPenetration(void) const
{
  return lambda * depth;
}

double layer::thermalDiffusivity( void ) const
{
  using thermal::define::diffusivity;
  return diffusivity( kthermal.offset, psithermal.offset );
}
double layer::thermalEffusivity( void ) const
{
  using thermal::define::effusivity;
  return effusivity( kthermal.offset, psithermal.offset );
}

layer::~layer(void){}

layer layer::loadConfigfromXMLTree( const ptree pt )
{
  
  const ptree branch1 = pt.get_child("conductivity");
  const property conductivity_ = property::loadConfigfromXMLTree(branch1);
  
  const ptree branch2 = pt.get_child("thermalmass");
  const property thermalMass_  = property::loadConfigfromXMLTree(branch2);
  
  const double lambda_ = pt.get<double>("lambda");
  const double length_ = pt.get<double>("length");
  
  layer layerObj(conductivity_, thermalMass_, length_, lambda_ );
  return layerObj;
}
  

}
