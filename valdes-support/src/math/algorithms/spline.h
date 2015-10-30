/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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
  double const * const xvar;
  double const * const func;
  size_t const N;

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
