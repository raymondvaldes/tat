//
//  mod_phase_to_complex.h
//  tat
//
//  Created by Raymond Valdes on 10/29/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef mod_phase_to_complex_h
#define mod_phase_to_complex_h

#include <complex>
#include <cmath>

namespace math{
namespace complex{

template< typename T >
std::complex< T >
mod_phase_to_complex( const T mod, const T arg ) noexcept
{
  using std::complex;
  using std::exp;
  const complex< T > _I_(0.,1.);
  complex< T > output(0.,0.);
  
  output = mod * exp( _I_ * arg ) ;

  return output;
};

}
}

#endif /* mod_phase_to_complex_h */
