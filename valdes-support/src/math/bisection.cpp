/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		        |

\*----------------------------------------------------------------------------*/
#include <functional>
#include <iostream>
#include <cmath>

#include <boost/math/tools/roots.hpp>

#include "math/bisection.hpp"
#include "math/utility.hpp"

namespace math{

size_t PrecisionToBits(const size_t precision) noexcept
{
  /*Enter the number of decimal precision required*/
  const double log10of2 = std::log10(2) ;
  const double bits = precision / log10of2 ;

  return static_cast<size_t> (std::ceil( bits ) ) ;
}


 double solve::myRootFunc(const double x) const noexcept
{
  return myF(x) - phi;
}

solve::solve( std::function<double(double)> myF_ , const double phi_,
                const double min_, const double max_) noexcept
  : myF(myF_), phi(phi_), min(min_), max(max_)
{
  assert( min < max ) ;
  assert( phi > 0);
  
  auto const tol = phi / 1000;
///  constexpr double tol  = 0.0001;
  using std::abs;
  auto const is_converged = abs( ( min - max ) / max ) < tol ;

  if( is_converged )
  {
    bestGuess = math::average( min, max ) ;
    solnTolerance = tol;
    pass = true ;
  }
  else
  {
    try
    {
      BisectMethod();
      pass = true ;
    }
    catch ( std::exception const&  ex )
    {
      bestGuess = min;
      pass = false ;
    }
  }
}

solve::solve(
  std::function<double(double)> myF_,
  const double min_,
  const double max_,
  double const f_a,
  double const f_b,
  double const tol
) noexcept
  : myF(myF_), phi(0), min(min_), max(max_)
{
  assert( min < max ) ;
  assert( f_a * f_b <= 0 );
  
  using std::abs;
  auto const is_converged = abs( ( min - max ) / max ) < tol ;

  if( is_converged )
  {
    bestGuess = math::average( min, max ) ;
    solnTolerance = tol;
    pass = true ;
  }
  else
  {
    try
    {
      toms748( f_a, f_b, tol );
      pass = true ;
    }
    catch ( std::exception const&  ex )
    {
      bestGuess = min;
      pass = false ;
    }
  }
}

void solve::toms748(
  double const f_a,
  double const f_b,
  double const tol
) noexcept
{
  using std::placeholders::_1;
  using std::pair;
  const std::function<double(double)>
      myFuncReduced = std::bind( &solve::myRootFunc, this , _1 );


  //This termination condition has been added to reduce the numer of iterations
  // necessary for convergence.
  auto const TerminationCondition = [tol]( auto const  min, auto const max) noexcept {
    
    return ( std::abs(min - max) / math::average( min, max ) ) <= tol;
  };

  
  const pair<double, double> result =
      boost::math::tools::toms748_solve( myFuncReduced, min, max, f_a, f_b, TerminationCondition, maxInt ) ;

  //output
  solnTolerance = std::abs( result.first - result.second ) ;
  bestGuess = math::average( result.first , result.second ) ;
}


void solve::BisectMethod(void) noexcept
{
  using std::placeholders::_1;
  using std::pair;
  const std::function<double(double)>
      myFuncReduced = std::bind( &solve::myRootFunc, this , _1 );


  //This termination condition has been added to reduce the numer of iterations
  // necessary for convergence.
  auto const TerminationCondition = []( double min, double max){
//    std::cout << std::abs(min - max) / math::average( min, max ) << "\n";
    
    return std::abs(min - max) / math::average( min, max ) <= 0.001;
  };

  
  const pair<double, double> result =
      boost::math::tools::bisect( myFuncReduced, min, max, TerminationCondition, maxInt ) ;

  //output
  solnTolerance = std::abs( result.first - result.second ) ;
  bestGuess = math::average( result.first , result.second ) ;
}

double solve::returnSoln(void) const noexcept
{
  return bestGuess;
}

size_t solve::returnIterations(void) const noexcept
{
  return maxInt;
}

double solve::returnSolnTolerance(void) const noexcept
{
  return solnTolerance;
}

}
