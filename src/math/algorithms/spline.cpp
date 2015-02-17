
/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
 -------------------------------------------------------------------------------
 License
 This file is part of Thermal Analysis Toolbox.
 
 Thermal Analysis Toolbox is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or (at your
 option) any later version.
 
 Thermal Analysis Toolbox is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License along with
 Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.
 
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
