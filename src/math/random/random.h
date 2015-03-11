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

#ifndef __tat__random__
#define __tat__random__

#include "algorithm/algorithm.h"
#include "units.h"

namespace math{

double genWseed( const double x_min, const double x_max, const unsigned seed ) noexcept;

double x_ini( const double x_min, const double x_max ) noexcept;

int xINTrandom( const int xmin, const int xmax ) noexcept;

double x_normal( const double Xmean, const double Xstddev,
                 const unsigned seed1 ) noexcept;

double x_normal( const double Xmean, const double Xstddev ) noexcept;

double x_bias( const double Xmean, const double Xstddev ) noexcept;

double random_in_logspace( const double start, const double end ) noexcept;

double random_0_to_1() noexcept;

template < class T, class Y>
auto addNoise
(
  std::vector< units::quantity< T, Y > > const & raw_data,
  units::quantity< T > const & stdError_nominal
) noexcept -> std::vector< units::quantity< T, Y > >
{
  using algorithm::transform;
  using std::begin;
  using units::quantity;
  
  auto const stdError_nominal_val = stdError_nominal.value();
  
  auto noisy_data = raw_data;
  
  transform( raw_data, begin(noisy_data), [&]( auto const & val )
  {
    auto const raw_value = val.value() ;
    auto const noisy_data_value = x_normal( raw_value, stdError_nominal_val ) ;
    auto const noisy_element = quantity<T>::from_value( noisy_data_value ) ;
    return noisy_element;
  } );
  
  return noisy_data;
}

template < class T, class Y>
auto addNoise
(
  std::vector< units::quantity< T, Y > > const & raw_data,
  units::quantity< units::si::dimensionless, Y > const & stdErrorPr,
  units::quantity< T > const & error_scale
)
noexcept -> std::vector< units::quantity< T, Y > >
{
  auto const stdError_nominal = stdErrorPr * error_scale;
  
  auto const noisy_data = addNoise( raw_data , stdError_nominal ) ;
  
  return noisy_data;
}

}

#endif /* defined(__tat__random__) */
