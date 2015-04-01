
/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "math/algorithms/spline.h"
#include <cmath>
#include <cassert>

namespace math{
namespace algorithms{

mySpline::mySpline(  double const * const a, double const * const b, const size_t c ) noexcept
  :
  xvar(a), func(b), N(c),
  spline( gsl_spline_alloc( gsl_interp_cspline, N ) ),
  workspace( gsl_integration_workspace_alloc (limit) )
{
  /*The arguments include two arrays where
      a ...independent array
      b ...dependent array
      c ...size of array */
  ///alloc space for the mySpline anbd assign to pointer
  gsl_spline_init( spline, xvar, func, N );
}

mySpline::~mySpline(void) noexcept
{
  gsl_spline_free( spline ) ;
  gsl_interp_accel_free( acc ) ;
  gsl_integration_workspace_free( workspace ) ;
}


double mySpline::eval( const double xpos ) const noexcept
{
  assert( xpos > xvar[0] ) ;
  assert( xpos < xvar[N-1]  ) ;
  
  return gsl_spline_eval( spline, xpos, acc );
}

double mySpline::CCallback( double d, void*params ) noexcept
{
  return static_cast<mySpline*>(params)->eval(d);
}



}
}
