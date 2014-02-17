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
#include <random>
#include <ctime>
#include <chrono>
#include <boost/assert.hpp>

#include "math/utility.hpp"

namespace math{

double x_ini(const double x_min, const double x_max)
{
/*
    Creates a random parameter between two open bounds
    x_min = minimum value
    x_max = maximum value
*/
    double xini = x_min ;
    while (equalto(xini,x_min) || equalto(xini,x_max))
    {
        std::mt19937 gen;
        gen.seed( std::time(NULL) + rand() ) ;
        std::uniform_real_distribution<> dis(x_min, x_max);
        xini = dis(gen);
    }

    return xini;
}

double x_ini(const double x_min, const double x_max, const size_t position,
             const size_t gN)
{
/*
    Creates a random parameter between two open bounds
    x_min = minimum value
    x_max = maximum value

    In addition, the number will be in a "low", "high" group depending on the gN
    value.  Example:
        gN = 2 would create two groups of "low" and "high".
        gN = 3 would create three groups of "low", "medium", "high" etc.
    The position will depend on the 'position' argument.
*/

    if(position  <= 0 || position  > gN)
    {
        exit(-99);
    }

    double xini = x_min;
    xini += (x_max - x_min) * ( ( position-1 ) / gN ) ;

    double xminNew = xini;
    double xmaxNew = x_max;
    xmaxNew -= (x_max - x_min) * ( ( position-1 ) / gN );

    while ( math::equalto(xini, xminNew) || math::equalto(xini, xmaxNew) )
    {
        std::mt19937 gen;
        gen.seed( std::time(NULL) + rand() ) ;
        std::uniform_real_distribution<> dis(xminNew, xmaxNew);
        xini = dis(gen);
    }

    return xini;
}

bool equalto(const double a, const double b)
{
    const double multi = a > b ? a : b;
    const double multi2 = multi >= 1 ? multi  : 1;

    return std::abs(a - b) < (std::numeric_limits<double>::epsilon()) * multi2;
}

bool equalto(const double a, const int b)
{
    const double multi = a > b ? a : b;
    const double multi2 = multi > 1 ? multi  : 1;

    return std::abs(a - b) < (std::numeric_limits<double>::epsilon()) * multi2;
}


double arrayMax(const double* x, const size_t I)
{
    double maxi = x[0];
    for(size_t i = 1; i < I ; ++i)
    {
        if(x[i] > maxi ) maxi = x[i];
    }

    return maxi;
}

double arrayMin(const double* x, const size_t I)
{
    double maxi = x[0];
    for(size_t i = 1; i < I ; ++i)
    {
        if(x[i] < maxi ) maxi = x[i];
    }

    return maxi;
}

double x_ini10(const int x_ref)
{
    return x_ini10(double(x_ref));
}
double x_ini10(const double x_ref)
{
/*
    Creates a random parameter between two open bounds
    x_ref*.9 = minimum value
    x_ref*1.1 = minimum value
*/
    const double percent = .1;
    return x_ini(x_ref*(1-percent), x_ref*(1+percent));
}





size_t xINTrandom(const size_t xmin, const size_t xmax)
{
    std::mt19937 gen;
    gen.seed( std::time( NULL ) + rand() );

    std::uniform_int_distribution<> distribution( xmin , xmax );
    return distribution(gen);
}


double x_normal(const double Xmean, const double Xstddev, const double seed1)
{
//    std::default_random_engine gen;
    std::mt19937 gen;
    gen.seed(seed1);

    std::normal_distribution<double> distribution(Xmean,Xstddev);
    return distribution(gen);
}

double x_normal(const double Xmean, const double Xstddev)
{
//    std::default_random_engine gen;
    std::mt19937 gen;
    gen.seed(std::time(NULL) + rand()) ;

    std::normal_distribution<double> distribution(Xmean,Xstddev);
    return distribution(gen);
}

double x_bias(const double Xmean, const double Xstddev)
{
    double xguess = x_normal(Xmean,Xstddev);

    while(xguess<Xmean)
    {
        xguess = x_normal(Xmean,Xstddev);
    }

    return xguess;
}

double average(const double a, const double b)
{
    double val = a;
    val += b;
    val *= .5;
    return val;
}

double percentile(const double xmin, const double xmax, const double x)
{
    /*
    This function returns the percentile of x in log10 space with respect to the
    x_min to x_max range.
    */

    if( x > xmax || x < xmin)
    {
        std::cout << "\noutside range linear\n";
        exit(-99);
    }

    return x / (xmax-xmin);
}

double percentilelog10(const double xmin, const double xmax, const double x)
{
    /*
    This function returns the percentile of x in log10 space with respect to the
    x_min to x_max range.
    */

    constexpr double epsilon = 1e-12;
    if( ( (x-epsilon) > xmax) || ( (x+epsilon) < xmin ) )
    {
        std::cout << "\n" << xmin << "\t" << xmax << "\t" << x << "\t"
        << (x > xmax) << "\t" << (x < xmin) << "\n";

        std::cout << "\noutside range logspace\n";
        exit(-99);
    }


    return (log10(x) - log10(xmin)) / (log10(xmax) - log10(xmin));
}

double valFROMpercentileLog10( const double input,  const double xmin,
                               const double xmax )
{
  assert( input <= 1 && input >=0) ;
  return xmin * pow( xmax / xmin , input );
}


void range( double* l_thermal, const double l_min, const double l_max,
            const size_t L_end )
{
    for(size_t i = 0 ; i <  L_end; ++i)
    {
      l_thermal[i] = ( l_max - l_min ) * ( double(i) / ( L_end - 1 ) );
    }
}

void range( std::vector<double>& l_thermal, const double l_min,
            const double l_max, const size_t L_end )
{
  //Creates equally spaced range from lmin to lmax
  for(size_t i = 0 ; i <  L_end; ++i)
  {
    l_thermal[i] = ( l_max - l_min ) * ( double(i) / (L_end - 1 ) ) ;
  }
}

std::vector<double>
range( const double xstart, const double xend, const size_t size )
{
  std::vector<double> result( size );
  size_t i = 0;
  for( auto& val : result )
  { 
    val = ( xend - xstart ) * ( double(i) / ( size - 1 ) ) ;
    i++;
  }

  return result;
}


std::pair<double, double> xCenterlog10( const double lmin, const double lmax )
{
  const double xlimits = std::log10( lmax / lmin ) ;
  const double center = lmin * std::pow( 10, xlimits / 2 ) ;

  const std::pair<double, double> output ( center, xlimits ) ;

  return output;
}

std::vector<double>
range1og10( const double l_min, const double l_max, const size_t L_end )
{
  BOOST_ASSERT_MSG( L_end >= 1 , "check inputs \n\n" );
  BOOST_ASSERT_MSG( l_min < l_max , "check inputs \n\n" );
  BOOST_ASSERT_MSG( l_min > 0 , "check inputs \n\n" );

  std::vector<double> output( L_end );

  if (L_end == 1)
  {
    output[0] = l_min ;
  }
  else if(L_end == 2)
  {
    output[0] = l_min ;
    output[L_end-1] = l_max ;
  }
  else if(L_end > 2)
  {
    const double start1 = std::log10( l_min ) + 1 ;
    const double end1   = std::log10( l_max ) + 1 ;
    const double increments = ( end1 - start1 ) / ( L_end - 1 ) ;
    double rangeI = start1 ;

    for(size_t n = 0 ; n < L_end - 1 ; ++n )
    {
      output[n] = pow( 10, rangeI - 1 ) ;
      rangeI += increments ;
    }
    output[L_end-1] = l_max ;
  }

  return output;
}

double xspread( const double xmin, const double xnominal, const double xmax)
{
  return (xmax - xmin) / xnominal;
}


std::pair<double, double>
CRfromSweepLimits( const double lstart, const double lend,
                            const std::pair<double, double> limits)
{
  const double xmin = limits.first;
  const double xmax = limits.second;

  const double posStart = math::percentilelog10( xmin,  xmax,  lstart ) ;
  const double posEnd = math::percentilelog10( xmin,  xmax,  lend ) ;

  const double range = posEnd - posStart;
  const double center = range / 2;

  const std::pair<double, double> output( center, range );
  return output;
}

std::pair<double, double>
newThermalSweepLimits( const double center, const double range,
                       const std::pair<double, double> limits )
{
  assert( center > 0 && center < 1) ;
  assert( range > 0 && range <= 1 ) ;

  const double min = limits.first;
  const double max = limits.second;

  double strPos = center - range/2;
  double endPos = center + range/2;

  if( strPos < 0 )
  {
    strPos = 0.001;
    endPos = 2 * center;
  }
  else if( endPos > 1 )
  {
    strPos = 2 * center  - 1;
    endPos = .999;
  }

  const double start = math::valFROMpercentileLog10( strPos, min, max ) ;
  const double end   = math::valFROMpercentileLog10( endPos, min, max ) ;

  const std::pair<double, double> output(start, end);

  return output;
}



}
