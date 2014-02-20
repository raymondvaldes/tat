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
#include <vector>
#include <cstring>
#include "math/numIntegration/gslfunc.hpp"
namespace math{
namespace numIntegration{

funcClass::funcClass(const double *a, const double *b, const size_t c )
  : xvar(a), func(b), N(c)
{
  /*The arguments include two arrays where
      a ...independent array
      b ...dependent array
      c ...size of array */
  ///alloc space for the spline anbd assign to pointer
  spline = gsl_spline_alloc(gsl_interp_cspline, N);
  gsl_spline_init(spline, xvar, func, N);
  workspace = gsl_integration_workspace_alloc (limit);
}

funcClass::~funcClass(void)
{
  gsl_spline_free(spline);
  gsl_interp_accel_free(acc);
  gsl_integration_workspace_free(workspace);
}


double funcClass::eval( const double xpos ) const
{
  const double tol = 10e-10;
  double xposNew = xpos;
  if( std::fabs( xpos - xvar[0]   ) < tol ) xposNew = xvar[0] + tol;
  if( std::fabs( xpos - xvar[N-1] ) < tol ) xposNew = xvar[N-1] - tol;

  if( xposNew < xvar[0] || xposNew > xvar[N-1] )
  {
    std::cout << "outside range!!\n\n"
    <<xpos<<" is outside of range "<<xvar[0]<<"\t"<<xvar[N-1]<<"\n";
    exit(-71);
    return 0;
  }

  return gsl_spline_eval( spline, xposNew, acc );
}

double funcClass::CCallback( double d, void*params )
{
  return static_cast<funcClass*>(params)->eval(d);
}

double fintegrate(double x, void *p)
{
  struct funcClass &params = *reinterpret_cast<struct funcClass *>(p);
  return params.eval(x);
}

double integrate( struct funcClass *Func, const double xlow, const double xhigh)
{
    //http://www.bnikolic.co.uk/nqm/1dinteg/gslgk.html

    struct funcClass &params = *Func;
    gsl_function F;
    F.function = &fintegrate;
    F.params = reinterpret_cast<void *>(&params);

    Func->code = gsl_integration_qng( &F, xlow, xhigh, params.epsabs,
                                      params.epsrel, &params.result,
                                      &params.error, &params.neval) ;
    return Func->result;
}

}}
