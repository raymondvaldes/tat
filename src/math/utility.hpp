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

#include <cstring>
#include <iostream>

namespace math{

double x_ini(const double x_min, const double x_max);
double x_ini(const double x_min, const double x_max, const size_t position,
             const size_t gN);

bool equalto(const double a, const double b);
bool equalto(const double a, const int b);
double arrayMax(const double* x, const size_t I);
double arrayMin(const double* x, const size_t I);

double x_ini10(const int x_ref);
double x_ini10(const double x_ref);


size_t xINTrandom(const size_t xmin, const size_t xmax);
double x_normal(const double Xmean, const double Xstddev, const double seed1);
double x_normal(const double Xmean, const double Xstddev);

double x_bias(const double Xmean, const double Xstddev);


double average(const double a, const double b);
double percentile(const double xmin, const double xmax, const double x);
double percentilelog10(const double xmin, const double xmax, const double x);


void range( double* l_thermal, const double l_min, const double l_max,
            const size_t L_end ) ;
void range( std::vector<double>& l_thermal, const double l_min,
            const double l_max, const size_t L_end ) ;
void range1og10( const double l_min, const double l_max, const size_t L_end,
                 std::vector<double> &l_thermal ) ;
void range1og10( const double l_min, const double l_max, const size_t L_end,
                 double* l_thermal ) ;

inline double mean(const double a, const double b)
{
    double mean1 = a;
    mean1 +=b;
    mean1 *=0.5;
    return mean1;
}
double xspread( const double xmin, const double xnominal, const double xmax);

}




#endif // UTILITY_HPP
