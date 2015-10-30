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
#include <cmath>
#include "math/numIntegration/gslfunc.hpp"

namespace math{
namespace numIntegration{


double fintegrate(double x, void *p) noexcept
{
  mySpline &params = *reinterpret_cast<class mySpline *>(p);
  return params.eval(x);
}

double integrate( mySpline *Func, const double xlow,
                  const double xhigh) noexcept
{
    //http://www.bnikolic.co.uk/nqm/1dinteg/gslgk.html

    mySpline &params = *Func;
    gsl_function F;
    F.function = &fintegrate;
    F.params = reinterpret_cast<void *>(&params);

    double result(0);
    double code(0);
    double error(0);
    size_t neval(0);
    
    static constexpr double epsabs = 1e-12;
    static constexpr double epsrel = 1e-12;
  
    code = gsl_integration_qng( &F, xlow, xhigh, epsabs, epsrel, &result,
                                &error, &neval) ;
  
    std::clog << "numerical integration returned: " << code
              << "\twith error "<< error << neval <<"\n";
    return result;
}

}}
