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
#include <math.h>
#include <boost/math/tools/roots.hpp>
#include "math/bisection.hpp"

namespace math{

size_t PrecisionToBits(const size_t precision)
{
  /*Enter the number of decimal precision required*/
  constexpr double log10of2 = log10(2);
  const double bits = precision / log10of2;

  return ceil(bits);
}

solve::solve( double(*myF_)(double), const double phi_, const double min_,
              const double max_)
  : myF(myF_), phi(phi_), min(min_), max(max_)
{
  namespace BMT =  boost::math::tools;

//  constexpr size_t digitsPrecision = 32;
//  constexpr size_t digitsBitsofPrecision = PrecisionToBits(digitsPrecision);
  constexpr size_t digitsBitsofPrecision = 64; //same as double
  BMT::eps_tolerance<double> tol = digitsBitsofPrecision;

  try
  {
    std::pair<double, double> result = BMT::bisect( myF, min, max, tol, maxInt);
    solnTolerance = abs( result.first - result.second );
    bestGuess = (result.first + result.second) / 2;
  }
  catch (std::exception const&  ex)
  {
    std::cout << "\noutside range or no roots \n\n" << "\n";
    bestGuess = max;
  }
}

double solve::returnSoln(void)
{
  return bestGuess;
}

size_t solve::returnIterations(void)
{
  return maxInt;
}

double solve::returnSolnTolerance(void)
{
  return solnTolerance;
}

solve::~solve(void){}

}
