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

#ifndef __tat__laser__
#define __tat__laser__

#include <iostream>

namespace thermal{
namespace equipment{

    
class Laser
{
private:
  double area(void) const;
  double IntensityTotal(void) const;
  double IntensitySteady(void) const;
  double IntensityTransient(void) const;
  double offset, amplitude;
  void update(void);
  
public:
  double Qlaser;
  double radius;
  double Is;
  double It;
  
  explicit Laser(const double a, const double b, const double c,
                 const double d);
  ~Laser();
  
  void updateRadius(const double r);
  void updatePower(const double Qpower);
};
  
  
}}

#endif /* defined(__tat__laser__) */
