//
//  central_difference.h
//  tat
//
//  Created by Raymond Valdes on 9/15/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__central_difference__
#define __tat__central_difference__

namespace math {
namespace numericalAnalysis {
namespace differentiation {
namespace firstDerivative {



template <typename Type, typename Element>
Type centralDifference( const Type func_plus, const Type func_minus, 
                        const Element dx)
{
  const Type output = ( func_plus - func_minus )  / ( 2 * dx) ;
  return output;
}

template <typename Type, typename Element>
Type central_difference_partial( const Type func_pp, const Type func_pm,
                                 const Type func_mp, const Type func_mm,
                                 const Element dx )
{
  Type
  output  = func_pp ;
  output -= func_pm ;
  output -= func_mp ;
  output += func_mm ;

  output /= 4 * dx * dx ;
  
  return output;
}




}}}}
#endif /* defined(__tat__central_difference__) */
