/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		        |
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
  constexpr double tol  = 0.0001;
  using std::abs;

  if( abs( ( min - max ) / max ) < tol )
  {
    bestGuess = math::average( min, max ) ;
    solnTolerance = tol;
    pass = true ;
  }
  else
  {
    BOOST_ASSERT(min < max) ;
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

void solve::BisectMethod(void) noexcept
{
  using std::placeholders::_1;
  const std::function<double(double)>
      myFuncReduced = std::bind( &solve::myRootFunc, this , _1 );

  namespace BMT =  boost::math::tools;
  constexpr size_t digitsBitsofPrecision = 64; //same as double
  const BMT::eps_tolerance<double> tol = digitsBitsofPrecision;

  const std::pair<double, double> result =
      BMT::bisect( myFuncReduced, min, max, tol, maxInt ) ;

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

solve::~solve(void) noexcept{}

}
