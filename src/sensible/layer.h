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

#ifndef __tat__layer__sensible
#define __tat__layer__sensible

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include "sensible/property.h"

namespace sensible{

class layer
{
private:
  double depth;
  double Lambda;
  double getOpticalPenetration( void ) ;
  
public:
  property kthermal;
  property psithermal;
  double c = 1;

  double opticalPenetration(void) const;
  double thermalDiffusivity(void) const;
  double thermalEffusivity(void) const;

  explicit layer( const property kthermal_,
                  const property psithermal_,
                  const double depth_, const double lambda_);
  ~layer(void);
  static layer loadConfigfromXMLTree( const boost::property_tree::ptree pt );
  double getDepth( void ) const;
  double getLambda( void ) const;
  void setDepth( const double depth_in ) ;
  void setLambda( const double Lambda_in ) ;
};


}

#endif /* defined(__tat__layer__sensible) */
