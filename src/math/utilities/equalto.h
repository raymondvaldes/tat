/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__equalto__
#define __tat__equalto__

#include <cmath>
#include <limits>


namespace math {
  
template< typename T1, typename T2 >
bool equalto ( const T1 a, const T2 b ) noexcept
{
  using std::abs;
  using std::numeric_limits;

  const double multi = ( a > b ? a : b ) ;
  const double multi2 = ( multi >= 1 ? multi  : 1 ) ;

  return ( abs(a - b) < ( numeric_limits<double>::epsilon()) * multi2 );
}  
  
}

#endif /* defined(__tat__equalto__) */
