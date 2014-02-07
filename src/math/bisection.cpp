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
#include <functional>
#include <iostream>
#include <math.h>
#include <boost/math/tools/roots.hpp>
#include "math/bisection.hpp"
#include "math/utility.hpp"

namespace math{

size_t PrecisionToBits(const size_t precision)
{
  /*Enter the number of decimal precision required*/
  constexpr double log10of2 = log10(2);
  const double bits = precision / log10of2;

  return ceil(bits);
}


 double solve::myRootFunc(const double x) const
{
  return myF(x) - phi;
}

solve::solve( std::function<double(double)> myF_ , const double phi_,
                const double min_, const double max_)
  : myF(myF_), phi(phi_), min(min_), max(max_)
{
  assert(min < max);

  try
  {
    BisectMethod();
    pass = true;
  }
  catch (std::exception const&  ex)
  {
//    std::cerr << "\t" <<phi_ << "\t" << min_ << "\t" << max_ << "\n";
//    std::cerr << "\noutside range or no roots \n\n" << "\n";
    bestGuess = min;
    pass = false;
  }
}

void solve::BisectMethod(void)
{
  using std::placeholders::_1;
  const std::function<double(double)>
      myFuncReduced = std::bind( &solve::myRootFunc, this , _1 );

  namespace BMT =  boost::math::tools;
  constexpr size_t digitsBitsofPrecision = 64; //same as double
  const BMT::eps_tolerance<double> tol = digitsBitsofPrecision;

  const std::pair<double, double> result =
      BMT::bisect( myFuncReduced, min, max, tol, maxInt ) ;

  solnTolerance = abs( result.first - result.second ) ;
  bestGuess = math::average( result.first , result.second ) ;
}

double solve::returnSoln(void) const
{
  return bestGuess;
}

size_t solve::returnIterations(void) const
{
  return maxInt;
}

double solve::returnSolnTolerance(void) const
{
  return solnTolerance;
}

solve::~solve(void){}

}
