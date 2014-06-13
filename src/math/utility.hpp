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
namespace math{


struct Interval_Ends
{
private:
  double left_end;
  double right_end;

public:
  Interval_Ends( const std::pair<double, double> endpoints_input ) ;
  Interval_Ends() ;
  double get_left_end() const ;
  double get_right_end() const ;
  bool is_valid() const ;
  bool is_invalid() const;
  void set_ends( const std::pair<double, double> endpoints_input) ;
  Interval_Ends get_log10_random_subInterval() const ;
};

double genWseed( const double x_min, const double x_max, const unsigned seed ) ;

double x_ini( const double x_min, const double x_max ) ;

template< typename T1, typename T2 >
bool equalto ( const T1 a, const T2 b )
{
  const double multi = ( a > b ? a : b ) ;
  const double multi2 = ( multi >= 1 ? multi  : 1 ) ;

  return (std::abs(a - b) < (std::numeric_limits<double>::epsilon()) * multi2 );
}

double arrayMax( const double* x, const size_t I ) ;
double arrayMin( const double* x, const size_t I ) ;
std::pair<double, double> OA_init( const double *x, const size_t span ) ;


int xINTrandom( const int xmin, const int xmax ) ;
double x_normal( const double Xmean, const double Xstddev,
                 const unsigned seed1 ) ;
double x_normal( const double Xmean, const double Xstddev ) ;

double x_bias( const double Xmean, const double Xstddev ) ;


double average( const double a, const double b ) ;
double percentile( const double xmin, const double xmax, const double x ) ;
double percentilelog10( const double xmin, const double xmax, const double x ) ;


void range( double* l_thermal, const double l_min, const double l_max,
            const size_t L_end ) ;
double random_in_logspace( const double start, const double end ) ;

std::vector<double>
  range( const double xstart, const double xend, const size_t size ) ;

double random_0_to_1();

std::pair<double, double>
CRfromSweepLimits( const std::pair<double, double> inner_bounds,
                   const std::pair<double, double> limits ) ;

std::pair<double, double>
random_CR_from_limits( const std::pair<double, double> limits );

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
x_limits_from_cenDec( const double cen, const double dec );

std::pair<double, double>
newThermalSweepLimits( const double center, const double range,
                                const std::pair<double, double> limits );

std::pair<double, double> xCenterlog10( const double lmin, const double lmax ) ;


bool checkLimits( const double center, const double range ) ;
bool checkLimits( const std::pair<double, double> CRpair ) ;


double average_of_all( const double* myarray, const size_t size) ;
bool within_tolerance( const double x1, const double x2, const double tol ) ;

template< typename integer >
bool even( const integer x )
{
  //cannot pass double because of modulus (template is for uint and int)
  const bool pass = ( (x % 2) == 0 ) ;
  return pass;
}

template< typename integer >
bool odd( const integer x )
{
  const bool fail = even(x) ;
  const bool pass = !fail ;
  return pass;
}

double median_of_all( const double* sortedvector ,
                      const size_t size ) ;


}




#endif // UTILITY_HPP
