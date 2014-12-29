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

#ifndef __tat__cmplx_combination__
#define __tat__cmplx_combination__

#include <vector>
#include <complex>
#include <cstddef>
#include <utility>

#include <iostream>

namespace thermal{
namespace analysis{

std::vector<double>
Tcplx_to_Ttransient( const std::complex<double> &cplx , const double w,
                     const size_t res ) noexcept;

std::complex<double>
Ttransient_to_Tcplx( const std::vector<double> Ttransient ) noexcept;
  
std::vector<double>
t_cmplx_to_t_time( const double omega, const double res ) noexcept;

}}

#endif /* defined(__tat__cmplx_combination__) */
