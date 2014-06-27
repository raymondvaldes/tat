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

#ifndef __tat__interval__
#define __tat__interval__

#include <utility>
#include <vector>
#include <cstddef>


namespace math {
//namespace geometry {


struct Interval
{
private:
  double left_end;
  double right_end;

public:
  Interval( const std::pair<double, double> endpoints_input ) ;
  
  double get_left_end() const ;
  double get_right_end() const ;
  bool is_valid() const ;
  bool is_invalid() const;
  void set_ends( const std::pair<double, double> endpoints_input) ;
  Interval get_log10_random_subInterval() const ;
  std::pair<double, double> get_pair() const ;
  
  std::vector<std::vector<double>> random_group_xCR( const size_t val ) const;
  
  std::vector< std::pair<double,double>>
    ordered_group_xCR( const size_t iter ) const;
};


//}
}

#endif /* defined(__tat__interval__) */
