//
//  get_real_component.h
//  tat
//
//  Created by Raymond Valdes on 10/29/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef get_real_component_h
#define get_real_component_h

#include <vector>
#include <complex>

namespace math{
namespace complex{
namespace container{

template< typename T >
std::vector< T > get_real_component( const std::vector< std::complex< T > > &input) noexcept
{
  const size_t size = input.size();
  std::vector< T > output( size );
  
  for( size_t i = 0; i < size ; ++i  )
    output[i] = input[i].real() ;

  return output;
};



}}}

#endif /* get_real_component_h */
