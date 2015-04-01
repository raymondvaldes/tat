/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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
