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
#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <limits>
#include <vector>
#include <array>
#include <cstring>
#include <iostream>
#include <typeinfo>
#include <cstddef>

#include "math/geometry/interval.h"

namespace math{

double arrayMax( const double* x, const size_t I ) noexcept;
double arrayMin( const double* x, const size_t I ) noexcept;

void range( double* l_thermal, const double l_min, const double l_max,
            const size_t L_end ) noexcept;
  
std::pair<double, double> OA_init( const double *x, const size_t span ) noexcept;
double average_of_all( const double* myarray, const size_t size) noexcept;

double median_of_all( const double* sortedvector ,
                      const size_t size ) noexcept;


double average( const double a, const double b ) noexcept;
double percentile( const double xmin, const double xmax, const double x ) noexcept;
double percentilelog10( const double xmin, const double xmax, const double x ) noexcept;



std::vector<double>
  range( const double xstart, const double xend, const size_t size ) noexcept;


std::pair<double, double>
CRfromSweepLimits( const std::pair<double, double>  & inner_bounds,
                   const std::pair<double, double>  & limits ) noexcept;

std::pair<double, double>
random_CR_from_limits( const Interval myInterval ) noexcept;

std::vector<double>
range1og10( const double l_min, const double l_max, const size_t L_end ) noexcept;

inline double mean(const double a, const double b) noexcept
{
    double mean1 = a ;
    mean1 += b ;
    mean1 *= 0.5 ;
    return mean1 ;
}
double xspread( const double xmin, const double xnominal, const double xmax) noexcept;

double valFROMpercentileLog10( const double input,  const double xmin,
                               const double xmax ) noexcept;

std::pair<double, double>
x_limits_from_cenDec( const double cen, const double dec ) noexcept;

std::pair<double, double>
newThermalSweepLimits( const double center, const double range,
                                const std::pair<double, double> & limits ) noexcept;

std::pair<double, double> xCenterlog10( const double lmin, const double lmax ) noexcept;


bool checkLimits( const double center, const double range ) noexcept;
bool checkLimits( const std::pair<double, double> & CRpair ) noexcept;


bool within_tolerance( const double x1, const double x2, const double tol ) noexcept;

template< typename integer >
bool even( const integer x ) noexcept
{
  //cannot pass double because of modulus (template is for uint and int)
  const bool pass = ( (x % 2) == 0 ) ;
  return pass;
}

template< typename integer >
bool odd( const integer x ) noexcept
{
  const bool fail = even(x) ;
  const bool pass = !fail ;
  return pass;
}

std::pair<double, double>
get_log10_random_pair( const double left_end, const double right_end) noexcept;

}

#endif // UTILITY_HPP
