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

#include <cstring>
#include "math/numIntegration/gslfunc.hpp"
namespace math{
  namespace numIntegration{


double fintegrate(double x, void *p)
{
  struct funcClass &params = *reinterpret_cast<struct funcClass *>(p);
  return params.eval(x);
}

double integrate(struct funcClass *Func, double xlow, double xhigh)
{
    //http://www.bnikolic.co.uk/nqm/1dinteg/gslgk.html

    struct funcClass &params = *Func;

    gsl_function F;
    F.function = &fintegrate;
    F.params = reinterpret_cast<void *>(&params);

    Func->code = gsl_integration_qng(&F, xlow, xhigh, params.epsabs,
                                     params.epsrel, &params.result,
                                     &params.error, &params.neval);
    return Func->result;
}

  }
}
