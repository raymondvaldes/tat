/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
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
#ifndef COMBINATIONS_HPP
#define COMBINATIONS_HPP

#include<vector>
#include<cstddef>

namespace math{
namespace algorithms{

template<typename OBJ>
std::vector< std::vector<OBJ> > combos_minusOne( const std::vector<OBJ> input ) noexcept
{
  using std::vector;
  
  const size_t N = input.size();
  vector< vector<OBJ> > output(N);

  size_t iter = 0;
  for( auto& val_o : input)
  {
    for( auto& val_i : input)
    {
      if( val_i != val_o )   
        { output[iter].push_back( val_i ) ; }
    }
    iter++;
  }

  return output;
}

size_t factorial( const size_t n ) noexcept;
size_t permutations( const size_t n, const size_t r) noexcept;

}}

#endif // COMBINATIONS_HPP
