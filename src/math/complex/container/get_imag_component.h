//
//  get_imag_component.h
//  tat
//
//  Created by Raymond Valdes on 10/29/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef get_imag_component_h
#define get_imag_component_h

#include <vector>
#include <complex>

namespace math{
namespace complex{
namespace container{

template< typename T >
std::vector< T > get_imag_component( const std::vector< std::complex< T > > &input) noexcept
{
  using std::vector;

  const size_t size = input.size();
  vector< T > output( size );
  
  for( size_t i = 0; i < size ; ++i  )
    output[i] = input[i].imag() ;

  return output;
};


}}}

#endif /* get_imag_component_h */
