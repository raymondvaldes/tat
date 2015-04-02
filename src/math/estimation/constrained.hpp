/*----------------------------------------------------------------------------*\
  ========                |
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
#ifndef CONSTRAINED_HPP
#define CONSTRAINED_HPP
#include <vector>

namespace math{
namespace estimation{

double x_limiter1( const double xi ) noexcept;

double x_limiter2( const double xi, const double x_min, const double x_max ) noexcept;

double kx_limiter1( const double ki ) noexcept;

double kx_limiter2( const double ki, const double k_min, const double k_max ) noexcept;

std::vector<double> x_to_kspace_unity( const double* x, const size_t n ) noexcept;

std::vector<double> kspace_to_x_unity( const double* x, const size_t n ) noexcept;

template< typename T >
auto x_to_k_constrained_from_0_to_1( T const x ) noexcept -> T
{
  assert( x >= 0 );
  assert( x <= 1 );
  return kx_limiter2( x, 0, 1 );
}

template< typename T >
auto k_to_x_constrained_from_0_to_1( T const k ) noexcept -> T
{
  return x_limiter2( k, 0, 1 );
}

} // namespace estimation
} // namespace math


#endif // CONSTRAINED_HPP
