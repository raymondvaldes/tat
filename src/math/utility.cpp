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

double genWseed( const double x_min, const double x_max, const unsigned seed )
{
  std::random_device rd;
  std::mt19937 gen( rd() ) ;
//  gen.seed( seed ) ;
  std::uniform_real_distribution<> dis( x_min, x_max ) ;
  
  return dis( gen ) ;
}
  
double x_ini( const double x_min, const double x_max )
{
/*
    Creates a random parameter between two open bounds
    x_min = minimum value
    x_max = maximum value
*/
  typedef std::chrono::high_resolution_clock myclock;
  myclock::time_point beginning = myclock::now();

  double xini = x_min ;
  while ( equalto( xini,x_min ) || equalto( xini, x_max ) )
  {
    myclock::duration d = myclock::now() - beginning;
    unsigned seed2 = static_cast<unsigned> (d.count() ) ;
  
    xini = genWseed( x_min, x_max, seed2 ) ;
  }

  return xini;
}

int xINTrandom(const int xmin, const int xmax)
{
  std::mt19937 gen;
  typedef std::chrono::high_resolution_clock myclock;
  myclock::time_point beginning = myclock::now();
  myclock::duration d = myclock::now() - beginning;
  unsigned seed = static_cast<unsigned> (d.count() ) ;
  
  gen.seed( seed );
  std::uniform_int_distribution<int> dist( xmin , xmax );
  
  return dist(gen);
  
}
  
double x_normal(const double Xmean, const double Xstddev, const unsigned seed1)
{
  std::mt19937 gen;
  gen.seed(seed1);

  std::normal_distribution<double> distribution(Xmean,Xstddev);
  return distribution(gen);
}

double x_normal(const double Xmean, const double Xstddev)
{
  std::random_device rd;
  std::mt19937 gen( rd() ) ;

  std::normal_distribution<double> distribution(Xmean,Xstddev);
  return distribution(gen);
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

std::pair<double, double> OA_init( const double *x, const size_t span )
{
  /* Givin a harmonic response over the length of one period this function
     returns initial guesses of the amplitude and offset in the form of
     
        x(t) = offset + amplitude * cos( omega * time - phase )
  */

  using std::pair;
  
  const double arrayMax_val = arrayMax( x, span ) ;
  const double arrayMin_val = arrayMin( x, span ) ;

  const double
  offsetInitial = average( arrayMax_val , arrayMin_val ) ;
  
  const double
  amplitudeInitial = ( arrayMax_val - arrayMin_val ) / 2 ;
  
  
  const pair<double, double> output( offsetInitial , amplitudeInitial );
  return output;
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
        std::cerr << "\noutside range linear\n";
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
        std::cerr << "\n" << xmin << "\t" << xmax << "\t" << x << "\t"
        << (x > xmax) << "\t" << (x < xmin) << "\n";

        std::cerr << "\noutside range logspace\n";
        exit(-99);
    }


  return (std::log10(x) - std::log10(xmin)) /
         (std::log10(xmax) - std::log10(xmin));
}

double valFROMpercentileLog10( const double input,  const double xmin,
                               const double xmax )
{
  BOOST_ASSERT( input <= 1 && input >=0) ;
  return xmin * std::pow( xmax / xmin , input );
}


void range( double* l_thermal, const double l_min, const double l_max,
            const size_t L_end )
{
    for(size_t i = 0 ; i <  L_end; ++i)
    {
      l_thermal[i] = ( l_max - l_min ) * ( double(i) / ( L_end - 1 ) );
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

bool checkLimits( const double center, const double range )
{
  // The center and range are used to charactize the data set.  The following
  /// are defined:
  ///
  /// center: This the center of the data set, where 0 is the beginning of the
  /// data and 1 is the end of the data.
  ///
  /// range: This the the span of the data. It is defined to represent a
  /// percentage of the data where 0 is 0% of the data and 1 is 100% of the
  /// data.
  ///
  /// For example: given the values of center = 0.3 and range = .25
  /// The dataset is bounded to ( 0.175 , 0.425 )

  BOOST_ASSERT( center > 0 && center < 1 ) ;
  BOOST_ASSERT( range > 0 && range <= 1 ) ;

  bool run = true;
  const double strPos = center - range / 2 ;
  const double endPos = center + range / 2 ;

  if( strPos < 0 ||  endPos > 1 )
    { run = false ; }

  return run ;
}


std::pair<double, double>
newThermalSweepLimits( const double center, const double range,
                       const std::pair<double, double> limits )
{
  BOOST_ASSERT( center > 0 && center < 1) ;
  BOOST_ASSERT( range > 0 && range <= 1 ) ;

  double strPos = center - range/2 ;
  double endPos = center + range/2 ;

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

  const double min = limits.first;
  const double max = limits.second;

  const double start = math::valFROMpercentileLog10( strPos, min, max ) ;
  const double end   = math::valFROMpercentileLog10( endPos, min, max ) ;

  const std::pair<double, double> output(start, end);

  return output;
}



}
