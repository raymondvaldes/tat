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

#ifndef __tat__spline_cplx__
#define __tat__spline_cplx__

#include <iostream>
#include <vector>
#include <complex>
#include "math/algorithms/spline.h"

namespace math{ namespace algorithms {

class spline_cplx
{
private:
  mySpline real;
  mySpline imag;

public:
  explicit spline_cplx( const std::vector< std::complex<double> > &ind,
                        const double* dep, const size_t c ) noexcept;
 // ~spline_cplx( void ) ;
  std::complex<double> eval( const double xpos ) const noexcept;
};



}}

#endif /* defined(__tat__spline_cplx__) */
