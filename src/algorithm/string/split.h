/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__split__
#define __tat__split__


#include <vector>
#include <string>

namespace algorithm{

namespace string{

auto split
(
  const std::string & strs,
  const std::string & splitter
)
noexcept -> std::vector<std::string>;
  
} // namespace string

} // namespace algorithm



#endif /* defined(__tat__split__) */
