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
#include <limits>
#include <random>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <boost/assert.hpp>

#include "math/utility.hpp"

namespace math{


Interval_Ends::Interval_Ends( const std::pair<double, double> endpoints_input )
  : left_end( endpoints_input.first ), right_end( endpoints_input.second ) {
}


double Interval_Ends::get_left_end() const {
  return left_end ;
}

double Interval_Ends::get_right_end() const {
  return right_end ;
}

bool Interval_Ends::is_valid() const {
  return left_end < right_end ;
}

bool Interval_Ends::is_invalid() const {
  return left_end >= right_end ;
}

void Interval_Ends::set_ends( const std::pair<double, double> endpoints_input) {
  left_end = endpoints_input.first ;
  right_end = endpoints_input.second ;
}

std::pair<double, double> Interval_Ends::get_pair() const {
  using std::make_pair;
  return make_pair( left_end, right_end ) ;
}


Interval_Ends Interval_Ends::get_log10_random_subInterval() const {
  //given an absolute bound, return a random new set of inner limits
  //randomly generated such that the distribution is uniform in log10 space

  BOOST_ASSERT( this->is_valid() ) ;
  using std::make_pair;
  
  Interval_Ends myInterval( make_pair(0 , 0) ) ;
  
  do {
    const double myleft = random_in_logspace( left_end, right_end ) ;
    const double myright = random_in_logspace( left_end, right_end ) ;
    myInterval.set_ends( make_pair( myleft, myright ) );
  } while ( myInterval.is_invalid() ) ;

  return myInterval ;
}


double genWseed( const double x_min, const double x_max, const unsigned seed )
{
  ( void ) seed;
      
  std::random_device rd;
  std::mt19937 gen( rd() ) ;
  std::uniform_real_distribution<> dis( x_min, x_max ) ;
  
  return dis( gen ) ;
}

double random_in_logspace( const double start, const double end )
{
  BOOST_ASSERT_MSG( start < end, "Setup issue" ) ;
  BOOST_ASSERT_MSG( start > 0, "must be positive for logspace transform" ) ;

  using std::pow;
  const double x = random_0_to_1() ;
  const double xini = start * pow( end/start, x ) ;
 
  return xini ;
}
  
double random_0_to_1() {
  const double lowerbound = 0 ;
  const double upperbound = 1 ;
  return x_ini( lowerbound, upperbound ) ;
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
    BOOST_ASSERT( xmin > 0 ) ;
    BOOST_ASSERT( xmin < xmax ) ;
    BOOST_ASSERT( x >= xmin && x <= xmax ) ;

    using std::log10;
    constexpr double epsilon = 1e-12;
    if( ( (x-epsilon) > xmax) || ( (x+epsilon) < xmin ) )
    {
        std::cerr << "\n" << xmin << "\t" << xmax << "\t" << x << "\t"
        << (x > xmax) << "\t" << (x < xmin) << "\n";

        std::cerr << "\noutside range logspace\n";
        exit(-99);
    }


  return ( log10(x) - log10(xmin)) /
         ( log10(xmax) - log10(xmin));
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

std::pair<double, double>
x_limits_from_cenDec( const double cen, const double dec )
{
  using std::log10;
  using std::pow;
  using std::pair;

  const double lmin = cen / pow( 10, dec / 2 ) ;
  const double lmax = lmin * pow( 10, dec ) ;

  const pair<double, double> output ( lmin, lmax ) ;
  return output;
}

std::pair<double, double> xCenterlog10( const double lmin, const double lmax )
{
  using std::log10;
  using std::pow;
  using std::pair;

  const double dec = log10( lmax / lmin ) ;
  const double center = lmin * pow( 10, dec / 2 ) ;

  const pair<double, double> output ( center, dec ) ;
  return output;
}

std::vector<double>
range1og10( const double start, const double end, const size_t points )
{
  //Creates a finite uniform distribution from lmin to lmax in log10space

  BOOST_ASSERT_MSG( points >= 1 , "number of points must be > 0 \n\n" );
  BOOST_ASSERT_MSG( start < end , "start must be smaller than end \n\n" );
  BOOST_ASSERT_MSG( start > 0 , "start cannot be negative! \n\n" );

  using std::log10;
  using std::pow;
  std::vector<double> output( points );

  if(points == 1)
  {
    output[0] = start ;
  }
  else if(points == 2)
  {
    output[0] = start ;
    output[points-1] = end ;
  }
  else if(points > 2)
  {
    const double start1 = log10( start ) + 1 ;
    const double end1   = log10( end ) + 1 ;
    const double increments = ( end1 - start1 ) / ( points - 1 ) ;
    double rangeI = start1 ;

    for(size_t n = 0 ; n < points - 1 ; ++n )
    {
      output[n] = pow( 10, rangeI - 1 ) ;
      rangeI += increments ;
    }
    output[points-1] = end ;
  }

  return output;
}

double xspread( const double xmin, const double xnominal, const double xmax)
{
  return (xmax - xmin) / xnominal;
}


std::pair<double, double>
CRfromSweepLimits( const std::pair<double, double> inner_bounds,
                   const std::pair<double, double> outer_bounds )
{
  BOOST_ASSERT( outer_bounds.first > 0 ) ;
  BOOST_ASSERT( inner_bounds.first  <= inner_bounds.second ) ;
  BOOST_ASSERT( outer_bounds.first  <= outer_bounds.second ) ;
  
  BOOST_ASSERT( outer_bounds.first <= inner_bounds.first) ;
  BOOST_ASSERT( inner_bounds.second <= outer_bounds.second ) ;
  
  
  //This function returns the "center and range" of based on the limits//
  using std::pair;
  using math::percentilelog10;

  const double xmin = outer_bounds.first;
  const double xmax = outer_bounds.second;

  const double posStart = percentilelog10( xmin,  xmax, inner_bounds.first  ) ;
  const double posEnd   = percentilelog10( xmin,  xmax, inner_bounds.second ) ;

  const double range = posEnd - posStart;
  const double center = posStart + range / 2;

  const pair<double, double> output( center, range );
  return output;
}

bool checkLimits( const std::pair<double, double> CRpair ) {
  return checkLimits( CRpair.first, CRpair.second ) ;
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

  bool run = false;
  const double strPos = center - range / 2 ;
  const double endPos = center + range / 2 ;

  if( strPos >= 0 && endPos <= 1 )
    run = true ;

  return run ;
}

std::pair<double, double>
random_CR_from_limits( const Interval_Ends myInterval )
{
  //generates distribution a new distrubtion limits in terms of the logspace
  //center and decades. It used some global limits (input).

  const Interval_Ends
  mySubInterval = myInterval.get_log10_random_subInterval();
  
  return CRfromSweepLimits( mySubInterval.get_pair() , myInterval.get_pair() ) ;
}


std::pair<double, double>
newThermalSweepLimits( const double center, const double range,
                       const std::pair<double, double> limits )
{
  using math::valFROMpercentileLog10;
  
  //BOOST_ASSERT( center > 0 && center < 1) ;
  const bool rangeChecker = range > 0 && range <= 1 ;
  const bool centerChecker = center > 0 && center < 1 ;
  if( !rangeChecker || !centerChecker )
  {
    std::cout << "check\t" <<center << "\t" << range << "\there";

    exit(-2);
  }
  
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

  const double start = valFROMpercentileLog10( strPos, min, max ) ;
  const double end   = valFROMpercentileLog10( endPos, min, max ) ;

  const std::pair<double, double> output(start, end);

  return output;
}

bool within_tolerance( const double x1, const double x2, const double tol ) {

  assert( tol > 0 ) ;
  
  using std::abs;
  
  const bool close_enough = abs( x1 - x2 ) < tol  ;
  return close_enough ;
}

double average_of_all( const double* myarray, const size_t size){
  double sum  = 0 ;
  for( size_t i = 0 ;  i < size ; ++i ) {
    sum += myarray[i] ;
  }

  const double average = sum / size ;
  return average;
}

double median_of_all( const double* sortedvector ,
                      const size_t size )
{
  using math::mean;
  using std::is_sorted;
  BOOST_ASSERT( size >= 1 ) ;
  BOOST_ASSERT( is_sorted( &sortedvector[0], &sortedvector[0]+size  ) ) ;
  
  
  const size_t N = size / 2;
  double medianout = 0;
  
  if( even(size)  ) {
    medianout = mean( sortedvector[N], sortedvector[N-1] ) ;
  }
  else if( odd(size) ) {
    medianout = sortedvector[N] ;
    
  }
  
  return medianout;
}



}
