/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__starts_with__
#define __tat__starts_with__

#include <string>
#include <vector>

namespace algorithm {

namespace string {
  
bool starts_with( const std::string& check_this,
                  const std::string& begins_with ) noexcept;
  
bool starts_with_not( const std::string& check_this,
                      const std::string& begins_with ) noexcept;

bool starts_with_not( const std::string & check_this,
                      const std::vector< std::string> & begins_with ) noexcept;

auto starts_with_not( const std::string & check_this,
                      const std::vector< std::string > & begins_with_these )
noexcept -> bool;

} // namespace string

} // namespace algorithm

#endif /* defined(__tat__starts_with__) */
