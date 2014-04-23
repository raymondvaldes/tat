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

#ifndef __tat__property__sensible
#define __tat__property__sensible

#include <iostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "thermal/define/temperature.h"

namespace sensible{
  
  using std::vector;
  using boost::property_tree::ptree;
  using thermal::define::Temperature;
  
class property
{
private:
  static constexpr bool tempDependent = false;
  double Current( const double temperature) const;
  
  double Projected( const double temperature1, const double temperature2) const;
  
public:
  double offset;
  double slope;
  
  explicit property(const double offset_,const double slope_);
  explicit property(void);
  
  double Current(const vector<vector<double>>& T, const size_t n,
                 const size_t j) const;
  
  double Current(const vector<vector<double>>& T, const size_t n,
                 const size_t j1, const size_t j2) const;
  
  
  double Current(const Temperature Tprofile, const size_t n,
                 const size_t j) const;
  
  double Current(const Temperature Tprofile, const size_t n,
                 const size_t j1, const size_t j2) const;
  
  
  double Projected(const vector< vector<double>>& T,
                   const size_t n, const size_t j) const;
  
  double Projected(const vector< vector<double>>& T, const size_t n,
                   const size_t j1, const size_t j2) const;
  
  double Projectedt( const vector< vector<double>>& T,
                     const size_t n, const size_t, const size_t j) const;
  
  double Projected( const Temperature Tprofile,
                    const size_t n, const size_t j) const;
  
  double Projected(const Temperature Tprofile, const size_t n,
                   const size_t j1, const size_t j2) const;
  
  double Projectedt(const Temperature Tprofile,
                    const size_t n, const size_t, const size_t j)
  const;
  static property loadConfigfromXMLTree(const ptree pt);
};

  
}

#endif /* defined(__tat__property__sensible) */
