//
//  planckWienApprox.cpp
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include <cmath>
#include <boost/assert.hpp>
#include "thermal/emission/blackBody/planckWienApprox.h"
#include "thermal/emission/blackBody/constants.h"

using std::pow;
using std::exp;

namespace thermal {
namespace emission {
namespace blackBody {
  
double plankWienApprox( const double wavelength, const double temperature ) noexcept {

  BOOST_ASSERT( temperature > 0 );
  BOOST_ASSERT( wavelength > 0 ) ;
  
  const double lambda = wavelength ;
  const double Temp = temperature ;
  
  double
  Ib  = C1 ;
  Ib /= M_PI *  pow( lambda, 5 )  ;
  Ib *= exp( -C2 / ( lambda * Temp ) ) ;
  
  return Ib;
}

}}}