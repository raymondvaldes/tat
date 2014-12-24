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

#include "algorithm/string/split.h"

namespace algorithm{
namespace string{

std::vector<std::string> split( const std::string& strs,
                                const std::string& splitter ) noexcept {
  using std::vector;
  using std::string;
  
  using boost::is_any_of;
  using boost::token_compress_on;
  
  typedef vector< string > split_vector_type;
  
  split_vector_type SplitVec;
  split( SplitVec, strs, is_any_of( splitter ), token_compress_on );
 
  return SplitVec;
}
  

}}