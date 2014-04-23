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

#ifndef __tat__labels__thermal_model
#define __tat__labels__thermal_model

#include <iostream>
#include <cstddef>
#include <string>

#include <boost/bimap.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/assign/list_of.hpp>

namespace thermal{
  namespace model{

class labels
{
public:
  enum class Name: uint8_t
  {
    gammaEff,
    asub,
    E1,
    R1,
    lambda,
    thermalCenter,
    thermalRange
  };
  
  typedef boost::bimap< enum Name , std::string > NameBiTYPE;
  const NameBiTYPE nameMap =
  boost::assign::list_of < NameBiTYPE::relation >
  ( Name::gammaEff , "gammaEff")
  ( Name::asub     , "asub")
  ( Name::E1       , "E1")
  ( Name::R1       , "R1")
  ( Name::lambda   , "lambda")
  ( Name::thermalCenter, "thermalCenter")
  ( Name::thermalRange, "thermalRange");
  
  explicit labels(void);
  explicit labels(const enum Name name_);
  Name getName(void) const;
  std::string getNameString(void) const;
  
  labels& operator=( const labels& that );
  
private:
  enum Name name;
};

  }
}
#endif /* defined(__tat__labels__thermal_model) */
