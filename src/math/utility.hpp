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

#include <vector>
#include <cstring>
#include <iostream>

namespace math{

double genWseed( const double x_min, const double x_max, const unsigned seed );

double x_ini(const double x_min, const double x_max);

template< typename T1, typename T2>
bool equalto ( const T1 a, const T2 b)
{
const double multi = a > b ? a : b;
const double multi2 = multi >= 1 ? multi  : 1;

return std::abs(a - b) < (std::numeric_limits<double>::epsilon()) * multi2;
}

double arrayMax(const double* x, const size_t I);
double arrayMin(const double* x, const size_t I);

double x_ini10(const int x_ref);
double x_ini10(const double x_ref);


int xINTrandom(const int xmin, const int xmax);
double x_normal(const double Xmean, const double Xstddev, const unsigned seed1);
double x_normal(const double Xmean, const double Xstddev);

double x_bias(const double Xmean, const double Xstddev);


double average(const double a, const double b);
double percentile(const double xmin, const double xmax, const double x);
double percentilelog10(const double xmin, const double xmax, const double x);


void range( double* l_thermal, const double l_min, const double l_max,
            const size_t L_end ) ;
std::vector<double>
  range( const double xstart, const double xend, const size_t size ) ;

std::vector<double>
range1og10( const double l_min, const double l_max, const size_t L_end );

inline double mean(const double a, const double b)
{
    double mean1 = a ;
    mean1 += b ;
    mean1 *= 0.5 ;
    return mean1 ;
}
double xspread( const double xmin, const double xnominal, const double xmax);

double valFROMpercentileLog10( const double input,  const double xmin,
                               const double xmax );


std::pair<double, double>
newThermalSweepLimits( const double center, const double range,
                                const std::pair<double, double> limits );
std::pair<double, double>
CRfromSweepLimits( const double lstart, const double lend,
                   const std::pair<double, double> limits ) ;
std::pair<double, double> xCenterlog10( const double lmin, const double lmax ) ;





}




#endif // UTILITY_HPP
