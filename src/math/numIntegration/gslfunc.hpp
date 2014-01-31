/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
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

#ifndef GSLFUNC_HPP
#define GSLFUNC_HPP

#include <gsl/gsl_spline.h>
#include <gsl/gsl_integration.h>
#include <iostream>
#include <iomanip>

namespace math{
  namespace numIntegration{

class funcClass
{
private:
  const size_t limit = 1001;    //defines size of workspace
  gsl_interp_accel *acc   = gsl_interp_accel_alloc();  ///Ptr interpolation iter
  gsl_spline *spline      = nullptr; ///Declare pointer to interpolations
  gsl_integration_workspace *workspace  = nullptr;
  const double* xvar;
  const double* func;
  const size_t  N;
  static double CCallback(double d, void*params);

public:
  /*  F:          the gsl_function which is the integrand
      xlow:       lower integration limit
      xhigh:      higher integration limit
      abstol:     absolute tolerance
      reltol:     relative tolerance
      result:     a pointer to a gdouble in which stores the result
      error:      a pointer to a gdobuel in which the function stores the
                  estimed error                                           */
  static constexpr double epsabs = 1e-8;
  static constexpr double epsrel = 1e-8;
  int code;
  double result;
  double error;
  size_t neval;

  explicit funcClass( const double* a, const double* b, const size_t c ) ;
  ~funcClass( void ) ;
  double eval( const double xpos ) const;
};


double fintegrate( double x, void *p ) ;
double integrate( funcClass *Func, const double xlow, const double xhigh ) ;


  }
}
#endif // GSLFUNC_HPP
