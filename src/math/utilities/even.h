//
//  even.h
//  tat
//
//  Created by Raymond Valdes_New on 3/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_even_h
#define tat_even_h

namespace math {

namespace utilities {
  
template< typename integer >
bool is_even( const integer x ) noexcept
{
  //cannot pass double because of modulus (template is for uint and int)
  const bool pass = ( (x % 2) == 0 ) ;
  return pass;
}
  
} // namespace utilities
  
} // namespace math

#endif
