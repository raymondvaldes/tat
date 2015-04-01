/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "algorithm/string/starts_with.h"

#include <boost/algorithm/string/predicate.hpp>

#include "algorithm/algorithm.h"

namespace algorithm {

namespace string {
  
bool starts_with( const std::string& check_this,
                  const std::string& begins_with ) noexcept
{
  using boost::starts_with;
  
  const bool pass = starts_with( check_this, begins_with ) ;
  return pass;
}

bool starts_with_not( const std::string& check_this,
                      const std::string& begins_with ) noexcept
{
  auto const startsWith = starts_with( check_this, begins_with ) ;
  return !startsWith ;
}

auto starts_with_not( const std::string & check_this,
                      const std::vector< std::string > & begins_with_these )
noexcept -> bool
{
  using algorithm::any_of;

  auto const val =
  any_of( begins_with_these, [ &check_this ]( auto const begins_with )
  {
    return starts_with( check_this, begins_with ) ;
  } ) ;
  
  return !val ;
}

} // namespace string

} // namespace algorithm
