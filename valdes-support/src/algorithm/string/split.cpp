/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <boost/algorithm/string.hpp>
#include "algorithm/string/split.h"

namespace algorithm{

namespace string{

auto split
(
  const std::string& strs,
  const std::string& splitter
) noexcept -> std::vector< std::string >
{
  using std::vector;
  using std::string;
  
  using boost::is_any_of;
  using boost::token_compress_on;
  
  auto SplitVec = vector< string >();
  
  split( SplitVec, strs, is_any_of( splitter ), token_compress_on );
 
  return SplitVec;
}
  

} // namespace string

} // namespace algorithm
