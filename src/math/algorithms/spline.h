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

#ifndef __tat__mySpline_math__algorithms__
#define __tat__mySpline_math__algorithms__

#include <iostream>
#include <vector>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_integration.h>

namespace math{
namespace algorithms{

class mySpline
{
private:
  static constexpr size_t limit = 1001;    //defines size of workspace
  static constexpr double tol = 1e-14;
  const double* xvar;
  const double* func;
  const size_t  N;

  gsl_interp_accel *acc   = gsl_interp_accel_alloc();  ///Ptr interpolation iter
  gsl_spline *spline      = nullptr; ///Declare pointer to interpolations
  gsl_integration_workspace *workspace  = nullptr;
  static double CCallback(double d, void*params) noexcept;

public:
  explicit mySpline( const double* a, const double* b, const size_t c ) noexcept;
  ~mySpline( void ) noexcept;
  
  double eval( const double xpos ) const noexcept;
};

}
}

#endif /* defined(__tat__mySpline_math__algorithms__) */
