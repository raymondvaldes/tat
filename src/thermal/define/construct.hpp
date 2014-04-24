/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                         |
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

#ifndef __TAT__CONSTRUCT_HPP
#define __TAT__CONSTRUCT_HPP

#include "thermal/define/model_type.h"
#include <boost/property_tree/ptree.hpp>

namespace thermal{
  namespace define{
  
class construct
{

public:
  enum HeatX heat;
  enum EmissionX emission;

  construct & operator = (const construct & other);
  explicit construct( const enum HeatX myHeat,
                      const enum EmissionX myEmission );

  void update( const enum HeatX heat_in, const enum EmissionX emission_in );
  static construct loadConfigfromXML( const boost::property_tree::ptree pt );

  ~construct(void);
};

}}

#endif // __TAT__CONSTRUCT_HPP