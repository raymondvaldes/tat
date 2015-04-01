/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include <boost/assert.hpp>
#include <random>
#include <chrono>
#include "math/random/random.h"
#include "math/utilities/equalto.h"


namespace math{



double genWseed( const double x_min, const double x_max, const unsigned seed ) noexcept
{
  ( void ) seed;
      
  std::random_device rd;
  std::mt19937 gen( rd() ) ;
  std::uniform_real_distribution<> dis( x_min, x_max ) ;
  
  return dis( gen ) ;
}

double random_in_logspace( const double start, const double end ) noexcept
{
  BOOST_ASSERT_MSG( start < end, "Setup issue" ) ;
  BOOST_ASSERT_MSG( start > 0, "must be positive for logspace transform" ) ;

  using std::pow;
  const double x = random_0_to_1() ;
  const double xini = start * pow( end/start, x ) ;
 
  return xini ;
}
  
double random_0_to_1() noexcept {
  const double lowerbound = 0 ;
  const double upperbound = 1 ;
  return x_ini( lowerbound, upperbound ) ;
}
  
double x_ini( const double x_min, const double x_max ) noexcept
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

int xINTrandom(const int xmin, const int xmax) noexcept
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
  
double x_normal(const double Xmean, const double Xstddev, const unsigned seed1) noexcept
{
  std::mt19937 gen;
  gen.seed(seed1);

  std::normal_distribution<double> distribution(Xmean,Xstddev);
  return distribution(gen);
}

double x_normal(const double Xmean, const double Xstddev) noexcept
{
  std::random_device rd;
  std::mt19937 gen( rd() ) ;

  std::normal_distribution<double> distribution(Xmean,Xstddev);
  return distribution(gen);
}

double x_bias(const double Xmean, const double Xstddev) noexcept
{
    double xguess = x_normal(Xmean,Xstddev);

    while(xguess<Xmean)
    {
        xguess = x_normal(Xmean,Xstddev);
    }

    return xguess;
}

}
