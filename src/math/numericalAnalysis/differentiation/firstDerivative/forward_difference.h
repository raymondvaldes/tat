//
//  forward_difference.h
//  tat
//
//  Created by Raymond Valdes on 9/15/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__forward_difference__
#define __tat__forward_difference__

namespace math {
namespace numericalAnalysis {
namespace differentiation {
namespace firstDerivative {

template <typename Type>
Type forward_difference( Type func, Type func_plus,
                         Type dx )
{
  const Type output = ( func_plus - func ) / dx ;
  return output;
}

}}}}


#endif /* defined(__tat__forward_difference__) */
