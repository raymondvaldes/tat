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

#ifndef simpsons_3_8_HPP_INCLUDED
#define simpsons_3_8_HPP_INCLUDED

#include <cstring>
#include <complex>
#include <vector>

namespace math{
  namespace numIntegration{

double simpson_3_8( const double *Y, const double *X, const size_t A,
                    const size_t B) noexcept;

double simpson_3_8(const std::vector<double>& Y, const double *X,
                   const size_t A,const size_t B) noexcept;

double simpson_3_8( const double *Y, const std::vector<double>& X,
                    const size_t A, const size_t B ) noexcept;

std::complex<double> simpson_3_8Complex(const double* YReal,
                                        const double* YCPLX,
                                        const double* X,
                                        const size_t A,const size_t B) noexcept;






  }
}

#endif // simpsons_3_8_HPP_INCLUDED
